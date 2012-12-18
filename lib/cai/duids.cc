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

#include <cai/duids.h>

using namespace CAI;
using type::mapping;

static const mapping::value_type duids[] = {
   mapping::value_type( 0x0, "HDU" ),
   mapping::value_type( 0x3, "TDU" ),
   mapping::value_type( 0x5, "LDU1" ),
   mapping::value_type( 0x7, "TSBK" ),
   mapping::value_type( 0x9, "VSELP" ),
   mapping::value_type( 0xa, "LDU2" ),
   mapping::value_type( 0xc, "PDU" ),
   mapping::value_type( 0xf, "TDU (with LC)" ),
};
static const size_t duids_sz = sizeof(duids) / sizeof(duids[0]);
const mapping CAI::DUIDS(&duids[0], &duids[duids_sz]);
