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

bin_PROGRAMS = p25dump
p25dump_SOURCES = p25dump.cc
p25dump_CPPFLAGS = -I@top_srcdir@/lib
p25dump_LDADD = @top_srcdir@/lib/libp25.la
p25dump_LDFLAGS = -lpcap -litpp
