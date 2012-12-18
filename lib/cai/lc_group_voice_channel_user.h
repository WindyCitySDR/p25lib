/* -*- mode: C++ -*- */

/*
 * Copyright 2010 Steve Glass
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

#ifndef INCLUDED_LC_GROUP_VOICE_CHANNEL_USER_H
#define INCLUDED_LC_GROUP_VOICE_CHANNEL_USER_H

#include <cai/link_control.h>

namespace CAI
{

   /**
    * P25 link control (LC) "voice channel user" message. Interface to
    * various types of information that might accompany a voice frame.
    */
   class lc_group_voice_channel_user : public link_control
   {
   public:

      /**
       * P25 lc_group_voice_channel_user (LC) constructor.
       *
       * \param bits A uint64_t containing the raw link_control word.
       */
      explicit lc_group_voice_channel_user(uint64_t bits);

      /**
       * Take a snapshot of the key fields from this frame.
       * 
       * \param s A reference to the snapshot to populate.
       * \return A reference to the populated snapshot.
       */
      virtual type::snapshot& take_snapshot(type::snapshot& s) const;

      // accessors specific to lc_group_voice_channel_user

      /**
       * Return the 16 bit group address.
       *
       * \param A uint16_t containing the group address.
       */
      virtual uint16_t group_address() const;

      /**
       * Return the 8 bit service options field.
       *
       * \return An 8 bit value containing the service options.
       */
      virtual uint8_t service_options() const;

      /**
       * Return the 32 bit source address.
       *
       * \return A uint32_t containing the source address.
       */
      virtual uint32_t source_address() const;

   };

}

#endif /* INCLUDED_LC_GROUP_VOICE_CHANNEL_USER_H */
