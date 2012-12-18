/* -*- mode: C++ -*- */

/*
 * Copyright 2010-2011 Steve Glass
 * Copyright 2008-2010 Mike Ossman
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

#define __STDC_LIMIT_MACROS

#include <fec/trellis.h>
#include <type/assertions.h>

#include <sstream>
#include <iomanip>

using namespace FEC;
using namespace std;
using type::raise;

vector<nybble>
FEC::trellis_1_2_encode(const vector<dibit>& IN)
{
   /* Trellis encoder state transitions.
    * \see Table 7-2 FDMA CAI Specification.
    */
   static const uint8_t STATES[4][4] = {
      {  0, 15, 12,  3 },
      {  4, 11,  8,  7 },
      { 13,  2,  1, 14 },
      {  9,  6,  5, 10 }
   };

   /* Constellation to dibit pair mapping in packed format.
    * \see Table 7-3 FDMA CAI Specification.
    */
   static const nybble MAPPINGS[16] = {
      0x2, 0xa, 0x7, 0xf,
      0xe, 0x6, 0xb, 0x3,
      0xd, 0x5, 0x8, 0x0,
      0x1, 0x9, 0x4, 0xc
   };

   // perform trellis encoding
   uint8_t state = 0;
   const size_t IN_SZ = IN.size();
   vector<nybble> out(IN_SZ + 1);
   for(size_t i = 0; i < IN_SZ; ++i) {
      const dibit DIBIT_MASK = 0x3;
      dibit d = IN[i] & DIBIT_MASK;
      uint8_t s = STATES[state][d];
      out[i] = MAPPINGS[s];
      state = d;
   }
   out[IN_SZ] = MAPPINGS[STATES[state][0]];

   return out;
}

vector<dibit>
FEC::trellis_1_2_decode(const vector<nybble>& IN)
{
   CHECK_MIN_SIZE(IN.size(), 1);

	/* constellation to dibit pair mapping
    */
	static const uint8_t NEXT_WORDS[4][4] = {
		{ 0x2, 0xc, 0x1, 0xf },
		{ 0xe, 0x0, 0xd, 0x3 },
		{ 0x9, 0x7, 0xa, 0x4 },
		{ 0x5, 0xb, 0x6, 0x8 }
	};

   /* bit counts
    */
   static const uint8_t BIT_COUNT[] = {
      0, 1, 1, 2,
      1, 2, 2, 3,
      1, 2, 2, 3,
      2, 3, 3, 4
   };

   // perform trellis decoding
   uint8_t state = 0;
   const size_t IN_SZ = IN.size() - 1;
   vector<uint8_t> out;
   out.reserve(IN_SZ);
   for(size_t i = 0; i < IN_SZ; ++i) {
      const uint8_t NYBBLE_MASK = 0xf;
		uint8_t codeword = IN[i] & NYBBLE_MASK;
		// find dibit with minimum Hamming distance
      uint8_t m = 0;
      uint8_t ns = UINT8_MAX;
      uint8_t hd = UINT8_MAX;
		for(size_t j = 0; j < 4; j++) {
         uint8_t n = BIT_COUNT[codeword ^ NEXT_WORDS[state][j]];
         if(n < hd) {
            m = 1;
            hd = n;
            ns = j;
         } else if(n == hd) {
            ++m;
         }
		}
      if(m != 1) {
         ostringstream msg;
         msg << "decoding error at offset " << i << endl;
         raise<runtime_error>(__PRETTY_FUNCTION__, __FILE__, __LINE__, msg.str());
      }
		state = ns;
      out.push_back(state);
   }
   return out;
}
