# Copyright 2010-2011 Stephen Glass.
# 
# This file is part of OP25
# 
# OP25 is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# OP25 is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.

bin_PROGRAMS = xfc
xfc_SOURCES = xfc.cc
xfc_CPPFLAGS = -I@top_srcdir@/lib
xfc_LDADD = @top_srcdir@/lib/libp25.la
xfc_LDFLAGS = -lpcap -litpp -lboost_program_options
