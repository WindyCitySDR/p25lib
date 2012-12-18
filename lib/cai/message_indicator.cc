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

#include <cai/message_indicator.h>
#include <type/assertions.h>

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace CAI;
using namespace std;
using namespace type;

message_indicator::message_indicator()
{
   bits_.set(bits_.size() - 1);
}

message_indicator::message_indicator(const string& mi_str)
{
   CHECK_MIN_SIZE(mi_str.size(), 16);
   const char *begins = mi_str.c_str();
   char *ends = const_cast<char*>(begins) + mi_str.size();
   // ToDo: compile-time check that sizeof(long long unsigned) == sizeof(uint64_t)
   uint64_t b = strtoull(begins, &ends, 16);
   // ToDo: ensure (*begins != '\0' && *ends =='\0')
   bits_ = message_indicator_bits(b);
}

message_indicator::message_indicator(uint64_t mi_val) :
   bits_(mi_val)
{
}

message_indicator::message_indicator(const message_indicator& other) :
   bits_(other.bits_)
{
}

message_indicator&
message_indicator::operator=(const message_indicator& other)
{
   if(this != &other) {
      bits_ = other.bits_;
   }
   return *this;
}

bool
message_indicator::operator==(const message_indicator& other) const
{
   return bits_ == other.bits_;
}


message_indicator::~message_indicator()
{
}

message_indicator::operator string() const
{
   ostringstream os;
   os << hex << setfill('0') <<setw(16) << bits_.to_ulong();
   return os.str();
}

message_indicator::operator uint64_t() const
{
   // ToDo: compile time check sizeof(uint64_t) == sizeof(unsingned long)

   return bits_.to_ulong();
}

void
message_indicator::clock(uint64_t n)
{
   for(uint64_t i = 0; i < n; ++i) {
      const bool  bit = bits_[14] ^ bits_[26] ^ bits_[37] ^ bits_[45] ^ bits_[61] ^ bits_[63];
      bits_ <<= 1;
      bits_ |= bit;
   }
}
