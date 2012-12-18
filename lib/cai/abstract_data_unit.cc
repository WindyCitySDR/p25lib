/* -*- mode: C++ -*- */

/*
 * Copyright 2008-2011 Steve Glass
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
 * License for more details.v
 * 
 * You should have received a copy of the GNU General Public License
 * along with OP25; see the file COPYING.  If not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Boston, MA
 * 02110-1301, USA.
 */

#include <cai/abstract_data_unit.h>
#include <cai/duids.h>
#include <cai/nacs.h>
#include <fec/bch.h>
#include <type/mapping.h>

#include <algorithm>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <stdexcept>

using namespace CAI;
using namespace FEC;
using namespace std;
using namespace type;

abstract_data_unit::~abstract_data_unit()
{
}

void
abstract_data_unit::apply_FEC()
{
}

void
abstract_data_unit::compute_FEC()
{
}

const bit_vector& 
abstract_data_unit::frame_body() const
{
   return frame_body_;
}

vector<uint8_t>
abstract_data_unit::pack() const
{
   vector<uint8_t> packed((frame_body_.size() + 7) / 8);
   frame_body_.pack(packed.size(), &packed[0]);
   return packed;
}

snapshot&
abstract_data_unit::take_snapshot(snapshot& s) const
{
   s.add("duid", lookup(DUIDS, DUID()));
   s.add("nac",  lookup(NACS,  NAC()));
   return s;
}

void
abstract_data_unit::write(ostream& os) const
{
   const size_t NCHUNKS =  frame_body().size() / 12;
   os << "      ___________0___________  ___________1___________";
   for(size_t i = 0; i < NCHUNKS; ++i) {
      if(0 == (i % 12)) {
         os << endl;
         os << dec << setw(4) << setfill('0') << i << "  ";
      } else if(0 == (i % 6)) {
         os << " ";
      }
      size_t where = i * 12;
      uint16_t bits = frame_body().extract(where, where + 12);
      os << hex << setw(3) << setfill('0') << bits << " ";
   }
   os << endl;
}

uint64_t
abstract_data_unit::FS() const
{
   return frame_body().extract(0, 48);
}

void
abstract_data_unit::FS(uint64_t fs)
{
   return frame_body().insert(0, 48, fs);
}

static const size_t NID_BITS[] = {
    48,  49,  50,  51,  52,  53,  54,  55, 
    56,  57,  58,  59,  60,  61,  62,  63,
    64,  65,  66,  67,  68,  69,  72,  73,
    74,  75,  76,  77,  78,  79,  80,  81,
    82,  83,  84,  85,  86,  87,  88,  89,
    90,  91,  92,  93,  94,  95,  96,  97,
    98,  99, 100, 101, 102, 103, 104, 105,
   106, 107, 108, 109, 110, 111, 112, 113,
};
static const size_t NID_BITS_SZ = sizeof(NID_BITS) / sizeof(NID_BITS[0]);

uint16_t
abstract_data_unit::NID() const
{
   uint64_t cw = frame_body().extract(NID_BITS_SZ, NID_BITS);
   return bch_63_16_decode(cw);
}

void
abstract_data_unit::NID(uint16_t nid)
{
   uint64_t cw = bch_63_16_encode(nid);
   frame_body().insert(NID_BITS_SZ, NID_BITS, cw);
}

const uint16_t DUID_MASK = 0xf;

uint8_t
abstract_data_unit::DUID() const
{
   return NID() & DUID_MASK;
}

void
abstract_data_unit::DUID(uint8_t duid)
{
   NID((NID() & ~DUID_MASK) | (duid & DUID_MASK));
}

const uint16_t NAC_MASK = 0xfff0;
const uint16_t NAC_SHIFT = 4;

uint16_t
abstract_data_unit::NAC() const
{
   return (NID() & NAC_MASK) >> NAC_SHIFT;
}

void
abstract_data_unit::NAC(uint16_t nac)
{
   NID(((nac << NAC_SHIFT) & NAC_MASK) | (NID() & ~NAC_MASK));
}

const size_t abstract_data_unit::SS_SZ_ = 2;
const size_t abstract_data_unit::SS_INTERVAL_ = 70;

vector<status_symbol>
abstract_data_unit::SS() const
{
   vector<status_symbol> ss;
   const size_t FRAME_BODY_SZ = frame_body().size();
   const size_t NSYMS = FRAME_BODY_SZ / (SS_INTERVAL_ + SS_SZ_);
   ss.reserve(NSYMS);
   for(size_t i = 0; i < NSYMS; ++i) {
      const size_t OFS = (1 + i) * (SS_INTERVAL_ + SS_SZ_);
      uint8_t symbol = frame_body().extract(OFS - SS_SZ_, OFS);
      ss.push_back(static_cast<status_symbol>(symbol));
   }
   return ss;
}

void
abstract_data_unit::SS(const vector<status_symbol>& ss)
{
   const size_t FRAME_BODY_SZ = frame_body().size();
   const size_t NSYMS = min(ss.size(), FRAME_BODY_SZ / (SS_INTERVAL_ + SS_SZ_));
   for(size_t i = 0; i < NSYMS; ++i) {
      const size_t OFS = (1 + i) * (SS_INTERVAL_ + SS_SZ_);
      frame_body().insert(OFS - SS_SZ_, OFS, static_cast<uint8_t>(ss[i]));
   }
}

abstract_data_unit::abstract_data_unit(size_t frame_body_sz) :
   frame_body_(frame_body_sz)
{
}

abstract_data_unit::abstract_data_unit(const bit_vector& frame_body) :
   frame_body_(frame_body)
{
}

bit_vector& 
abstract_data_unit::frame_body()
{
   return frame_body_;
}

bool
abstract_data_unit::is_status_symbol(size_t i) const
{
   // TODO: test i is even!
   return !((i + 2) % (SS_INTERVAL_ + SS_SZ_));
}
