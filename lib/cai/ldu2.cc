/* -*- mode: C++ -*- */

/*
 * Copyright 2008-2010 Steve Glass
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

#include <cai/ldu2.h>
#include <cai/algids.h>
#include <cai/data_unit_handler.h>
#include <type/mapping.h>

#include <iomanip>
#include <sstream>

using namespace CAI;
using namespace std;
using namespace type;

ldu2::ldu2(const bit_vector& frame_body) :
   voice_data_unit(frame_body)
{
}

ldu2::~ldu2()
{
}

void
ldu2::apply_FEC()
{
   apply_RS_FEC();
   voice_data_unit::apply_FEC();
}

void
ldu2::compute_FEC()
{
   compute_RS_FEC();
   voice_data_unit::compute_FEC();
}

void
ldu2::dispatch(data_unit_handler& handler)
{
   handler.dispatch(*this);
}

snapshot&
ldu2::take_snapshot(snapshot& s) const
{
   s.add("algid", lookup(ALGIDS, algid()));
   s.add("kid",   kid());
   s.add("mi",    static_cast<string>(mi()));
   return abstract_data_unit::take_snapshot(s);
}

static const size_t ALGID_BITS[] = {
   978, 979, 980, 981, 982, 983, 988, 989
};
static const size_t ALGID_BITS_SZ = sizeof(ALGID_BITS) / sizeof(ALGID_BITS[0]);

uint8_t
ldu2::algid() const
{
   return frame_body().extract(ALGID_BITS_SZ, ALGID_BITS);
}

void
ldu2::algid(uint8_t algid)
{
   frame_body().insert(ALGID_BITS_SZ, ALGID_BITS, algid);
}

static const size_t KID_BITS[] = {
   990,  991,  992,  993,  998,  999, 1000, 1001,
   1002, 1003, 1010, 1011, 1012, 1013, 1014, 1015
};
static const size_t KID_BITS_SZ = sizeof(KID_BITS) / sizeof(KID_BITS[0]);

uint16_t
ldu2::kid() const
{
   return frame_body().extract(KID_BITS_SZ, KID_BITS);
}

void
ldu2::kid(uint16_t kid)
{
   return frame_body().insert(KID_BITS_SZ, KID_BITS, kid);
}

static const size_t MI_BITS[] = {
   410, 411, 412, 413, 414, 415, 420, 421, 
   422, 423, 424, 425, 432, 433, 434, 435, 
   436, 437, 442, 443, 444, 445, 446, 447, 
   600, 601, 602, 603, 604, 605, 610, 611, 
   612, 613, 614, 615, 620, 621, 622, 623, 
   624, 625, 630, 631, 632, 633, 634, 635, 
   788, 789, 792, 793, 794, 795, 800, 801, 
   802, 803, 804, 805, 810, 811, 812, 813, 
//   These bits should always be set to 0
//   814, 815, 820, 821, 822, 823, 824, 825
};
static const size_t MI_BITS_SZ = sizeof(MI_BITS) / sizeof(MI_BITS[0]);

MI
ldu2::mi() const
{
   return MI(frame_body().extract(MI_BITS_SZ, MI_BITS));
}

void
ldu2::mi(MI mi)
{
   frame_body().insert(MI_BITS_SZ, MI_BITS, mi);
}

static const size_t NOF_RS_CODEWORDS = 1; // ToDo!
static const size_t RS_CODEWORD_SZ = 24;
static const size_t RS_VALUE_SZ = 16;
static const size_t RS_CODEWORD_BITS[NOF_RS_CODEWORDS][RS_CODEWORD_SZ] = {
};

void
ldu2::apply_RS_FEC()
{   
   // ToDo: implement me!
}

void
ldu2::compute_RS_FEC()
{
   // ToDo: implement me!
}
