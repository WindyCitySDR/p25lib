/* -*- mode: C++ -*- */

/*
 * Copyright 2008 Steve Glass
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

#ifndef INCLUDED_TYPE_SIMPLE_SNAPSHOT_H
#define INCLUDED_TYPE_SIMPLE_SNAPSHOT_H

#include <type/snapshot.h>

namespace type
{

   /**
   * A self-describing snapshot of the key fields in an object which
   * can be used for debugging purposes.
   */
   class simple_snapshot : public snapshot
   {

   public:

      /**
       * simple_snapshot constructor.
       */
      simple_snapshot();

      /**
       * Returns this snapshot as a string. The format of the string
       * is a simple list of key/value pairs one per line.
       *
       * \return A string representation of the snapshot.
       */
      virtual std::string to_string() const;

   };

}

#endif /* INCLUDED_TYPE_SIMPLE_SNAPSHOT_H */
