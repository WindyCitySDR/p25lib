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

#include <cai/mfids.h>

using namespace CAI;
using type::mapping;

static const mapping::value_type mfids[] = {
   mapping::value_type( 0x00, "Standard MFID (pre-2001)" ),
   mapping::value_type( 0x01, "Standard MFID (post-2001)" ),
   mapping::value_type( 0x09, "Aselsan Inc." ),
   mapping::value_type( 0x10, "Relm / BK Radio" ),
   mapping::value_type( 0x18, "EADS Public Safety Inc." ),
   mapping::value_type( 0x20, "Cycomm" ),
   mapping::value_type( 0x28, "Efratom Time and Frequency Products, Inc" ),
   mapping::value_type( 0x30, "Com-Net Ericsson" ),
   mapping::value_type( 0x34, "Etherstack" ),
   mapping::value_type( 0x38, "Datron" ),
   mapping::value_type( 0x40, "Icom" ),
   mapping::value_type( 0x48, "Garmin" ),
   mapping::value_type( 0x50, "GTE" ),
   mapping::value_type( 0x55, "IFR Systems" ),
   mapping::value_type( 0x5A, "INIT Innovations in Transportation, Inc" ),
   mapping::value_type( 0x60, "GEC-Marconi" ),
   mapping::value_type( 0x64, "Harris Corp." ),
   mapping::value_type( 0x68, "Kenwood Communications" ),
   mapping::value_type( 0x70, "Glenayre Electronics" ),
   mapping::value_type( 0x74, "Japan Radio Co." ),
   mapping::value_type( 0x78, "Kokusai" ),
   mapping::value_type( 0x7C, "Maxon" ),
   mapping::value_type( 0x80, "Midland" ),
   mapping::value_type( 0x86, "Daniels Electronics Ltd." ),
   mapping::value_type( 0x90, "Motorola" ),
   mapping::value_type( 0xA0, "Thales" ),
   mapping::value_type( 0xA4, "M/A-COM" ),
   mapping::value_type( 0xB0, "Raytheon" ),
   mapping::value_type( 0xC0, "SEA" ),
   mapping::value_type( 0xC8, "Securicor" ),
   mapping::value_type( 0xD0, "ADI" ),
   mapping::value_type( 0xD8, "Tait Electronics" ),
   mapping::value_type( 0xE0, "Teletec" ),
   mapping::value_type( 0xF0, "Transcrypt International" ),
   mapping::value_type( 0xF8, "Vertex Standard" ),
   mapping::value_type( 0xFC, "Zetron, Inc" ),
};
static const size_t mfids_sz = sizeof(mfids) / sizeof(mfids[0]);
const mapping CAI::MFIDS(&mfids[0], &mfids[mfids_sz]);
