/* -*- mode: C++ -*- */

/*
 * Copyright 2010-2011 Steve Glass
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

#ifndef INCLUDED_FEC_TRELLIS_H
#define INCLUDED_FEC_TRELLIS_H

#include <stddef.h>
#include <stdint.h>
#include <vector>

namespace FEC {

   /**
    * A two-bit symbol used by the half-rate codec.
    */
   typedef uint8_t dibit;

   /**
    * A three bit symbol used by the 3/4 rate codec.
    */
   typedef uint8_t tribit;

   /**
    * A four bit symbol produced by the trellis encoder.
    */
   typedef uint8_t nybble;

   /**
    * 1/2 rate trellis encoder.
    *
    * \param IN A reference to the unencoded input buffer.
    * \return out The trellis-encoded buffer.
    * \throws runtime_error When decoding fails.
    */
   extern std::vector<nybble> trellis_1_2_encode(const std::vector<dibit>& IN);

   /**
    * 1/2 rate trellis decoder.
    *
    * \param IN A reference to the trellis-encoded input buffer.
    * \return The unencoded buffer.
    */
   extern std::vector<dibit> trellis_1_2_decode(const std::vector<nybble>& IN);

   /**
    * 3/4 rate trellis encoder.
    *
    * \param IN A reference to the unencoded input buffer.
    * \return out The trellis-encoded buffer.
    */
   extern std::vector<nybble> trellis_3_4_encode(const std::vector<tribit>& IN);

   /**
    * 3/4 rate trellis decoder.
    *
    * \param IN A reference to the trellis-encoded input buffer.
    * \return The unencoded buffer.
    * \throws runtime_error When decoding fails.
    */
   extern std::vector<tribit> trellis_3_4_decode(const std::vector<nybble>& IN);

}

#endif /* INCLUDED_FEC_TRELLIS_H */
