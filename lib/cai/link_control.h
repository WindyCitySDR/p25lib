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

#ifndef INCLUDED_LINK_CONTROL_H
#define INCLUDED_LINK_CONTROL_H

#include <type/bit_vector.h>
#include <type/snapshot.h>

#include <boost/shared_ptr.hpp>

namespace CAI
{

   /**
    * link_control_sptr is an alias for boost::shared_ptr<link_control>.
    */
   typedef boost::shared_ptr<class link_control> link_control_sptr;

   /**
    * P25 link control (LC). Interface to various types of information
    * about how to handle a message.
    */
   class link_control
   {
   public:

      /**
       * Create an appropriate link_control object.
       *
       * \param bits A uint64_t specifying the raw bits of this link_control word.
       */
      static link_control_sptr create(uint64_t bits);

      /**
       * link_control (virtual) destructor.
       */
      virtual ~link_control();

      /**
       * Conversion to uint64_t.
       */
      operator uint64_t() const;

      /**
       * Take a snapshot of the key fields from this frame.
       * 
       * \param s A reference to the snapshot to populate.
       * \return A reference to the populated snapshot.
       */
      virtual type::snapshot& take_snapshot(type::snapshot& s) const;

   protected:

      /**
       * P25 link_control (LC) constructor.
       *
       * \param bits A uint64_t specifying the raw bits of this link_control word..
       */
      explicit link_control(uint64_t bits);

      /**
       * Return the raw bits that make up this link_control word.
       *
       * \return A const reference to a bit_vector.
       */
      const type::bit_vector bits() const;

   private:

      /**
       * The bits representing the link_control word.
       */
      type::bit_vector d_bits;

   };

}

#endif /* INCLUDED_LINK_CONTROL_H */
