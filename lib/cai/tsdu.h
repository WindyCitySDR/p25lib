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

#ifndef INCLUDED_CAI_TSDU_H
#define INCLUDED_CAI_TSDU_H

#include <cai/abstract_data_unit.h>

#include <vector>

namespace CAI
{

   /**
    * Trunk Signalling Block (TSBK). These are the payload present
    * in a TSDU and comprise a series of commands and requests that
    * we map using a 12 octet structure.
    */
   union tsbk {

      /**
       * raw storage
       */
      uint8_t raw[12];

      /**
       * extended function command (xfc).
       */
      struct {
         uint8_t opcode;
         uint8_t mfid;
         uint8_t clazz;
         uint8_t operand;
         uint8_t dst[3];
         uint8_t src[3];
         uint16_t crc;
      } __attribute__((packed)) xfc;

   } __attribute((packed));

   /**
    * P25 trunking signalling data unit (TSDU). Note that a single
    * TSDU can contain up to three TSBKs; the Danelec training guide
    * confuses TSDUs and TSBKs.
    */
   class tsdu : public abstract_data_unit
   {

   public:

      /**
       * default tsdu constructor. Used to construct a new TSDU.
       */
      tsdu();

      /**
       * tsdu constructor. Used to construct a TSDU from a bit string.
       *
       * \param frame_body A const bit_vector representing the frame body.
       */
      explicit tsdu(const type::bit_vector& frame_body);

      /**
       * tsdu virtual destructor.
       */
      virtual ~tsdu();

      /**
       * Dispatch this data_unit to the specified
       * data_unit_handler. This is a double-dispatch to allow for
       * data_unit handlers specialized on the data_unit subtype.
       *
       * \param A reference to a data_unit_handler.
       */
      virtual void dispatch(data_unit_handler& handler);

      /**
       * Returns the ISP/OSP TSBK payload of this TSDU.
       *
       * \param n The index of the block to return.
       * \return The specified TSBK.
       */
      virtual union tsbk tsbk(size_t n) const;

      /**
       * Sets the specified ISP/OSP TSBK payload for this TSDU.
       *
       * \param n The index of the block to set.
       * \param blk A const reference to a tsbk.
       */
      virtual void tsbk(size_t n, const union tsbk& blk);

      /**
       * Returns the minimum frame size (in bits) of this data unit in
       * bits.
       *
       * \return The expected size (in bits) of this data_unit when encoded.
       */
      static uint16_t reqd_frame_size();

   };

   /**
    * Synonym for shared_ptr<tsdu>.
    */
   typedef boost::shared_ptr<tsdu> tsdu_sptr;

}

#endif /* INCLUDED_CAI_TSDU_H */
