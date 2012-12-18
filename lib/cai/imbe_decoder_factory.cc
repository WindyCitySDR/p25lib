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

#include <cai/imbe_decoder.h>
#include <cai/null_imbe_decoder.h>
#include <cai/software_imbe_decoder.h>
#include <cai/vc55_imbe_decoder.h>

#include <cstdlib>
#include <cstring>

using namespace CAI;

imbe_decoder_sptr
imbe_decoder::create()
{
   imbe_decoder_sptr imbe;
   const char *imbe_type = getenv("IMBE");
   if(imbe_type) {
      if(strcasecmp(imbe_type, "null") == 0) {
         imbe = imbe_decoder_sptr(new null_imbe_decoder());
      } else if(strcasecmp(imbe_type, "vc55") == 0) {
         imbe = imbe_decoder_sptr(new vc55_imbe_decoder());
      } else {
         imbe = imbe_decoder_sptr(new software_imbe_decoder());
      }
   } else {
      imbe = imbe_decoder_sptr(new software_imbe_decoder());
   }
   return imbe;
}
