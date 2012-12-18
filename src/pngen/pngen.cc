/* -*- mode: C++ -*- */

/*
 * Copyright 2010 Steve Glass
 * 
 * This file is part of OP25.
 * 
 * OP25 is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * OP25 is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with OP25; see the file COPYING. If not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Boston, MA
 * 02110-1301, USA.
 */

#include <cai/data_unit.h>
#include <cai/voice_data_unit.h>
#include <fec/golay.h>
#include <fec/hamming.h>

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <sysexits.h>

using namespace CAI;
using namespace FEC;
using namespace std;
using namespace type;

uint32_t
pngen15(uint32_t& Pr)
{
   int n = 0;
   for(int i = 14; i >= 0; --i) {
      Pr = (173 * Pr + 13849) & 0xffffu;
      if(Pr & 32768) {
         n += (1 << i);
      }
   }
   return n;
}

uint32_t
pngen23(uint32_t& Pr)
{
   int n = 0;
   for(int i = 22; i >= 0; --i) {
      Pr = (173 * Pr + 13849) & 0xffffu;
      if(Pr & 32768) {
         n += (1 << i);
      }
   }
   return  n;
}

voice_codeword
deinterleave(const voice_codeword& in)
{
   static const size_t BITS[] = {
      0, 7, 12, 19, 24, 31, 36, 43, 48, 55, 60, 67,
      72, 79, 84, 91, 96, 103, 108, 115, 120, 127, 132, 139,
      1, 6, 13, 18, 25, 30, 37, 42, 49, 54, 61, 66,
      73, 78, 85, 90, 97, 102, 109, 114, 121, 126, 133, 138,
      2, 9, 14, 21, 26, 33, 38, 45, 50, 57, 62, 69,
      74, 81, 86, 93, 98, 105, 110, 117, 122, 129, 134, 141,
      3, 8, 15, 20, 27, 32, 39, 44, 51, 56, 63, 68,
      75, 80, 87, 92, 99, 104, 111, 116, 123, 128, 135, 140,
      4, 11, 16, 23, 28, 35, 40, 47, 52, 59, 64, 71,
      76, 83, 88, 95, 100, 107, 112, 119, 124, 131, 136, 143,
      5, 10, 17, 22, 29, 34, 41, 46, 53, 58, 65, 70,
      77, 82, 89, 94, 101, 106, 113, 118, 125, 130, 137, 142
   };
   static const size_t BITS_SZ = sizeof(BITS) / sizeof(BITS[0]);

   voice_codeword out(in.size());
   for(size_t i = 0; i < out.size(); ++i) {
      out[i] = in[BITS[i]];
   }
   return out;
}

void
display(const voice_codeword& cw)
{
   size_t errs = 0;
   uint32_t v0 = cw.extract(0, 23);
   v0 = golay_23_12_decode(v0);
   uint32_t u0 = v0 & 0xfff;

   uint32_t pn = u0 << 4;
   uint32_t m1 = pngen23(pn);
   uint32_t v1 = cw.extract(23, 46) ^ m1;
   uint32_t u1 = golay_23_12_decode(v1) & 0xfff;

   uint32_t m2 = pngen23(pn);
   uint32_t v2 = cw.extract(46, 69) ^ m2;
   uint32_t u2 = golay_23_12_decode(v2) & 0xfff;

   uint32_t m3 = pngen23(pn);
   uint32_t v3 = cw.extract(69, 92) ^ m3;
   uint32_t u3 = golay_23_12_decode(v3) & 0xfff;

   uint32_t m4 = pngen15(pn);
   uint32_t v4 = cw.extract(92, 107) ^ m4;
   uint32_t u4 = hamming_15_11_decode(v4) & 0x7ff;

   uint32_t m5 = pngen15(pn);
   uint32_t v5 = cw.extract(107, 122) ^ m5;
   uint32_t u5 = hamming_15_11_decode(v5) & 0x7ff;

   uint32_t m6 = pngen15(pn);
   uint32_t v6 = cw.extract(122, 137) ^ m6;
   uint32_t u6 = hamming_15_11_decode(v6) & 0x7ff;

   uint32_t u7 = cw.extract(137, 144);
   u7 <<= 1; /* so that bit0 is free (see note about BOT bit */

   cout << hex << setw(3) << setfill('0');
   cout << u0 << " " << u1 << " " << u2 << " " << u3 << " " << u4 << " " << u5 << " " << u6 << " " << setw(2) << u7 << endl;
}

int
main(int ac, char **av)
{
   static const uint16_t bits[] = {
      0x6C42, 0xE85D, 0xE2E8, 0x2693, 0x63D9, 0x81F9, 0xBE23, 0xB18A, 0xE004    
   };

   voice_codeword vcw(144);
   for(size_t i = 0; i < 9; ++i) {
      size_t where = i * 16;
      vcw.insert(where, where + 16, bits[i]);
   }

   cout << vcw.to_string() << endl;

   voice_codeword x(deinterleave(vcw));

   cout << x.to_string() << endl;

   display(deinterleave(vcw));

   return(EX_OK);
}
