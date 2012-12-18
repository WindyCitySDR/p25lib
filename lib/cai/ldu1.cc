/* -*- C++ -*- */

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

#include <cai/ldu1.h>
#include <cai/data_unit_handler.h>

using namespace CAI;
using namespace type;

ldu1::ldu1(const bit_vector& frame_body) :
   voice_data_unit(frame_body)
{
}

ldu1::~ldu1()
{
}

void
ldu1::apply_FEC()
{
   apply_RS_FEC();
   voice_data_unit::apply_FEC();
}

void
ldu1::compute_FEC()
{
   compute_RS_FEC();
   voice_data_unit::compute_FEC();
}

void
ldu1::dispatch(data_unit_handler& handler)
{
   handler.dispatch(*this);
}

snapshot&
ldu1::take_snapshot(snapshot& s) const
{
   link_control_sptr lc(link_control_word());
   lc->take_snapshot(s);
   return abstract_data_unit::take_snapshot(s);
}

static const size_t LC_BITS[] = {
   410, 411, 412, 413, 414, 415, 420, 421,
   436, 437, 442, 443, 444, 445, 446, 447,
   600, 601, 602, 603, 604, 605, 610, 611,
   612, 613, 614, 615, 620, 621, 622, 623,
   624, 625, 630, 631, 632, 633, 634, 635,
   788, 789, 792, 793, 794, 795, 800, 801,
   802, 803, 804, 805, 810, 811, 812, 813,
   814, 815, 820, 821, 822, 823, 824, 825,
};
static const size_t LC_BITS_SZ = sizeof(LC_BITS) / sizeof(LC_BITS[0]);

link_control_sptr
ldu1::link_control_word() const
{
   return link_control::create(frame_body().extract(LC_BITS_SZ, LC_BITS));
}

void
ldu1::link_control_word(link_control_sptr lcw)
{
   // ToDo: implement me!
}

static const size_t NOF_RS_CODEWORDS = 1; // ToDo!
static const size_t RS_CODEWORD_SZ = 24;
static const size_t RS_VALUE_SZ = 12;
static const size_t RS_CODEWORD_BITS[NOF_RS_CODEWORDS][RS_CODEWORD_SZ] = {
};

void
ldu1::apply_RS_FEC()
{   
   // ToDo: implement me!
}

void
ldu1::compute_RS_FEC()
{
   // ToDo: implement me!
}

