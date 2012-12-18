/* -*- mode: C++ -*- */

/*
 * Copyright 2008-2011 Steve Glass
 * Copyright 2010 KA1RBI
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

#ifndef INCLUDED_DATA_UNIT_ASSEMBLER_H
#define INCLUDED_DATA_UNIT_ASSEMBLER_H

#include <stdint.h>
#include <type/bit_vector.h>
#include <boost/noncopyable.hpp>
#include <cai/data_unit.h>

namespace CAI 
{

	/**
    * data_unit_assembler is a concrete class that constructs P25
    * data_units from a stream of dibit symbols.
    */
   class data_unit_assembler : public boost::noncopyable
   {
   public:

      /**
       * data_unit_assembler default constructor.
       */
      data_unit_assembler();

      /**
       * data_unit_assembler destructor.
       */
      ~data_unit_assembler();

      /**
       * Process a received symbol and emit a pointer to the data_unit
       * if that symbol completes a data_unit. The FS denotes the
       * beginning of the frame and, once recognized, the NID is read
       * and an appropriate number of bits read until the data_unit is
       * complete. When a symbol completes a data_unit that object is
       * returned to the caller and the search for the next FS
       * commences.
       * 
       * \param dibit A two bit symbol received from the lower layers
       * \return A (possibly NULL) data_unit_sptr pointing to the new
       * data_unit.
       */
      data_unit_sptr receive_symbol(uint8_t dibit);

#if 0

      /* ToDo? */

      /**
       * Return the number of symbols received by this object.
       */
      uint_least32_t nof_symbols_received() const;

      /**
       * Return the number of symbols ignored by this object.
       */
      uint_least32_t nof_symbols_ignored() const;

      /**
       * Return the number of symbols processed by this object.
       */
      uint_least32_t nof_symbols_processed() const;

#endif

   private:

      /**
       * Tests whether d_frame_header correlates with the APCO P25
       * frame sync sequence. This method must only be called when the
       * frame header is larger than 48 bits in length (the minimum
       * size for the FS).
       *
       * \return true if the frame header correlates; otherwise false.
       */
      bool correlated();

      /**
       * Tests whether d_frame_header identifies a known data unit and
       * if so sets d_data_unit to point to an appropriate instance
       * and returns a pointer to it. This method must only be called
       * when the frame header is larger than 114 bits in length (the
       * minimum size for a frame containing a NID).
       *
       * \return A data_unit_sptr pointing to an appropriate data_unit
       * instance or NULL if the frame header is unrecognized.
       */
      data_unit_sptr identified() const;

   private:

      uint_least32_t nof_symbols_received_;
      uint_least32_t nof_symbols_ignored_;
      bit_vector frame_body_;
      uint32_t max_frame_size_;
   };

}

#endif /* INCLUDED_DATA_UNIT_ASSEMBLER_H */
