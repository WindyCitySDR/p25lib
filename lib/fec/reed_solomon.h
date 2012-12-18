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

#ifndef INCLUDED_FEC_REED_SOLOMON_H
#define INCLUDED_FEC_REED_SOLOMON_H

#include <stddef.h>
#include <stdint.h>

namespace FEC {

   /* APCO Reed_Solomon(36,20,17) ecoder.
    *
    * \param val The 20-hexbit value to encode.
    * \return The encoded codeword.
    */
   extern uint32_t reed_solomon_23_11_encode(uint16_t);

   /* APCO Reed_Solomon(33,20,17) decoder.
    *
    * \param cw The 23-bit codeword to decode.
    * \param nof_errs Pointer to an error tally.
    * \return The number of errors detected.
    */
   extern uint16_t reed_solomon_23_11_decode(uint32_t cw, size_t *nof_errs = NULL);

   /**
    * fake (24,12,13) Reed-Solomon decoder, no error correction
    *
    * \param cw 
    * \param value 
    */
   extern void rs_24_12_13_decode(uint8_t *cw, uint8_t *value);

   /**
    * fake (24,16,9) Reed-Solomon decoder, no error correction.
    */
   extern void rs_24_16_9_decode(uint8_t *cw, uint8_t *value);

   /**
    * fake (36,20,17) Reed-Solomon decoder, no error correction.
    */
   extern void rs_36_20_17_decode(uint8_t *cw, uint8_t *value);

}

#endif /* INCLUDED_FEC_REED_SOLOMON_H */
