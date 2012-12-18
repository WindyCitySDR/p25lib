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

#include <cai/data_unit_handler.h>

using namespace boost;
using namespace CAI;

data_unit_handler::~data_unit_handler()
{
}

data_unit_handler::data_unit_handler() :
   d_next(),
   d_stash()
{
}

data_unit_handler::data_unit_handler(data_unit_handler_sptr next) :
   d_next(next),
   d_stash()
{
}

void
data_unit_handler::dispatch(data_unit_sptr du)
{
   data_unit_sptr saved(d_stash);
   d_stash = du;
   du->dispatch(*this);
   d_stash = saved;
   if(d_next) {
      d_next->dispatch(du);
   }
}

void
data_unit_handler::handle(hdu_sptr du)
{
}

void
data_unit_handler::handle(ldu1_sptr du)
{
}

void
data_unit_handler::handle(ldu2_sptr du)
{
}

void
data_unit_handler::handle(tdu_sptr du)
{
}

void
data_unit_handler::handle(tdu_with_link_control_sptr du)
{
}

void
data_unit_handler::handle(tsdu_sptr du)
{
}

void
data_unit_handler::handle(pdu_sptr du)
{
}
