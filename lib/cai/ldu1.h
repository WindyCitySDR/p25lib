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

#ifndef INCLUDED_CAI_LDU1_H
#define INCLUDED_CAI_LDU1_H

#include <cai/voice_data_unit.h>
#include <cai/link_control.h>

namespace CAI
{

   /**
    * P25 Logical Data Unit 1.
    */
   class ldu1 : public voice_data_unit
   {
   public:

      /**
       * ldu1 constuctor
       *
       * \param frame_body A const bit_vector representing the frame body.
       */
      explicit ldu1(const type::bit_vector& frame_body);

      /**
       * ldu1 (virtual) destuctor
       */
      virtual ~ldu1();

      /**
       * Apply forward error-correction to this data_unit.
       */
      virtual void apply_FEC();

      /**
       * Compute the forward error-correction bits for this data_unit.
       */
      virtual void compute_FEC();

      /**
       * Dispatch this data_unit to the specified
       * data_unit_handler. This is a double-dispatch to allow for
       * data_unit handlers specialized on the data_unit subtype.
       *
       * \param A reference to a data_unit_handler.
       */
      virtual void dispatch(class data_unit_handler& handler);

      /**
       * Take a snapshot of the key fields from this frame.
       * 
       * \param s A reference to the snapshot to populate.
       * \return A reference to the populated snapshot.
       */
      virtual type::snapshot& take_snapshot(type::snapshot& s) const;

      // data unit specific accessors

      /**
       * Return the link_control word.
       *
       * \return A boost::shared_pointer to the link_control word.
       */
      link_control_sptr link_control_word() const;

      /**
       * Set the link_control word.
       *
       * \param A boost::shared_pointer to the link_control word.
       */
      void link_control_word(link_control_sptr lcw);

   private:

      /**
       * Apply shortened RS(24,12,13) forward error-correction to the
       * non-voice payload.
       */
      void apply_RS_FEC();

      /**
       * Compute the shortened RS(24,12,13) forward error-correction
       * bits to the non-voice payload.
       */
      void compute_RS_FEC();

   };

   /**
    * Synonym for shared_ptr<ldu1>.
    */
   typedef boost::shared_ptr<ldu1> ldu1_sptr;

}

#endif /* INCLUDED_CAI_LDU1_H */
