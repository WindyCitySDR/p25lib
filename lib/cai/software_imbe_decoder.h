/* -*- C++ -*- */

/*
 * Copyright 2008-2010 Steve Glass
 *
 * This file is part of OP25.
 *
 * OP25 is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or(at your option)
 * any later version.
 *
 * OP25 is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OP25; see the file COPYING. If not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Boston, MA
 * 02110-1301, USA.
 */

#ifndef INCLUDED_CAI_SOFTWARE_IMBE_DECODER_H
#define INCLUDED_CAI_SOFTWARE_IMBE_DECODER_H

#include <cai/imbe_decoder.h>

namespace CAI
{

	/**
    * A software implementation of the imbe_decoder interface.
    */
   class software_imbe_decoder : public imbe_decoder {
   public:

      /**
       * Default constructor for the software_imbe_decoder.
       */
      software_imbe_decoder();

      /**
       * Destructor for the software_imbe_decoder.
       */
      virtual ~software_imbe_decoder();

      /**
       * Decode the compressed audio.
       *
       * \cw in IMBE codeword (including parity check bits).
       */
      virtual void decode(const voice_codeword& cw);

   };

}

#endif /* INCLUDED_CAI_SOFTWARE_IMBE_DECODER_H */
