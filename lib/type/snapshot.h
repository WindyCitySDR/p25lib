/* -*- mode: C++ -*- */

/*
 * Copyright 2008, 2009 Steve Glass
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

#ifndef INCLUDED_TYPE_SNAPSHOT_H
#define INCLUDED_TYPE_SNAPSHOT_H

#include <map>
#include <stdint.h> 
#include <string>

namespace type
{

   /**
   * A self-describing snapshot of the key fields in an object.
   * Concrete subclasses provide a means of accessing the snapshot
   * in different formats.
   */
   class snapshot
   {

   public:

      /**
       * snapshot virtual destructor.
       */
      virtual ~snapshot();

      /**
       * Add a key/string value pair to the snapshot dictionary
       *
       * \param key The attribute name.
       * \param value The attribute's value.
       */
      virtual void add(std::string key, std::string value);

      /**
       * Adds a key/integer value pair to the snapshot dictionary
       *
       * \param key The attribute name.
       * \param value The attribute's value.
       */
      virtual void add(std::string key, uint64_t value);

      /**
       * Returns this snapshot as a string.
       *
       * \return A string representation of the snapshot.
       */
      virtual std::string to_string() const = 0;

   protected:

      /**
       * snapshot constructor.
       */
      snapshot();

   protected:

      typedef std::map<std::string, std::string> stringmap;

      /**
       * A map of attribute names/values.
       */
      stringmap map_;

   };

}

#endif /* INCLUDED_TYPE_SNAPSHOT_H */
