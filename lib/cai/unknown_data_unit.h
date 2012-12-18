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

#ifndef INCLUDED_CAI_UNKNOWN_DATA_UNIT_H
#define INCLUDED_CAI_UNKNOWN_DATA_UNIT_H

#include <cai/abstract_data_unit.h>

namespace CAI
{

   /**
    * P25 header data unit (UNKNOWN_DATA_UNIT).
    */
   class unknown_data_unit : public abstract_data_unit
   {

   public:

      /**
       * unknown_data_unit constructor.
       *
       * \param frame_body A const bit_vector representing the frame body.
       */
      explicit unknown_data_unit(const type::bit_vector& frame_body);

      /**
       * unknown_data_unit virtual destructor.
       */
      virtual ~unknown_data_unit();

      /**
       * Dispatch this data_unit to the specified
       * data_unit_handler. This is a double-dispatch to allow for
       * data_unit handlers specialized on the data_unit subtype.
       *
       * \param handler A reference to a data_unit_handler.
       * \param du Shared pointer to this data_unit instance.
       */
      virtual void dispatch(class data_unit_handler& handler, data_unit_sptr du);

   };

   /**
    * Synonym for shared_ptr<unknown_data_unit>.
    */
   typedef boost::shared_ptr<unknown_data_unit> unknown_data_unit_sptr;

}

#endif /* INCLUDED_CAI_UNKNOWN_DATA_UNIT_H */
