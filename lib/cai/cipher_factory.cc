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

#include <cipher.h>

using namespace CAI;

cipher_sptr
cipher::get(uint8_t algid, uint16_t keyid)
{
   cipher_sptr c;
   switch(algid) {
   case 0x80:
      c = new null_cipher(algid, keyid);
      break;
   case 0x81:
      c = new des_ofb_cipher(algid, keyid);
      break;
   case 0xaa:
      c = new rc4_cipher(algid, keyid);
      break;
   default:
      // ToDo: throw an exception
      break;
   }
   return c;
}
