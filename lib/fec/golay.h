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

#ifndef INCLUDED_FEC_GOLAY_H
#define INCLUDED_FEC_GOLAY_H

#include <stddef.h>
#include <stdint.h>

namespace FEC {

   /* APCO Golay(23,12,7) ecoder.
    *
    * \param val The 12-bit value to encode.
    * \return The encoded codeword.
    */
   extern uint32_t golay_23_12_encode(uint16_t);

   /* APCO Golay(23,12,7) decoder.
    *
    * \param cw The 23-bit codeword to decode.
    * \param nof_errs Pointer to an error tally.
    * \return The number of errors detected.
    */
   extern uint16_t golay_23_12_decode(uint32_t cw, size_t *nof_errs = NULL);

}

#endif /* INCLUDED_FEC_GOLAY_H */
