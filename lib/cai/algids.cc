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

#include <cai/algids.h>

using namespace CAI;
using type::mapping;

static const mapping::value_type algids[] = {
   /* Type I */
   mapping::value_type( 0x00, "ACCORDION 1.3" ),
   mapping::value_type( 0x01, "BATON (Auto Even)" ),
   mapping::value_type( 0x02, "FIREFLY Type 1" ),
   mapping::value_type( 0x03, "MAYFLY Type 1" ),
   mapping::value_type( 0x04, "SAVILLE" ),
   mapping::value_type( 0x41, "BATON (Auto Odd)" ),
   /* Type III */
   mapping::value_type( 0x80, "Plain" ),
   mapping::value_type( 0x81, "DES-OFB" ),
   mapping::value_type( 0x82, "2 key Triple DES" ),
   mapping::value_type( 0x83, "3 key Triple DES" ),
   mapping::value_type( 0x84, "AES-256" ),
   /* Motorola proprietary */
   mapping::value_type( 0x9F, "Motorola DES-XL" ),
   mapping::value_type( 0xA0, "Motorola DVI-XL" ),
   mapping::value_type( 0xA1, "Motorola DVP-XL" ),
   mapping::value_type( 0xAA, "Motorola ADP" ),
};
static const size_t algids_sz = sizeof(algids) / sizeof(algids[0]);
const mapping CAI::ALGIDS(&algids[0], &algids[algids_sz]);
