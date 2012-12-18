/* -*- mode: C++ -*- */

/*
 * Copyright 2008-2010, 2009 Steve Glass
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

#include <cai/cipher.h>

using namespace CAI;
using type::bit_vector;

cipher::~cipher()
{
}

uint8_t
cipher::algid() const
{
   return d_algid;
}

uint16_t
cipher::keyid() const
{
   return d_keyid;
}

cipher::cipher(uint8_t algid, uint16_t keyid) :
   d_algid(algid),
   d_keyid(keyid)
{
}
