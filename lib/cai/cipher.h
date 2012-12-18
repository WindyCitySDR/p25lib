/* -*- mode: C++ -*- */

/*
 * Copyright 2008-2011 Steve Glass
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

#ifndef INCLUDED_CAI_CIPHER_H
#define INCLUDED_CAI_CIPHER_H

#include <type/bit_vector.h>

#include <boost/shared_ptr.hpp>
#include <stdint.h>

namespace CAI
{

   /**
    * Declare cipher_sptr as synonym for shared_ptr<class cipher>.
    */
   typedef boost::shared_ptr<class cipher> cipher_sptr;

   /**
    * P25 stream cipher implementation.
    */
   class cipher {
   public:

      /**
       * Construct a cipher for the given algid, kid combination. If
       * either algid or kid are unrecognized then a null cipher_sptr
       * is returned.
       *
       * \param algid The encryption algorithm.
       * \param kid The ID of the key to use.
       * \return A (possibly null) cipher_sptr pointint to the cipher.
       */
      static cipher_sptr get(uint8_t algid, uint16_t kid);

      /**
       * (Virtual) cipher constructor.
       */
      virtual ~cipher();

      /**
       * Return the algorithm ID for this cipher.
       *
       * \param A uint8_t idenntifying the cipher.
       */
      virtual uint8_t algid() const = 0;

      /**
       * Return the key ID for this cipher instance.
       *
       * \param A uint16_t identifying the key to use.
       */
      virtual uint16_t keyid() const = 0;

      /**
       * Return the next n octets of the keystream.
       *
       * \param n The size of keystream to return (in octets).
       * \return A bit_vector containing the keystream content.
       */
      virtual type::bit_vector keystream(size_t n) = 0;

   protected:

      /**
       * cipher constructor.
       */
      cipher(uint8_t algid, uint16_t keyid);

   private:

      /**
       * The algorithm ID.
       */
      uint8_t d_algid;

      /**
       *  The key ID.
       */
      uint16_t d_keyid;

   };

}

#endif /* INCLUDED_CAI_CIPHER_H */
