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

#ifndef INCLUDED_TYPE_MAPPING_H
#define INCLUDED_TYPE_MAPPING_H

#include <map>
#include <stdint.h>
#include <string>

namespace type {

   /**
    * We'll switch this type to unordered_map<K,V> once g++ supports
    * uniform initialization.
    */
   typedef std::map<uint16_t, std::string> mapping;

   /**
    * Look up a value from a mapping. If a match is found that is
    * returned otherwise a string of the form "Unknown (%x)" is
    * returned.
    *
    * \param mapping The mapping to query.
    * \param value The value to look up.
    * \return The string associated witht the value.
    */
   std::string lookup(const mapping& mapping, uint16_t value);

}

#endif // INCLUDED_TYPE_MAPPING_H
