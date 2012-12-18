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

#ifndef INCLUDED_FEC_BCH_H
#define INCLUDED_FEC_BCH_H

#include <cstddef>
#include <stdint.h>

namespace FEC {

   /**
    * APCO BCH(63,16,11) encoder. Encodes the supplied value and
    * returns the codeword.
    *
    * \param value The 16-bit value to encode.
    * \return The encoded codeword.
    */
   extern uint64_t bch_63_16_encode(uint16_t value);

   /**
    * APCO BCH(63,16,11) decoder. Decodes cw and return the result. If
    * nof_errs is non-NULL then it is updated to reflect the number of
    * detected errors.
    *
    * \param cw The 63-bit codeword to decode.
    * \param nof_errs Pointer to an error tally.
    * \return The number of errors detected; UINT8_MAX if decode failed.
    */
   extern uint16_t bch_63_16_decode(uint64_t cw, uint8_t *nof_errs = NULL);

}

#endif /* INCLUDED_FEC_BCH_H */
