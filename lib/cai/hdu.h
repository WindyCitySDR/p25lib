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

#ifndef INCLUDED_CAI_HDU_H
#define INCLUDED_CAI_HDU_H

#include <cai/abstract_data_unit.h>
#include <cai/message_indicator.h>

namespace CAI
{

   /**
    * P25 header data unit (HDU).
    */
   class hdu : public abstract_data_unit
   {

   public:

      /**
       * hdu constructor.
       *
       * \param frame_body A const bit_vector representing the frame body.
       */
      explicit hdu(const type::bit_vector& frame_body);

      /**
       * hdu virtual destructor.
       */
      virtual ~hdu();

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
       * Returns the required size (in bits) of this data unit. This
       * static method must be implemented for all fixed-length data
       * units.
       *
       * \return The expected size (in bits) of this data_unit.
       */
      static uint16_t reqd_frame_size();

      /**
       * Take a snapshot of the key fields from this frame.
       * 
       * \param s A reference to the snapshot to populate.
       * \return A reference to the populated snapshot.
       */
      virtual type::snapshot& take_snapshot(type::snapshot& s) const;

      // Accessors specific to the HDU

      /**
       * Return the encryption algorithm ID (ALGID).
       *
       * \return A uint8_t identifying the ALGID.
       */
      virtual uint8_t algid() const;

      /**
       * Sets the encryption algorithm ID (ALGID).
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
      virtual void kid(uint16_t);

      /**
       * Returns a uint8_t identifying the manufacturer ID (MFID).
       *
       * \return A uint8_t identifying the manufacturer.
       */
      virtual uint8_t mfid() const;

      /**
       * Sets the manufacturer ID (MFID).
       *
       * \param A uint8_t identifying the manufacturer.
       */
      virtual void mfid(uint8_t mfid);

      /**
       * Returns the message indicator (MI).
       *
       * \return An MI specifying the message indicator.
       */
      virtual MI mi() const;

      /**
       * Sets the message indicator (MI).
       *
       * \param An MI specifying the message indicator.
       */
      virtual void mi(MI);

      /**
       * Returns the talk group id (TGID).
       *
       * \return A uint16_t identifying the TGID.
       */
      virtual uint16_t tgid() const;

      /**
       * Returns the talk group id (TGID).
       *
       * \return A uint16_t identifying the TGID.
       */
      virtual void tgid(uint16_t tgid);

   private:

      /**
       * Apply shortened Golay(18,6,8) forward error-correction to
       * this HDU.
       */
      virtual void apply_golay_FEC();

      /**
       * Compute the shortened Golay(18,6,8) forward error-correction
       * bits for this HDU.
       */
      virtual void compute_golay_FEC();

      /**
       * Apply RS(36,20,17) forward error-correction to this HDU.
       */
      virtual void apply_RS_FEC();

      /**
       * Compute the RS(36,20,17) forward error-correction bits for this HDU.
       */
      virtual void compute_RS_FEC();

   };

   /**
    * A shared_ptr<hdu> typedef.
    */
   typedef boost::shared_ptr<hdu> hdu_sptr;

}

#endif /* INCLUDED_CAI_HDU_H */
