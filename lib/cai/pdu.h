/* -*- mode: C++ -*- */

/*
 * Copyright 2008-2010 Steve Glass
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

#ifndef INCLUDED_PDU_H
#define INCLUDED_PDU_H

#include <cai/abstract_data_unit.h>

namespace CAI
{

   /**
    * P25 packet data unit (PDU).
    */
   class pdu : public abstract_data_unit
   {
   public:

      /**
       * P25 packet data unit (PDU) constructor.
       *
       * \param frame_body A const bit_vector representing the frame body.
       */
      explicit pdu(const type::bit_vector& frame_body);

      /**
       * pdu (virtual) destructor.
       */
      virtual ~pdu();

      /**
       * Dispatch this data_unit to the specified
       * data_unit_handler. This is a double-dispatch to allow for
       * data_unit handlers specialized on the data_unit subtype.
       *
       * \param A reference to a data_unit_handler.
       */
      virtual void dispatch(data_unit_handler& handler);

      /**
       * Returns the required size (in bits) of this data unit. This
       * static method must be implemented for all fixed-length data
       * units.
       *
       * \return The expected size (in bits) of this data_unit.
       */
      static uint16_t reqd_frame_size();

   };

   /**
    * Synonym for shared_ptr<pdu>.
    */
   typedef boost::shared_ptr<pdu> pdu_sptr;

}

#endif /* INCLUDED_PDU_H */
