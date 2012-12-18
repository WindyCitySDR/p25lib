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

#ifndef INCLUDED_CAI_TDU_WITH_LINK_CONTROL_H
#define INCLUDED_CAI_TDU_WITH_LINK_CONTROL_H

#include <cai/abstract_data_unit.h>

namespace CAI
{

   /**
    * P25 terminator data unit (TDU_WITH_LINK_CONTROL).
    */
   class tdu_with_link_control : public abstract_data_unit
   {
   public:

      /**
       * tdu_with_link_control constructor.
       *
       * \param frame_body A const bit_vector representing the frame body.
       */
      explicit tdu_with_link_control(const type::bit_vector& frame_body);

      /**
       * tdu_with_link_control destructor.
       */
      virtual ~tdu_with_link_control();

      /**
       * Applies error correction to this frame.
       */
      virtual void correct_errors();

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
    * Synonym for shared_ptr<tdu_with_link_control>.
    */
   typedef boost::shared_ptr<tdu_with_link_control> tdu_with_link_control_sptr;
}

#endif /* INCLUDED_CAI_TDU_WITH_LINK_CONTROL_H */
