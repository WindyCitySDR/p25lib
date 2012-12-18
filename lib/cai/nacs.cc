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

#include <cai/nacs.h>

using namespace CAI;
using type::mapping;

static const mapping::value_type nacs[] = {
   mapping::value_type( 0x293, "Default NAC" ),
   mapping::value_type( 0xF7E, "Receiver to open on any NAC" ),
   mapping::value_type( 0xF7F, "Repeater to receive and retransmit any NAC" ),
};
static const size_t nacs_sz = sizeof(nacs) / sizeof(nacs[0]);
const mapping CAI::NACS(&nacs[0], &nacs[nacs_sz]);
