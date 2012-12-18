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

#ifndef INCLUDED_CAI_VOICE_DATA_UNIT_H
#define INCLUDED_CAI_VOICE_DATA_UNIT_H

#include <cai/abstract_data_unit.h>

namespace CAI
{
   /**
    * 144 bit IMBE voice codeword.
    */
   typedef type::bit_vector voice_codeword;

	/**
    * Abstract data_unit for compressed IBME voice frames.
    */
   class voice_data_unit : public abstract_data_unit
   {
   public:

      /**
       * voice_data_unit (virtual) destuctor
       */
      virtual ~voice_data_unit();

      /**
       * Apply forward error-correction to this data_unit.
       */
      virtual void apply_FEC();

      /**
       * Compute the forward error-correction bits for this data_unit.
       */
      virtual void compute_FEC();

      /**
       * Returns the required size (in bits) of this data unit. This
       * static method must be implemented for all fixed-length data
       * units.
       *
       * \return The expected size (in bits) of this data_unit.
       */
      static uint16_t reqd_frame_size();

      // field accessors

      /**
       * Returns the specified 88-bit voice codeword. This
       * representation returns only the data bits used by IMBE and
       * does not return any of the FEC parity bits.
       *
       * \param n The index of the codeword to return.
       * \return The specified voice_codeword.
       */
      voice_codeword short_codeword(size_t n) const;

      /**
       * Sets the specified voice codeword. This representation sets
       * only the data bits used by IMBE and does not modify any of
       * the FEC parity bits.
       *
       * \param n The index of the codeword to modify.
       * \param cw The voice_codeword value to set.
       */
      void short_codeword(size_t n, const voice_codeword& cw);

      /**
       * Returns the specified 144-bit voice codeword. This
       * representation returns both the data and FEC parity bits.
       *
       * \param n The index of the codeword to return.
       * \return The specified voice_codeword.
       */
      voice_codeword long_codeword(size_t n) const;

      /**
       * Sets the specified voice codeword.
       *
       * \param n The index of the codeword to modify.
       * \param cw The voice_codeword value to set.
       */
      void long_codeword(size_t n, const voice_codeword& cw);

      /**
       * Returns the low-speed data attached to this frame.
       *
       * \returns A uint16_t containing the low-speed data.
       */
      uint16_t low_speed_data() const;

      /**
       * Sets the low-speed data attached to this frame.
       *
       * \param lsd A uint16_t containing the low-speed data.
       */
      void low_speed_data(uint16_t lsd);

   protected:

      /**
       * voice_data_unit constuctor
       *
       * \param frame_body A const bit_vector representing the frame body.
       */
      explicit voice_data_unit(const type::bit_vector& frame_body);

   private:

      /**
       * Apply Golay(23,12,7) forward error-correction to this
       * voice_data_unit.
       */
      void apply_golay_FEC();

      /**
       * Compute the Golay(23,12,7) forward error-correction bits for
       * this voice_data_unit.
       */
      void compute_golay_FEC();

      /**
       * Apply Hamming(15,11,3) forward error-correction to this
       * voice_data_unit. This Hamming code is applied to the
       * voice traffic.
       */
      void apply_hamming_FEC();

      /**
       * Compute the Hamming(15,11,3) forward error-correction bits
       * for this voice_data_unit. This Hamming code is computed for
       * the non-voice traffic.
       */
      void compute_hamming_FEC();

      /**
       * Apply shortened Hamming(10,6,3) forward error-correction to this
       * voice_data_unit. This Hamming code is applied to the
       * non-voice traffic and should be applied before the concrete
       * data_unit has computed any necessary FEC parity.
       */
      void apply_short_hamming_FEC();

      /**
       * Compute the Hamming(10,6,3) forward error-correction bits
       * for this voice_data_unit. This Hamming code is computed for
       * the non-voice traffic and should be called after the concrete
       * data_unit has computed any necessary FEC parity.
       */
      void compute_short_hamming_FEC();

      /**
       * Applies the (16,8,5) cyclic code to this voice_data_unit
       */
      void apply_cyclic_code();

      /**
       * Computes the (16,8,5) cyclic code to this voice_data_unit
       */
      void compute_cyclic_code();

   };

   /**
    * Alias for shared_ptr<voice_data_unit>.
    */
   typedef boost::shared_ptr<voice_data_unit> voice_data_unit_sptr;

}

#endif /* INCLUDED_CAI_VOICE_DATA_UNIT_H */
