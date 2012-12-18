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

#ifndef INCLUDED_CAI_DATA_UNIT_H
#define INCLUDED_CAI_DATA_UNIT_H

#include <type/bit_vector.h>
#include <type/snapshot.h>

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <iosfwd>
#include <stdint.h>
#include <vector>

namespace CAI
{

   /**
    * Status symbols.
    */
   enum status_symbol {
      TALKAROUND = 0x00,
      BUSY       = 0x01,
      UNKNOWN    = 0x02,
      IDLE       = 0x03
   };

   /**
    * Synonym for shared_ptr<data_unit>.
    */
   typedef boost::shared_ptr<class data_unit> data_unit_sptr;

   /**
    * An APCO P25 data unit. The data_unit is responsible for forward
    * error correction and field access/data interleaving and provides
    * accessors for taking snapshots or dumping the frame to an output
    * stream.
    */
   class data_unit : public boost::noncopyable
   {
   public:

      /**
       * Virtual data_unit constructor. Given a frame body constructs
       * a frame of the appropriate type. Throws an invalid_argument
       * exception when the DUID is of an unknown type; length_error
       * when the frame_body is either too long or too short.
       *
       * \param octets_sz The size of the frame.
       * \param octets Pointer to the content of the frame.
       * \return A reference to the data_unit.
       */
      static data_unit_sptr create(size_t octets_sz, const uint8_t *octets);

      /**
       * Virtual data_unit constructor. Given a frame body constructs
       * a frame of the appropriate type. Throws an invalid_argument
       * exception when the DUID is of an unknown type; length_error
       * when the frame_body is either too long or too short.
       *
       * \param frame_body The content of the frame.
       * \return A reference to the data_unit.
       */
      static data_unit_sptr create(const type::bit_vector& frame_body);

      /**
       * data_unit (virtual) destructor.
       */
      virtual ~data_unit();

      /**
       * Apply forward error-correction to this data_unit.
       */
      virtual void apply_FEC() = 0;

      /**
       * Compute forward error-correction parity bits for this data_unit.
       */
      virtual void compute_FEC() = 0;

      /**
       * Dispatch this data_unit to the specified
       * data_unit_handler. This is a double-dispatch to allow for
       * data_unit handlers specialized on the data_unit subtype.
       *
       * \param handler A reference to a data_unit_handler.
       */
      virtual void dispatch(class data_unit_handler& handler) = 0;

      /**
       * Return a reference to the frame body.
       */
      virtual const type::bit_vector& frame_body() const = 0;

      /**
       * Return the frame contents packed into an octet vector.
       *
       * \return The frame encoded as an octet vector.
       */
      virtual std::vector<uint8_t> pack() const = 0;

      /**
       * Take a snapshot of the key fields from this frame.
       * 
       * \param s A reference to the snapshot to populate.
       * \return A reference to the populated snapshot.
       */
      virtual type::snapshot& take_snapshot(type::snapshot& s) const = 0;

      /**
       * Writes this object in human-readable form onto the supplied
       * stream. The output is formatted as per the conformance spec
       * guide.
       *
       * \param os The ostream to write to.
       */
      virtual void write(std::ostream& os) const = 0;

      // field accessors

      /**
       * Returns the Framing Sequence (FS). The FS is 48 bits and 
       * occupies the low order 48 bits of the returned value.
       */
      virtual uint64_t FS() const = 0;

      /**
       * Sets the Framing Sequence (FS).
       */
      virtual void FS(uint64_t) = 0;

      /**
       * Returns the Network ID (NID). This is a 16 bit value which
       * concatenates the NAC and DUID.
       *
       * \return A uint16_t containing the NID.
       */
      virtual uint16_t NID() const = 0;

      /**
       * Returns the Network ID (NID). This is a 16 bit value which
       * concatenates the NAC and DUID.
       *
       * \return A uint16_t containing the NID.
       */
      virtual void NID(uint16_t nid) = 0;

      /**
       * Returns the Data Unit ID (DUID). Note that the DUID
       * identifies the frame type and, therefore, cannot be changed.
       *
       * \return A uint8_t identifying the DUID.
       */
      virtual uint8_t DUID() const = 0;

      /**
       * Returns the Network Access Code (NAC).
       *
       * \return A uint16_t identifying the NAC.
       */
      virtual uint16_t NAC() const = 0;

      /**
       * Sets the Network Access Code (NAC).
       *
       * \param nacA uint16_t identifying the NAC.
       */
      virtual void NAC(uint16_t nac) = 0;

      /**
       * Returns the Status Symbols (SS) from this frame.
       *
       * \return A vector of status_symbol values.
       */
      virtual std::vector<status_symbol> SS() const = 0;

      /**
       * Sets the Status Symbols (SS) for this frame.
       *
       * \param ss A vector of status_symbol values.
       */
      virtual void SS(const std::vector<status_symbol>& ss) = 0;

   protected:

      /**
       * data_unit default constructor.
       */
      data_unit();

   };

	/**
    * iostream output operator to allow data_unit objects to be written
    * using the normal infix '<<' notation.
    *
    * \param os The ostream to write to.
    * \param d The data_unit to be written.
    * \return A reference to the modified ostream object.
    */
   inline std::ostream&
   operator<<(std::ostream& os, const data_unit& d)
   {
      d.write(os);
      return os;
   }

}

#endif /* INCLUDED_CAI_DATA_UNIT_H */
