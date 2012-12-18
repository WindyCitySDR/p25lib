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
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with OP25; see the file COPYING. If not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Boston, MA
 * 02110-1301, USA.
 */

#include <cai/data_unit.h>
#include <type/simple_snapshot.h>

#include <exception>
#include <iomanip>
#include <iostream>
#include <pcap/pcap.h>

#include <type/assertions.h>

using namespace CAI;
using namespace std;
using namespace type;

void
dump(const char *filename)
{
   char err[PCAP_ERRBUF_SIZE];
   pcap_t *p = pcap_open_offline(filename, err);
   if(p) {
      struct pcap_pkthdr hdr;
      for(const u_char *octets; octets = pcap_next(p, &hdr);) {
         const size_t ethernet_sz = 14;
         try {
            if(ethernet_sz < hdr.caplen) {
               data_unit_sptr du(data_unit::create(hdr.caplen - ethernet_sz, octets + ethernet_sz));
               du->apply_FEC();
               simple_snapshot s;
               du->take_snapshot(s);
               cout << s.to_string() << endl;
            } else {
               cerr << "error: bad frame!" << endl;
            }
         } catch(const exception& x) {
            cerr << x.what() << endl;
         }
      }
      pcap_close(p);
   } else {
      cerr << filename << ": "  << pcap_geterr(p) << endl;
   }
}

int
main(int ac, char **av)
{
   while(--ac) {
      dump(*++av);
   }
   exit(0);
}
