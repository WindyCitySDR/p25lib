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

#ifndef INCLUDED_TYPE_ASSERTIONS_H
#define INCLUDED_TYPE_ASSERTIONS_H

#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace type
{

   /**
    * Raise an exception of type T with the given error message.
    *
    * \param func The name of the function in error.
    * \param file The name of the file.
    * \param line The line number where the error originated.
    * \param text A string describing the error.
    */
   template<class T>
      void raise(const char *func, const char *file, int line, std::string text) {
      std::ostringstream msg;
      msg << "Error: " << text << std::endl;
      msg << " Func: " << func << std::endl;
      msg << " File: " << file << std::endl;
      msg << " Line: " << line << std::endl << std::endl;
      throw T(msg.str());
   }

}

#define CHECK_MIN_SIZE(ACTUAL, MIN) \
   if(ACTUAL < MIN) { \
      std::ostringstream text; \
      text << "value " << ACTUAL << " is less than the expected minimum value " << MIN << std::endl; \
      type::raise<std::length_error>(__PRETTY_FUNCTION__, __FILE__, __LINE__, text.str()); \
   }

#define CHECK_MAX_SIZE(ACTUAL, MAX) \
   if(ACTUAL > MAX) { \
      std::ostringstream text; \
      text << "value " << ACTUAL << " exceeds the expected maximum value " << MAX << std::endl; \
      type::raise<std::length_error>(__PRETTY_FUNCTION__, __FILE__, __LINE__, text.str()); \
   }

#define CHECK_NOT_NULL(P) \
   if(NULL == P) { \
      type::raise<std::invalid_argument>(__PRETTY_FUNCTION__, __FILE__, __LINE__, "NULL pointer"); \
   }

#define CHECK_RANGE(MIN,VALUE,MAX) \
   if(!((MIN <= VALUE) && (VALUE < MAX))) { \
      std::ostringstream text; \
      text << "value " << VALUE << "outside valid range " << MIN << " <= x < " << MAX << std::endl; \
      type::raise<std::out_of_range>(__PRETTY_FUNCTION__, __FILE__, __LINE__, text.str()); \
   }

#define CHECK_SIZE(ACTUAL_SZ, EXPECTED_SZ) \
   if(ACTUAL_SZ != EXPECTED_SZ) { \
      std::ostringstream text; \
      text << "size " << ACTUAL_SZ << " is not the expected size " << EXPECTED_SZ << std::endl; \
      type::raise<std::length_error>(__PRETTY_FUNCTION__, __FILE__, __LINE__, text.str()); \
   }

#if 0

#define CHECK_SIZE_BUFFER(ACTUAL_SZ, EXPECTED_SZ, BUFFER) \
   if(ACTUAL_SZ != EXPECTED_SZ) { \
      std::ostringstream text; \
      text << "size " << ACTUAL << " is not the expected size " << EXPECTED << std::endl; \
      text << type::dump(ACTUAL_SZ, buffer) << std::endl;               \
      type::raise<std::length_error>(__PRETTY_FUNCTION__, __FILE__, __LINE__, text.str()); \
   }

#endif

#endif /* INCLUDED_TYPE_ASSERTIONS_H */
