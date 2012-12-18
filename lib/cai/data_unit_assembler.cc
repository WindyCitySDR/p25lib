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

#include <fec/bch.h>
#include <cai/data_unit_assembler.h>

data_unit_assembler::data_unit_assembler() :
	frame_body_(114),
   state_(SYNCHRONIZING)
{
}

data_unit_assembler::~data_unit_assembler()
{
}

data_unit_sptr
data_unit_assembler::receive_symbol(dibit d)
{
	++nof_symbols_received_;
   frame_body_.push_back(d & 0x2);
   frame_body_.push_back(d & 0x1);
   const size_t frame_body__sz = frame_body_.size();

   switch(state_) {
   case SYNCHRONIZING:
      if(48 <= frame_body__sz) {
         frame_body_.erase(frame_body_.begin(), frame_body_.begin() + (frame_body__sz - 48));
         if(correlated()) {
            state = IDENTIFYING;
         }
      }
      break;
   case IDENTIFYING:
      if(114 == frame_body__sz) {
         if(identified()) {
            state = READING;
         } else {
            state = SYNCHRONIZING;
         }
      }
      break;
   case READING:
      if(data_unit->is_complete()) {
/*
  ToDo: instantiate frame here!
         data_unit->correct_errors();
         data_unit_handler->handle(data_unit);
*/
         data_unit_sptr null;
         data_unit = null;
         state = SYNCHRONIZING;
      }
      break;
   }
}

bool
op25_decoder_bf::correlated()
{
   static const bit FS[] = {
      0, 1, 0, 1,  0, 1, 0, 1,  0, 1, 1, 1,  0, 1, 0, 1, 
      1, 1, 1, 1,  0, 1, 0, 1,  1, 1, 1, 1,  1, 1, 1, 1, 
      0, 1, 1, 1,  0, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1
   };
   static const size_t FS_SZ = sizeof(FS)/sizeof(FS[0]);

   uint8_t errs = 0;
   const uint8_t ERR_THRESHOLD = 4;
   for(size_t i = 0; i < FS_SZ; ++i) {
      if(frame_body_[i] ^ FS[i]) {
         ++errs;
      }
   }
   return (errs <= ERR_THRESHOLD);
}

bool
op25_decoder_bf::identified()
{
   uint8_t duid = duid();
   if(duid != UINT8_MAX) {

      static const int MAX_FRAME_LENGTHS[16] = {
         792,                   // 0 - hdu
         -1,                    // 1 - not defined
         -1,                    // 2 - not defined
         144,                   // 3 - tdu
         -1,                    // 4 - undef
         1728,                  // 5 - ldu1
         -1,                    // 6 - not defined
         720,                   // 7 - trunking
         -1,                    // 8 - not defined
         -1,                    // 9 - pdu
         1728,                  // a - ldu2
         -1,                    // b - not defined
         792,                   // c - VSELP "voice PDU"
         -1,                    // d - not defined
         -1,                    // e - not defined
         432                    // f - tdu (with link control)
      };

   }

   return ;
}

uint8_t 
data_unit_assembler::duid() const
{
   static const size_t NID[] = {
      48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
      64, 65, 66, 67, 68, 69, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81,
      82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97,
      98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112
   };
   size_t NISZ = sizeof(NID) / sizeof(NID[0]);

   uint64_t cw = frame_body_.extract(NID, NID_SZ);
   uint16_t nid = bch_decode(cw, &nof_errs);
   return(nof_errs != UINT8_MAX ? nid >> 12 : UINT8_MAX);
}
