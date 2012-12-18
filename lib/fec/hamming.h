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

#ifndef INCLUDED_HAMMING_H
#define INCLUDED_HAMMING_H

#include <cstddef>
#include <stdint.h>

namespace FEC {

   /*
    * APCO Hamming(15,11,3) ecoder.
    *
    * \param val The 11-bit value to encode.
    * \return The encoded codeword.
    */
   extern uint16_t hamming_15_11_encode(uint16_t val);

   /*
    * APCO Hamming(15,11,3) decoder.
    *
    * \param cw The 15-bit codeword to decode.
    * \param nof_errs Pointer to an error tally.
    * \return The corrected 11 bit codeword.
    */
   extern uint16_t hamming_15_11_decode(uint16_t cw, size_t *nof_errs = NULL);

}

#endif /* INCLUDED_HAMMING_H */
