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

#include <type/bit_vector.h>
#include <type/assertions.h>

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <stdexcept>

using namespace std;
using namespace type;

bit_vector::bit_vector(size_t n) :
   vector<bit>(n)
{
}

size_t
bit_vector::pack(size_t out_sz, uint8_t *out) const
{
   CHECK_NOT_NULL(out);
   const size_t N = (7 + size()) / 8;
   CHECK_MAX_SIZE(out_sz, N);

   std::fill(out, out + out_sz, 0);
   for(size_t i = 0; i < size(); ++i) {
      out[i / 8] |= (at(i) ? 1 << (7 - (i % 8)) : 0);
   }
   return N;
}

size_t
bit_vector::unpack(size_t in_sz, const uint8_t *in)
{
   CHECK_NOT_NULL(in);

   const size_t N = in_sz * 8;
   resize(N);
   std::fill(begin(), end(), 0);
   for(size_t i = 0; i < N; ++i) {
      at(i) = in[i / 8] & (1 << (7 - (i % 8)));
   }
   return N;
}

uint64_t
bit_vector::extract(size_t begin, size_t end) const
{
   CHECK_MAX_SIZE(end - begin, 64);
   uint64_t out = 0LL;
   size_t nbits = end - begin;
   for(size_t i = begin; i < end; ++i) {
      out <<= 1;
      out |= (at(i) ? 1 : 0);
   }
   return out;
}

void
bit_vector::insert(size_t begin, size_t end, uint64_t value)
{
   CHECK_MAX_SIZE(end - begin, 64);
   const size_t NBITS = end - begin;
   for(int i = 0; i < NBITS; ++i) {
      uint64_t bit = 1LL << (NBITS - i - 1);
      at(begin + i) = (value & bit);
   }
}

uint64_t
bit_vector::extract(size_t bits_sz, const size_t bits[]) const
{
   CHECK_MAX_SIZE(bits_sz, 64);
   uint64_t out = 0LL;
   for(size_t i = 0; i < bits_sz; ++i) {
      out <<= 1;
      out |= (at(bits[i]) ? 1 : 0);
   }
   return out;
}

void
bit_vector::insert(size_t bits_sz, const size_t bits[], uint64_t in)
{
   CHECK_MAX_SIZE(bits_sz, 64);
   for(size_t i = 0; i < bits_sz; ++i) {
      uint64_t bit = 1LL << (bits_sz - i - 1);
      at(bits[i]) = (in & bit);
   }
}

string
bit_vector::to_string() const
{
#if 1
   ostringstream os;
   size_t n = size() % 64;
   uint64_t oddbits = extract(0, n);
   os << hex << oddbits;
   for(size_t i = n; i < size(); i += 64) {
      uint64_t bits = extract(i, i + 64);
      os << hex << setw(16) << setfill('0') << bits;
   }
   return os.str();
#else
   ostringstream os;
   for(size_t i = 0; i < size(); ++i) {
      if(0 == (i % 4)) {
         os << ' ';
      }
      os << (at(i) ? '1' : '0');
   }
   return os.str();
#endif
}
