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

#define __STDC_CONSTANT_MACROS
#include <assert.h>
#include <cai/p25cai_encapsulation.h>
#include <arpa/inet.h>
#include <string.h>

#ifdef __cplusplus
using namespace CAI;
#endif

/*
 * The P25CAI encapsulation header.
 */
struct p25cai_hdr {
  uint8_t version;  /* 0 at present. */
  uint8_t pad;
  uint16_t length;  /* length of the header */
  uint32_t seq_no;  /* frame sequence number */
  uint32_t present; /* bit-mask indicating which optional fields are present */
} __attribute__((packed));

/*
 * Align p to next n byte boundary.
 *
 * \param p A non-null pointer.
 * \param n The alignment size (must be a power of 2).
 * \return The aligned pointer.
 */
static const uint8_t*
align_const_ptr(const uint8_t *p, uint8_t n)
{
   assert((n & n - 1) == n);
   uint8_t x = n - 1;
   uint64_t i = (uint64_t)(p);
   return (const uint8_t*)((i + x) & ~x);
}

const uint8_t*
p25cai_parse(size_t buf_sz, const uint8_t *buf, struct p25cai_info *info)
{
   uint32_t i;
   struct p25cai_hdr *hdr = (p25cai_hdr*)(buf);
   const uint8_t *args = buf + sizeof(struct p25cai_hdr);
   uint16_t hdr_len = ntohs(hdr->length);
   assert(hdr_len <= buf_sz);
   memset(info, 0, sizeof(struct p25cai_info));
   info->seq_no = ntohl(hdr->seq_no);
   info->present = ntohl(hdr->present);
   for(i = P25CAI_TIMESTAMP_ms; i < P25CAI_POWER_dBm; i <<= 1) {
      uint32_t bit = i & info->present;
      switch(bit) {
      case P25CAI_TIMESTAMP_ms:
         args = align_const_ptr(args, sizeof(uint32_t));
         info->timestamp_ms = ntohl(*((uint32_t*) args));
         args += sizeof(uint32_t);
         break;
      case P25CAI_FREQUENCY_kHz:
         args = align_const_ptr(args, sizeof(uint32_t));
         info->frequency_kHz = ntohl(*((uint32_t*) args));
         args += sizeof(uint32_t);
         break;
      case P25CAI_CHANNEL:
         args = align_const_ptr(args, sizeof(uint16_t));
         info->channel = ntohs(*((uint16_t*) args));
         args += sizeof(uint16_t);
         break;
      case P25CAI_POWER_dBm:
         args = align_const_ptr(args, sizeof(int16_t));
         info->power_dBm = ntohs(*((int16_t*) args));
         args += sizeof(int16_t);
         break;
      default:
         break;
      }
      assert(args <= buf + hdr_len);
   }
   return args;
}

/*
 * Align p to next n byte boundary.
 *
 * \param p A non-null pointer.
 * \param n The alignment size (must be a power of 2).
 * \return The aligned pointer.
 */
static uint8_t*
align_ptr(uint8_t *p, uint8_t n)
{
   assert((n & n - 1) == n);
   uint8_t x = n - 1;
   uint64_t i = (uint64_t)(p);
   return (uint8_t*)((i + x) & ~x);
}

size_t
p25cai_format(size_t buf_sz, uint8_t *buf, struct p25cai_info *info)
{
   uint32_t i;
   uint8_t *args = buf + sizeof(p25cai_hdr);
   struct p25cai_hdr *hdr = (p25cai_hdr*)(buf);
   for(i = P25CAI_TIMESTAMP_ms; i < P25CAI_POWER_dBm; i <<= 1) {
      uint32_t bit = i & info->present;
      switch(bit) {
      case P25CAI_TIMESTAMP_ms:
         args = align_ptr(args, sizeof(uint32_t));
         *((uint32_t*) args) = htonl(info->timestamp_ms);
         args += sizeof(uint32_t);
         break;
      case P25CAI_FREQUENCY_kHz:
         args = align_ptr(args, sizeof(uint32_t));
         *((uint32_t*) args) = htonl(info->frequency_kHz);
         args += sizeof(uint32_t);
         break;
      case P25CAI_CHANNEL:
         args = align_ptr(args, sizeof(uint16_t));
         *((uint16_t*) args) = htons(info->channel);
         args += sizeof(uint16_t);
         break;
      case P25CAI_POWER_dBm:
         args = align_ptr(args, sizeof(int16_t));
         *((int16_t*) args) = htons(info->power_dBm);
         args += sizeof(int16_t);
         break;
      default:
         break;
      }
      assert(args <= buf + buf_sz);
   }
   hdr->version = 0;
   hdr->pad     = 0;
   hdr->seq_no  = htonl(info->seq_no);
   hdr->present = htonl(info->present);
   hdr->length  = htons(args - buf);
   return args - buf;
}
