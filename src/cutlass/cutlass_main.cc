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

#include <cutlass.h>
#include <cai/data_unit.h>
#include <type/simple_snapshot.h>

#include <exception>
#include <iomanip>
#include <iostream>
#include <pcap/pcap.h>
#include <stdexcept>
#include <sysexits.h>

using namespace CAI;
using namespace std;
using namespace type;

int
main(int ac, char **av)
{
   try {
      cutlass c;
      while(--ac) {
         char err[PCAP_ERRBUF_SIZE];
         pcap_t *p = pcap_open_offline(*++av, err);
         if(p) {
            struct pcap_pkthdr hdr;
            for(const u_char *octets; octets = pcap_next(p, &hdr);) {
               const size_t ethernet_sz = 14;
               if(ethernet_sz < hdr.caplen) {
                  data_unit_sptr du(data_unit::create(hdr.caplen - ethernet_sz, octets + ethernet_sz));
                  // d->apply_FEC();
                  c.dispatch(du);
               }
            }
            pcap_close(p);
         } else {
            cerr << *av << ": "  << pcap_geterr(p) << endl;
            exit(EX_NOINPUT);
         }
      }
   } catch(const exception& x) {
      cerr << x.what() << endl;
      exit(EX_SOFTWARE);
   } catch(...) {
      cerr << "unhandled exception!" << endl;
      exit(EX_SOFTWARE);
   }
   return(EX_OK);
}
