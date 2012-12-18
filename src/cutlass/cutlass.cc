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
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
 * License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with OP25; see the file COPYING.  If not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Boston, MA
 * 02110-1301, USA.
 */

#include <cutlass.h>
#include <fec/golay.h>
#include <fec/hamming.h>
#include <type/dump.h>

#include <iostream>
#include <iomanip>

using namespace boost;
using namespace CAI;
using namespace std;
using FEC::golay_23_12_decode;
using FEC::hamming_15_11_decode;
using std::vector;
using type::dump;

cutlass::cutlass() :
   d_state(SYNC),
   d_frame_no(0)
{
}

cutlass::~cutlass()
{
}

void
cutlass::dispatch(data_unit_sptr du)
{
   ++d_frame_no;
   data_unit_handler::dispatch(du);
}

void
cutlass::handle(hdu_sptr du)
{
   switch(d_state) {
   case RECV2:
      d_ldu2.reset();
   case RECV1:
      d_ldu1.reset();
   case SYNC:
   case SKIP:
      d_state = SYNC;
      d_mi = du->mi();
      d_algid = du->algid();
      d_kid = du->kid();
      break;
   default:
      break;
   }
}

void
cutlass::handle(ldu1_sptr du)
{
   switch(d_state) {
   case SYNC:
      d_state = RECV1;
      d_ldu1 = du;
      break;
   case RECV2:
      d_state = RECV1;
      d_mi = d_ldu2->mi();
      d_algid = d_ldu2->algid();
      d_kid = d_ldu2->kid();
      d_ldu1 = du;
      d_ldu2.reset();
      break;
   case SKIP:
   case RECV1:
      d_state = SKIP;
      d_ldu1.reset();
      d_ldu2.reset();
      break;
   default:
      break;
   }
}

void
cutlass::handle(ldu2_sptr du)
{
   switch(d_state) {
   case SKIP:
   case SYNC:
   case RECV2:
      d_state = SKIP;
      d_ldu1.reset();
      d_ldu2.reset();    
      break;
   case RECV1:
      d_state = RECV2;
      d_ldu2 = du;
      break;
   default:
      break;
   }
}

void
cutlass::handle(tdu_sptr du)
{
   switch(d_state) {
   case SKIP:
   case SYNC:
      break;
   case RECV1:
      d_state = SKIP;
      cut_last(d_mi, d_algid, d_kid, d_ldu1);
      d_ldu1.reset();
      d_ldu2.reset();
      break;
   case RECV2:
      d_state = SKIP;
      cut_last(d_mi, d_algid, d_kid, d_ldu2);
      d_ldu1.reset();
      d_ldu2.reset();
      break;
   default:
      break;
   }
}

void
cutlass::handle(tdu_with_link_control_sptr du)
{
   switch(d_state) {
   case SKIP:
   case SYNC:
      break;
   case RECV1:
      d_state = SKIP;
      cut_last(d_mi, d_algid, d_kid, d_ldu1);
      d_ldu1.reset();
      d_ldu2.reset();
      break;
   case RECV2:
      d_state = SKIP;
      cut_last(d_mi, d_algid, d_kid, d_ldu2);
      d_ldu1.reset();
      d_ldu2.reset();
      break;
   default:
      break;
   }
}

void
cutlass::cut_last(const MI& mi, uint8_t algid, uint16_t kid, voice_data_unit_sptr du)
{
   cout << "FRAME: " << dec << d_frame_no << endl;

//   vector<uint8_t> octets = du->pack();
//   cout << hex << dump(octets.size(), &octets[0]);
//   du->dump(cout);

   cout << "   MI: " << static_cast<string>(mi) << endl;
   cout << "ALGID: " << hex << setw(2) << setfill('0') << static_cast<uint16_t>(algid) << endl;
   cout << "  KID: " << hex << setw(4) << setfill('0') << kid << endl << endl;
   cout << "  LSD: " << hex << setw(4) << setfill('0') << du->low_speed_data() << endl << endl;

   for(size_t i = 0; i < 9; ++i) {
      voice_codeword long_cw(du->long_codeword(i));
      voice_codeword short_cw(decode(long_cw));
      cout << "IMBE#" << dec << 1+i << " " << short_cw.to_string() << " ";
      cout << endl;
   }

   cout << endl;
}

uint32_t
cutlass::pngen15(uint32_t& Pr)
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
cutlass::pngen23(uint32_t& Pr)
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
cutlass::decode(const voice_codeword& in)
{
   voice_codeword out(88);

   size_t errs = 0;
   uint32_t v0 = in.extract(0, 23);
   uint32_t u0 = golay_23_12_decode(v0) & 0xfff;
   out.insert(0, 12, u0);

   uint32_t pn = u0 << 4;
   uint32_t m1 = pngen23(pn);
   uint32_t v1 = in.extract(23, 46) ^ m1;  
   uint32_t u1 = golay_23_12_decode(v1) & 0xfff;
   out.insert(12, 24, u1);

   uint32_t m2 = pngen23(pn);
   uint32_t v2 = in.extract(46, 69) ^ m2;
   uint32_t u2 = golay_23_12_decode(v2) & 0xfff;
   out.insert(24, 36, u2);

   uint32_t m3 = pngen23(pn);
   uint32_t v3 = in.extract(69, 92) ^ m3;
   uint32_t u3 = golay_23_12_decode(v3) & 0xfff;
   out.insert(36, 48, u3);

   uint32_t m4 = pngen15(pn);
   uint16_t v4 = in.extract(92, 107) ^ m4;
   uint32_t u4 = hamming_15_11_decode(v4) & 0x7ff;
   out.insert(48, 59, u4);

   uint32_t m5 = pngen15(pn);
   uint16_t v5 = in.extract(107, 122) ^ m5;
   uint32_t u5 = hamming_15_11_decode(v5) & 0x7ff;
   out.insert(59, 70, u5);

   uint32_t m6 = pngen15(pn);
   uint16_t v6 = in.extract(122, 137) ^ m6;
   uint32_t u6 = hamming_15_11_decode(v6) & 0x7ff;
   out.insert(70, 81, u6);

   uint32_t u7 = in.extract(137, 144);
   out.insert(81, 88, u7);

#if 0
   // diagnostix!
   cout << endl;
   cout << " u0  u1  u2  u3  u4  u5  u6  u7" << endl;
   cout << hex << setw(3) << setfill('0');
   cout << u0 << " " << u1 << " " << u2 << " " << u3 << " " << u4 << " " << u5 << " " << u6 << " " << setw(2) << u7 << endl;
   cout << endl;
#endif

   return out;
}
