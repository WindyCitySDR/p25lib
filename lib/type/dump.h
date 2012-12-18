/* -*- mode: C++; tab-width: 3; -*- */

/*
 * Copyright 2010 Steve Glass
 * 
 * This file is part of OP25.
 * 
 * OP25 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * Banjax is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 */

#ifndef TYPE_DUMP_HPP
#define TYPE_DUMP_HPP

#include <boost/noncopyable.hpp>
#include <iosfwd>
#include <stdint.h>

namespace type {

   /*
    * Output operator and associated class to dumps a block of memory
    * to an ostream. The output is a human-readable representation of
    * the original data. You can change the representation to
    * octal/hex/decimal using the conventional iomanip operators.
    *
    * The expected use is:
    * 
    * <pre>os << hex << dump(size, data) << endl;</pre>
    *
    */
   class dump /* : public boost::noncopyable */ {
   public:

      /*
       * Construct a new dump.
       * \param octets_sz The number of octets to dump.
       * \param octets Non-null pointer to the data to dump.
       */
      dump(size_t octets_sz, const uint8_t *octets);

      /**
       * Write this dump to the specified ostream.
       * 
       * \param os The ostream to write to.
       * \return The modified ostream.
       */
      std::ostream& write(std::ostream& os) const;

   private:

      /**
       * The size of the dump.
       */
      size_t octets_sz_;

      /**
       * The actual memory.
       */
      const uint8_t *octets_;

   };

	/**
    * iostream output operator to allow dump objects to be written
    * using the normal infix '<<' notation.
    *
    * \param os The ostream to write to.
    * \return A reference to the modified ostream object.
    */
   inline std::ostream&
   operator<<(std::ostream& os, const type::dump& d)
   {
      return d.write(os);
   }

}

#endif /* TYPE_DUMP_HPP */
