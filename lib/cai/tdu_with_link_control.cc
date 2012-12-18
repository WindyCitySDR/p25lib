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

#include <cai/tdu_with_link_control.h>
#include <cai/data_unit_handler.h>
#include <type/assertions.h>

#include <iomanip>
#include <sstream>
#include <stdexcept>

using namespace CAI;
using namespace std;
using namespace type;

tdu_with_link_control::tdu_with_link_control(const bit_vector& frame_body) :
   abstract_data_unit(frame_body)
{
   CHECK_SIZE(frame_body.size(), reqd_frame_size());
}

tdu_with_link_control::~tdu_with_link_control()
{
}

void
tdu_with_link_control::correct_errors()
{
#if 0
   bit_vector& bits = frame_body();

   static itpp::Reed_Solomon rs(63, 17, true);
   itpp::bvec b(70);
   swab(frame, 114, 122, b,  0);
   swab(frame, 122, 126, b,  8);
   swab(frame, 138, 142, b, 12);
   swab(frame, 144, 152, b, 16);
   swab(frame, 164, 176, b, 24);
   swab(frame, 188, 200, b, 36);
   swab(frame, 212, 213, b, 48);
   swab(frame, 216, 226, b, 50);
   swab(frame, 238, 250, b, 60);
   itpp::bvec bd(rs.decode(b));
#endif
}

void
tdu_with_link_control::dispatch(data_unit_handler& handler)
{
   handler.dispatch(*this);
}

uint16_t
tdu_with_link_control::reqd_frame_size()
{
   return 432;
}


#if 0
link_control_sptr
tdu_with_link_control::get_link_code_word() const
{
   const size_t LC_BITS[] = {
      114, 115, 116, 117, 118, 119, 120, 121,
      144, 145, 146, 147, 148, 149, 150, 151,
      164, 165, 166, 167, 168, 169, 170, 171,
      172, 173, 174, 175, 188, 189, 190, 191,
      192, 193, 194, 195, 196, 197, 198, 199,
      212, 213, 216, 217, 218, 219, 220, 221,
      222, 223, 224, 225, 238, 239, 240, 241,
      242, 243, 244, 245, 246, 247, 248, 249,
   };
   const size_t LC_BITS_SZ = sizeof(LCW_BITS) / sizeof(LCW_BITS[0]);
}
#endif
