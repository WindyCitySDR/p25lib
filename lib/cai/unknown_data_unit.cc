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

#include <cai/unknown_data_unit.h>

using namespace CAI;

unknown_data_unit::unknown_data_unit(const bit_vector& frame_body) :
   abstract_data_unit(frame_body)
{
}

unknown_data_unit::~unknown_data_unit()
{
}

void
unknown_data_unit::dispatch(class data_unit_handler& handler, data_unit_sptr du);
{
   if(dynamic_cast<unknown_data_unit*>(du.data()) == this) {
      unknown_data_sptr unknown_du(du.dynamic_cast<unknown_data_unit>());
      handler.dispatch(unknown_du);
   }
}
