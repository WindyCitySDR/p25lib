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

#include <cai/tsdu.h>
#include <cai/data_unit_handler.h>
#include <fec/trellis.h>
#include <type/assertions.h>

#include <string.h>

using namespace CAI;
using namespace FEC;
using namespace type;
using std::vector;

const size_t TSDU_TSBK_SZ = sizeof(union tsbk);

tsdu::tsdu() :
   abstract_data_unit(reqd_frame_size())
{
}

tsdu::tsdu(const bit_vector& frame_body) :
   abstract_data_unit(frame_body)
{
   CHECK_SIZE(frame_body.size(), reqd_frame_size());
}

tsdu::~tsdu()
{
}

void
tsdu::dispatch(data_unit_handler& handler)
{
   handler.dispatch(*this);
}

/* Bit offset for start ofwjh each TSBK.
 *
 */
static const size_t TSBK_OFS[] = {
   114,
   316,
   518
};

/* Symbol interleaving, derived from CAI specification table 7.4
 */
static const size_t INTERLEAVING[] = {
    0, 13, 25, 37, 
    1, 14, 26, 38, 
    2, 15, 27, 39, 
    3, 16, 28, 40, 
    4, 17, 29, 41, 
    5, 18, 30, 42, 
    6, 19, 31, 43, 
    7, 20, 32, 44, 
    8, 21, 33, 45, 
    9, 22, 34, 46, 
   10, 23, 35, 47, 
   11, 24, 36, 48, 
   12 
};

#define NOF(X) (sizeof(X) / sizeof(X[0]))

union tsbk
tsdu::tsbk(size_t n) const
{
   CHECK_MAX_SIZE(n, NOF(TSBK_OFS));

   // recover symbols
   size_t p = TSBK_OFS[n];
   const uint8_t DIBIT_MASK = 0x3;
   const size_t NOF_SYMBOLS = 49;
   vector<nybble> interleaved(NOF_SYMBOLS);
   for(size_t i = 0; i < NOF_SYMBOLS; ++i) {
      interleaved[i] = frame_body().extract(p, p+2) << 2;
      p += (is_status_symbol(p + 2) ? 4 : 2);
      interleaved[i] |= frame_body().extract(p, p+2);
      p += (is_status_symbol(p + 2) ? 4 : 2);
   }

   // de-interleave
   vector<nybble> trellis_buffer(NOF_SYMBOLS);
   for(size_t i = 0; i < NOF_SYMBOLS; ++i) {
      trellis_buffer[i] = interleaved[INTERLEAVING[i]];
   }

   // trellis decode and pack into octets
   union tsbk blk;
   memset(blk.raw, 0, TSDU_TSBK_SZ);
   vector<dibit> decoded(trellis_1_2_decode(trellis_buffer));
   const size_t NOF_DIBITS = decoded.size();
   for(size_t i = 0; i < NOF_DIBITS; ++i) {
      blk.raw[i / 4] |= (decoded[i] & DIBIT_MASK) << (6 - ((i % 4) * 2));
   }
   return blk;
}

void
tsdu::tsbk(size_t n, const union tsbk& tsbk)
{
   CHECK_MAX_SIZE(n, NOF(TSBK_OFS));

   // unpack tsbk and trellis-encode
   const size_t NOF_DIBITS = 48;
   vector<dibit> unpacked(NOF_DIBITS);
   for(size_t i = 0; i < NOF_DIBITS; ++i) {
      const uint8_t DIBIT_MASK = 0x3;
      unpacked[i] = (tsbk.raw[i / 4] >> (6 - ((i % 4) * 2))) & DIBIT_MASK;
   }
   vector<nybble> encoded(trellis_1_2_encode(unpacked));

   // interleave
   const size_t NOF_SYMBOLS = encoded.size();
   vector<nybble> interleaved(NOF_SYMBOLS);
   for(size_t i = 0; i < NOF_SYMBOLS; ++i) {
      interleaved[INTERLEAVING[i]] = encoded[i];
   }

   // pack nybbles into the frame body avoiding the status symbols
   size_t p = TSBK_OFS[n];
   for(size_t i = 0; i < NOF_SYMBOLS; ++i) {
      frame_body().insert(p, p+2, (interleaved[i] >> 2) & 0x3);
      p += (is_status_symbol(p + 2) ? 4 : 2);
      frame_body().insert(p, p+2, (interleaved[i]) & 0x3);
      p += (is_status_symbol(p + 2) ? 4 : 2);
   }
}

uint16_t
tsdu::reqd_frame_size()
{
   return 720;   // ToDo: make size depend on number of TSBKs
}
