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

#ifndef INCLUDED_CUTLASS_H
#define INCLUDED_CUTLASS_H

#include <cai/data_unit_handler.h>

/**
 * Cutlass is a data_unit_handler used to analyze traffic.
 */
class cutlass : public CAI::data_unit_handler
{

public:

   /**
    * cutlass default constructor.
    */
   cutlass();

   /**
    * data_unit_handler virtual destructor.
    */
   virtual ~cutlass();

   /**
    * Called for every data_unit being handled.
    *
    * \param du A non-null data_unit_sptr.
    */
   void dispatch(CAI::data_unit_sptr du);
   
   /**
    * Handle a hdu instance.
    *
    * \param du A shared_ptr<hdu> pointing to the HDU..
    */
   virtual void handle(CAI::hdu_sptr du);

   /**
    * Handle a ldu1 instance.
    *
    * \param du A shared_ptr<ldu1> pointing to the LDU1.
    */
   virtual void handle(CAI::ldu1_sptr du);

   /**
    * Handle a ldu2 instance.
    *
    * \param du A shared_ptr<ldu2> pointing to the LDU2.
    */
   virtual void handle(CAI::ldu2_sptr du);

   /**
    * Handle a tdu instance.
    *
    * \param du A shared_ptr<tdu> pointing to the TDU.
    */
   virtual void handle(CAI::tdu_sptr du);

   /**
    * Handle a tdu_with_link_control instance.
    *
    * \param du A shared_ptr<tdu_with_link_control> pointing to the TDU.
    */
   virtual void handle(CAI::tdu_with_link_control_sptr du);

private:

   /**
    * Called to cut last frame of an exchange.
    *
    * \param mi The MI for this superframe.
    * \param algid The ALGID for this superframe.
    * \param kid The KID used for this superframe.
    * \param du Smart pointer to the final voice_data_unit.
    */
   void cut_last(const CAI::MI& mi, uint8_t algid, uint16_t kid, CAI::voice_data_unit_sptr du);

   uint32_t pngen15(uint32_t &pn);
   uint32_t pngen23(uint32_t &pn);
   CAI::voice_codeword decode(const CAI::voice_codeword& cw);

private:

   /**
    * The number of the frame (to assist in finding frames in Wireshark).
    */
   size_t d_frame_no;

   /**
    * States used to identify traffic.
    */
   enum { SKIP, SYNC, RECV1, RECV2 } d_state;

   /**
    * Reference to the MI currently being used.
    */
   CAI::MI d_mi;

   /**
    * The encryption algorithm ID.
    */
   uint8_t d_algid;

   /**
    * They key ID.
    */
   uint16_t d_kid;

   /**
    * The last LDU1 frame.
    */
   CAI::ldu1_sptr d_ldu1;

   /**
    * The last LDU1 frame.
    */
   CAI::ldu2_sptr d_ldu2;

};

#endif /* INCLUDED_CUTLASS_H */
