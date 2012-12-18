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

#ifndef INCLUDED_CAI_LDU2_H
#define INCLUDED_CAI_LDU2_H

#include <cai/voice_data_unit.h>
#include <cai/message_indicator.h>

namespace CAI
{

   /**
    * P25 Logical Data Unit 2.
    */
   class ldu2 : public voice_data_unit
   {
   public:
      /**
       * ldu2 constructor.
       *
       * \param frame_body A const bit_vector representing the frame body.
       */
      explicit ldu2(const type::bit_vector& frame_body);

      /**
       * ldu2 (virtual) destructor.
       */
      virtual ~ldu2();


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
       * Return the encryption algorithm ID (ALGID).
       *
       * \return A uint8_t identifying the ALGID.
       */
      virtual uint8_t algid() const;

      /**
       * Set the encryption algorithm ID (ALGID).
       *
       * \param A uint8_t identifying the ALGID.
       */
      virtual void algid(uint8_t algid);

      /**
       * Returns the key id (KID).
       *
       * \return A uint16_t identifying the KID.
       */
      virtual uint16_t kid() const;

      /**
       * Sets the key id (KID).
       *
       * \param A uint16_t identifying the KID.
       */
      virtual void kid(uint16_t kid);

      /**
       * Returns the message indicator (MI).
       *
       * \return An MI specifying the message indicator.
       */
      virtual MI mi() const;

      /**
       * Sets the message indicator (MI).
       *
       * \para,m An MI specifying the message indicator.
       */
      virtual void mi(MI mi);

   private:

      /**
       * Apply shortened RS(24,16,9) forward error-correction to the
       * non-voice payload.
       */
      void apply_RS_FEC();

      /**
       * Compute the shortened RS(24,16,9) forward error-correction
       * bits to the non-voice payload.
       */
      void compute_RS_FEC();

   };

   /**
    * Synonym for shared_ptr<ldu2>.
    */
   typedef boost::shared_ptr<ldu2> ldu2_sptr;

}

#endif /* INCLUDED_CAI_LDU2_H */
