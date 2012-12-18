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

#include <cai/pdu.h>
#include <cai/data_unit_handler.h>
#include <type/assertions.h>

using namespace CAI;
using namespace type;

pdu::pdu(const bit_vector& frame_body) :
   abstract_data_unit(frame_body)
{
   CHECK_SIZE(frame_body.size(), reqd_frame_size());
}

pdu::~pdu()
{
}

void
pdu::dispatch(data_unit_handler& handler)
{
   handler.dispatch(*this);
}

uint16_t
pdu::reqd_frame_size()
{
  return 312;
}
