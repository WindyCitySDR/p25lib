# Copyright 2010 Stephen Glass.
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

bin_PROGRAMS = pngen
pngen_SOURCES = pngen.cc
pngen_CPPFLAGS = -I@top_srcdir@/lib
pngen_LDADD = @top_srcdir@/lib/libp25.la
pngen_LDFLAGS = -lpcap -litpp
