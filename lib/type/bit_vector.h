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

#ifndef INCLUDED_TYPE_BIT_VECTOR_H
#define INCLUDED_TYPE_BIT_VECTOR_H

#include <stdint.h>
#include <string>
#include <vector>

namespace type {

   /**
    * bit is a synonym for bool.
    */
   typedef bool bit;

	/**
    * bit_vector is a minor specialization of vector<bool> that adds
    * insert/extract accessors.
    */
   class  bit_vector : public std::vector<bit>
   {
   public:
      
      /**
       * bit_vector constructor. Constructs a bit_vector of initial
       * size n.
       *
       * \param n The initial size of the vector.
       */
      bit_vector(size_t n = 0);

      /**
       * Pack this bit_vector into an octet buffer. If the output
       * buffer is not large enough to contain the whole of the
       * bit_vector then a length_error is thrown.
       *
       * \param out_sz The size of the octet buffer.
       * \param out Address of the octet buffer to pack into.
       * \return The number of octets packed into out.
       */
      size_t pack(size_t out_sz, uint8_t *out) const;

      /**
       * Unpack an octet buffer into this bit_vector. The previous
       * content of the bit_vector will be completely destroyed and it
       * is resized to hold only the bits unpacked from the buffer.
       *
       * \param in_sz The size of the octet buffer,
       * \param in Address of the octet buffer to unpack from.
       * \return The number of octets unpacked from in.
       */
      size_t unpack(size_t in_sz, const uint8_t *in);

      /**
       * Extract value of bits[begin, end).
       *
       * \param begin The beginning bit position.
       * \param end The ending bit position.
       * \return A uint64_t containing the value
       */
      uint64_t extract(size_t begin, size_t end) const;

      /**
       * Insert value into bits[from, to).
       *
       * \param begin The beginning bit position.
       * \param end The ending bit position.
       * \param value A uint64_t containing the value to insert
       */
      void insert(size_t begin, size_t end, uint64_t value);

      /**
       * Extract value of bits from [bits[0..bits_sz)).
       *
       * \param bits_sz The size of the bits array.
       * \param bits An array specifying the ordinals of the bits to extract.
       * \return A uint64_t containing the value
       */
      uint64_t extract(size_t bits_sz, const size_t bits[]) const;

      /**
       * Insert value of bits into [bits[0..bits_sz)).
       *
       * \param bits_sz The size of the bits array.
       * \param bits An array specifying the ordinals of the bits to insert.
       * \param A uint64_t containing the value to insert
       */
      void insert(size_t bits_sz, const size_t bits[], uint64_t in);

      /**
       * Extract sequential bits from [bits[0..bits_sz)).
       *
       * \param bits_sz A pointer to a size_t specifying the size of the bits array.
       * \param bits An array specifying the ordinals of the bits to extract.
       * \return A bit_vector containing the extracted bits.
       */
      bit_vector extract_bit_vector(size_t bits_sz, const size_t bits[]) const;

      /**
       * Insert sequential bits of in into [bits[0..bits_sz)].
       *
       * \param bits_sz The size of the bits array.
       * \param bits An array specifying the ordinals of the bits to insert.
       * \param A bit_vector containing the bits to insert.
       */
      void insert_bit_vector(size_t bits_sz, const size_t bits[], const bit_vector& in);

      /**
       * Returns this bit vector represented as a hex string.
       *
       * \return A string representing the bit_vector.
       */
      std::string to_string() const;

   };

}

#endif // INCLUDED_TYPE_BIT_VECTOR_H
