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

#ifndef INCLUDED_CAI_MESSAGE_INDICATOR_H
#define INCLUDED_CAI_MESSAGE_INDICATOR_H

#include <type/bit_vector.h>

#include <bitset>
#include <stdint.h>
#include <string>

namespace CAI
{

   /**
    * P25 Message Indicator (MI) - the initialization value used by
    * the encryption cipher. Note that although this is a 72 bit
    * quantity the DES implementation uses just 64 bits and ignores
    * the last 8 bits.
    */
   class message_indicator
   {
   public:

      /**
       * message_indicator default constructor.
       */
      message_indicator();

      /**
       * message_indicator constructor. Constructs an MI from the
       * supplied string representation.
       *
       * \param mi_str A string created by operator std::string().
       */
      explicit message_indicator(const std::string& mi_str);

      /**
       * message_indicator constructor. Constructs an MI from the
       * supplied frame. When bits_sz is too small a length_error is
       * thrown.
       *
       * \param mi_val A uint64_t containing the high order 8 octets of the MI.
       */
      explicit message_indicator(uint64_t mi_val);

      /**
       * message_indicator copy constructor. Construct a new
       * message_indicator instance from an existing instance.
       *
       * \param other A const reference to the other message_indicator.
       */
      message_indicator(const message_indicator& other);

      /**
       * message_indicator assignment operator.
       *
       * \param other A const reference to the other message_indicator.
       */
      message_indicator& operator=(const message_indicator& other);

      /**
       * message_indicator equality comparison operator.
       * 
       * \param true when this MI is equal to other; false otherwise;
       */
      bool operator==(const message_indicator& other) const;

      /**
       * message_indicator destructor.
       */
      ~message_indicator();

      /**
       * String conversion operator. Converts this MI to string
       * representation.
       *
       * \return A string representing the MI.
       */
      operator std::string() const;

      /**
       * Return the high order 64 bits as an uint64_t.
       *
       * \return A uint64_t containing the high order 64 bits.
       */
      operator uint64_t() const;

      /**
       * Clock this MI by n bits. This simply winds forward the LFSR.
       * 
       * \param n The number of bits to clock.
       */
      void clock(uint64_t n = 64);

   private:

      /**
       * Alias for bitset<64>.
       */
      typedef std::bitset<64> message_indicator_bits;

      /**
       * The bits that comprise this MI.
       */
      message_indicator_bits bits_;

   };

   /**
    * Abbreviated typename for message_indicator.
    */
   typedef message_indicator MI;

}

#endif /* INCLUDED_CAI_MESSAGE_INDICATOR_H */
