/* -*- C++ -*- */

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
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with OP25; see the file COPYING. If not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Boston, MA
 * 02110-1301, USA.
 */

#include <cai/logfile_du_handler.h>
#include <type/assertions.h>

#include <iomanip>
#include <stdint.h>
#include <sstream>

using namespace CAI;
using namespace std;
using type::raise;

logfile_du_handler::logfile_du_handler(const char *filename) :
   data_unit_handler()
{
   CHECK_NOT_NULL(filename);
   const int max_snapshot_len = 2048;
   dead_ = pcap_open_dead(DLT_EN10MB, max_snapshot_len);
   dump_ = pcap_dump_open(dead_, filename);
   if(!dump_) {
      ostringstream msg;
      msg << filename << ": " << pcap_geterr(dead_);
      raise<invalid_argument>(__PRETTY_FUNCTION__, __FILE__, __LINE__, msg.str());
   }
}

logfile_du_handler::logfile_du_handler(data_unit_handler_sptr next, const char *filename) :
   data_unit_handler(next)
{
   CHECK_NOT_NULL(filename);
   const int max_snapshot_len = 2048;
   dead_ = pcap_open_dead(DLT_EN10MB, max_snapshot_len);
   dump_ = pcap_dump_open(dead_, filename);
   if(!dump_) {
      ostringstream msg;
      msg << filename << ": " << pcap_geterr(dead_);
      raise<invalid_argument>(__PRETTY_FUNCTION__, __FILE__, __LINE__, msg.str());
   }
}

logfile_du_handler::~logfile_du_handler()
{
   pcap_dump_close(dump_);
   pcap_close(dead_);
}

void
logfile_du_handler::dispatch(data_unit_sptr du)
{
   size_t n = 0;
   struct pcap_pkthdr hdr;
   gettimeofday(&hdr.ts, NULL);
   vector<uint8_t> frame(du->pack());

   // insert the ethernet frame header
   static const uint8_t HDR[] = {
      0x01, 0x00, 0x5e, 0x00, 0x00, 0x01, 0x00, 0x0c,
      0x29, 0xf9, 0x99, 0x01, 0x08, 0x00, 0x45, 0x00,
      0x00, 0xf4, 0x57, 0x8d, 0x40, 0x00, 0x01, 0x11,
      0xa9, 0x13, 0xc0, 0xa8, 0xd7, 0xae, 0xe0, 0x00,
      0x00, 0x01, 0xda, 0xf7, 0x5b, 0xa0, 0x00, 0xe0,
      0x79, 0x4a
   };
   static const size_t HDR_SZ = sizeof(HDR);
   frame.insert(frame.begin(), &HDR[0], &HDR[HDR_SZ]);

   // write to file
   hdr.len = hdr.caplen = frame.size();
   u_char *pcap = reinterpret_cast<u_char*>(dump_);
   pcap_dump(pcap, &hdr, &frame[0]);
   data_unit_handler::dispatch(du);
}
