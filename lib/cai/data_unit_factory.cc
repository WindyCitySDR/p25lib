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

#include <cai/data_unit.h>
#include <cai/hdu.h>
#include <cai/ldu1.h>
#include <cai/ldu2.h>
#include <cai/pdu.h>
#include <cai/tdu.h>
#include <cai/tdu_with_link_control.h>
#include <cai/tsdu.h>

using namespace CAI;
using namespace type;

data_unit_sptr
data_unit::create(size_t octets_sz, const uint8_t *octets)
{
   bit_vector bits;
   bits.unpack(octets_sz, octets);
   return create(bits);
}

data_unit_sptr
data_unit::create(const bit_vector& frame_body)
{
   data_unit_sptr d;
   uint8_t duid = frame_body.extract(60, 64);
   switch(duid) {
   case 0x0:
      d = data_unit_sptr(new hdu(frame_body));
      break;
   case 0x3:
      d = data_unit_sptr(new tdu(frame_body));
      break;
   case 0x5:
      d = data_unit_sptr(new ldu1(frame_body));
      break;
   case 0xa:
      d = data_unit_sptr(new ldu2(frame_body));
      break;
   case 0x7:
      d = data_unit_sptr(new tsdu(frame_body));
      break;
   case 0x9: // VSELP "voice PDU"
   case 0xc:
      d = data_unit_sptr(new pdu(frame_body));
      break;
   case 0xf:
      d = data_unit_sptr(new tdu_with_link_control(frame_body));
      break;
   default:
      // ToDo: throw a invalid_argument exception!
      break;
   };
   return d;
}
