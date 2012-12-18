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

#ifndef INCLUDED_CAI_ABSTRACT_DATA_UNIT_H
#define INCLUDED_CAI_ABSTRACT_DATA_UNIT_H

#include <cai/data_unit.h>

namespace CAI
{

   /**
    * Abstract P25 data unit.
    */
   class abstract_data_unit : public data_unit
   {

   public:

      /**
       * abstract data_unit virtual destructor.
       */
      virtual ~abstract_data_unit();

      /**
       * Apply forward error-correction to this data_unit.
       */
      virtual void apply_FEC();

      /**
       * Compute the forward error-correction bits for this data_unit.
       */
      virtual void compute_FEC();

      /**
       * Return a reference to the frame body.
       */
      virtual const type::bit_vector& frame_body() const;

      /**
       * Return the frame contents packed into an octet vector.
       *
       * \return The frame encoded as an octet vector.
       */
      virtual std::vector<uint8_t> pack() const;

      /**
       * Take a snapshot of the key fields from this frame.
       * 
       * \param s A reference to the snapshot to populate.
       * \return A reference to the populated snapshot.
       */
      virtual type::snapshot& take_snapshot(type::snapshot& s) const;

      /**
       * Writes this object in human-readable form onto the supplied
       * stream. Dumps are formatted as per the P25 conformance spec.
       *
       * \param os The ostream to write to.
       */
      virtual void write(std::ostream& os) const;

      // field accessors

      /**
       * Returns the Framing Sequence (FS). The FS is 48 bits and 
       * occupies the low order 48 bits of the returned value.
       *
       * \return A uint64_t containing the FS.
       */
      virtual uint64_t FS() const;

      /**
       * Sets the Framing Sequence (FS).
       *
       * \param fs A uint64_t containing the new FS.
       */
      virtual void FS(uint64_t fs);

      /**
       * Returns the Network ID (NID). This is a 16 bit value which
       * concatenates the NAC and DUID.
       *
       * \return A uint16_t containing the NID.
       */
      virtual uint16_t NID() const;

      /**
       * Returns the Network ID (NID). This is a 16 bit value which
       * concatenates the NAC and DUID.
       *
       * \return A uint16_t containing the NID.
       */
      virtual void NID(uint16_t nid);

      /**
       * Returns the Data Unit ID (DUID). The DUID is 4 bits and
       * occupies the low-order 4 bits of the returned value.
       *
       * \return A uint8_t identifying the DUID.
       */
      virtual uint8_t DUID() const;

      /**
       * Sets the Data Unit ID (DUID).
       *
       * \param duid A uint8_t specifying the DUID.
       */
      virtual void DUID(uint8_t duid);

      /**
       * Returns the Network Access Code (NAC). The NAC is 12 bits in
       * length and occupies the low-order 12 bits of the returned
       * value.
       *
       * \return A uint16_t identifying the NAC.
       */
      virtual uint16_t NAC() const;

      /**
       * Sets the Network Access Code (NAC).
       *
       * \param nacA uint16_t identifying the NAC.
       */
      virtual void NAC(uint16_t nac);

      /**
       * Returns the Status Symbols (SS) from this frame.
       *
       * \return A vector of status_symbol values.
       */
      virtual std::vector<status_symbol> SS() const;

      /**
       * Sets the Status Symbols (SS) for this frame.
       *
       * \param ss A vector of status_symbol values.
       */
      virtual void SS(const std::vector<status_symbol>& ss);

   protected:

      /**
       * abstract_data_unit constructor. Used to construct an
       * abstract_data_unit in an empty state.
       *
       * \param n The size of this abstract_data_unit.
       */
      explicit abstract_data_unit(size_t n);

      /**
       * abstract_data_unit constructor. Used to construct an
       * abstract_data_unit from a bit string.
       *
       * \param frame_body A const reference to the frame body.
       */
      explicit abstract_data_unit(const type::bit_vector& frame_body);

      /**
       * Return a reference to the frame body.
       */
      type::bit_vector& frame_body();

      /**
       * Tests whether the symbol at bit index i is used by a status
       * symbol. As all status symbols fall on even boundaries this
       * will throw an invalid_argument exception for odd indices.
       *
       * \param i The index of the bit position to test.
       * \return true if i indexes a status symbol; otherwise false.
       */
      bool is_status_symbol(size_t i) const;

   private:

      /**
       * A bit vector representing the frame body.
       */
      type::bit_vector frame_body_;

   private:

      /**
       * The size (in bits) of a single status symbol.
       */
      static const size_t SS_SZ_;

      /**
       * The distance (in bits) between successive status symbols.
       */
      static const size_t SS_INTERVAL_;

   };

}

#endif /* INCLUDED_CAI_ABSTRACT_DATA_UNIT_H */
