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

#ifndef INCLUDED_CAI_DATA_UNIT_HANDLER_H
#define INCLUDED_CAI_DATA_UNIT_HANDLER_H

#include <cai/data_unit.h>
#include <cai/hdu.h>
#include <cai/ldu1.h>
#include <cai/ldu2.h>
#include <cai/pdu.h>
#include <cai/tdu.h>
#include <cai/tsdu.h>
#include <cai/tdu_with_link_control.h>
#include <cai/voice_data_unit.h>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

namespace CAI
{

   /**
    * Shared pointer to a data_unit_handler.
    */
   typedef boost::shared_ptr<class data_unit_handler> data_unit_handler_sptr;

	/**
    * P25 data_unit_handler interface. This allows us to process
    * specific subtypes of data_unit using a trampoline dispatch
    * mechanism.
    */
   class data_unit_handler : public boost::noncopyable
   {
   public:

      /**
       * data_unit_handler virtual destructor.
       */
      virtual ~data_unit_handler();

      /**
       * Dispatch a P25 data_unit to a type-specific handler
       * method. This is the first step in a double dispatch used to
       * find the correct handler and calls the appropriate
       * data_unit::dispatch() implementation.
       *
       * \param du A non-null data_unit_sptr.
       */
      void dispatch(data_unit_sptr du);

      /**
       * Dispatch a P25 data_unit instance to a type-specific handler
       * method. This is the second step in a double dispatch used to
       * find the correct handler and should only be called by the
       * concrete data_unit::dispatch() implementations.
       *
       * \param du A reference to the HDU.
       */
      template<class T>
      void dispatch(T& du) {
         // ToDo compile-time enforcement of T as a data_unit subtype
         if(d_stash.get() == &du) {
            boost::shared_ptr<T> ptr(boost::dynamic_pointer_cast<T>(d_stash));
            if(ptr) {
               handle(ptr);
            }
         }
      }

      /**
       * Handle a hdu instance.
       *
       * \param du A shared_ptr<hdu> pointing to the HDU..
       */
      virtual void handle(hdu_sptr du);

      /**
       * Handle a ldu1 instance.
       *
       * \param du A shared_ptr<ldu1> pointing to the LDU1.
       */
      virtual void handle(ldu1_sptr du);

      /**
       * Handle a ldu2 instance.
       *
       * \param du A shared_ptr<ldu2> pointing to the LDU2.
       */
      virtual void handle(ldu2_sptr du);

      /**
       * Handle a tdu instance.
       *
       * \param du A shared_ptr<tdu> pointing to the TDU.
       */
      virtual void handle(tdu_sptr du);

      /**
       * Handle a tdu_with_link_control instance.
       *
       * \param du A shared_ptr<tdu_with_link_control> pointing to the TDU.
       */
      virtual void handle(tdu_with_link_control_sptr du);

      /**
       * Handle a tsdu instance.
       *
       * \param A shared_ptr<tsru> pointing to the TSDU.
       */
      virtual void handle(tsdu_sptr du);

      /**
       * Handle a pdu instance.
       *
       * \param A shared_ptr<pdu> pointing to the PDU.
       */
      virtual void handle(pdu_sptr du);

   protected:

      /**
       * data_unit_handler default constructor.
       */
      data_unit_handler();

      /**
       * data_unit_handler constructor.
       *
       * \param next The next data_unit_handler in this chain.
       */
      data_unit_handler(data_unit_handler_sptr next);

   private:

      /**
       * Temporary stash for the du_sptr currently being handled.
       */
      data_unit_sptr d_stash;

      /**
       * The next data_unit_handler in this chain.
       */
      data_unit_handler_sptr d_next;

   };

}

#endif /* INCLUDED_CAI_DATA_UNIT_HANDLER_H */
