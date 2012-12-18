/* -*- mode: C++ -*- */

/*
 * Copyright 2011 Steve Glass
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

#include <cai/tsdu.h>
#include <cai/logfile_du_handler.h>
#include <type/bit_vector.h>
#include <type/dump.h>

#include <algorithm>
#include <boost/crc.hpp>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unistd.h>

#include <fec/bch.h>
using namespace FEC;

using namespace boost;
using namespace CAI;
using namespace std;
using namespace type;

int
main(int ac, char **av)
{
   uint64_t fs = 0x5575f5ff77ff;
   uint16_t nac = 0x293;
   uint8_t duid = 0x07;
   uint8_t opcode = 0x24;
   uint8_t clazz = 0x00;
   uint8_t operand = 0x7e;
   uint32_t src = 0x00;
   uint32_t dst = 0x00;
   bool verbose = false;

   // parse command line
   int errs = 0;
   opterr = 0; /* suppress errors from getopt() */
   for(int opt; (opt = getopt(ac, av, "f:n:o:s:d:v")) != -1;) {
      switch(opt) {
      case 'f':
         fs = strtoull(optarg, NULL, 16);
         break;
      case 'n':
         nac = strtoul(optarg, NULL, 16);
         break;
      case 'o':
         opcode = strtoul(optarg, NULL, 16);
         break;
      case 'd':
         dst = strtoul(optarg, NULL, 16);
         break;
      case 's':
         src = strtoul(optarg, NULL, 16);
         break;
      case 'v':
         verbose = true;
         break;
      default:
         ++errs;
         break;
      }
   }
   if(errs || (ac - optind) != 1) {
      cerr << "usage: xfc [-f FS] [-n NAC] [-d destination] [-s source] file" << endl;
      exit(EXIT_FAILURE);
   }

   // create frame
   shared_ptr<tsdu> du(new tsdu);

   du->FS(fs);
   du->NAC(nac);
   du->DUID(duid);

   vector<status_symbol> ss(du->SS());
   ss[0] = IDLE;
   fill(&ss[1], &ss[ss.size()], UNKNOWN);
   du->SS(ss);

   union tsbk blk;
   blk.xfc.opcode = opcode; 
   blk.xfc.mfid = 0;
   blk.xfc.clazz = clazz;
   blk.xfc.operand = operand;
   blk.xfc.src[0] = (src >> 16)  & 0xff;
   blk.xfc.src[1] = (src >> 8) & 0xff;
   blk.xfc.src[2] = src & 0xff;
   blk.xfc.dst[0] = (dst >> 16) & 0xff;
   blk.xfc.dst[1] = (dst >> 8) & 0xff;
   blk.xfc.dst[2] = dst & 0xff;
   boost::crc_optimal<16, 0x1021, 0x0000, 0xffff, false, false> crc;
   crc.process_bytes(blk.raw, sizeof(blk) - 2);
   blk.xfc.crc = crc.checksum();
   du->tsbk(0, blk);
   du->tsbk(1, blk);
   const uint8_t LAST_BLOCK = 0x80;
   blk.xfc.opcode = LAST_BLOCK | opcode; 
   crc.reset();
   crc.process_bytes(blk.raw, sizeof(blk) - 2);
   du->tsbk(2, blk);

   if(verbose)
      cout << *du;

   // write the frame to pcap file
   const char *path = av[optind];
   logfile_du_handler logger(path);
   logger.dispatch(du);

   exit(EXIT_SUCCESS);
}
