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

#ifndef INCLUDED_P25CAI_ENCAPSULATION_H
#define INCLUDED_P25CAI_ENCAPSULATION_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
namespace CAI {
#endif

/*
 * bits indicating which fields are present in a P25CAI encapsulation header.
 */
const uint32_t P25CAI_TIMESTAMP_ms   = 0x00000001;
const uint32_t P25CAI_FREQUENCY_kHz  = 0x00000002;
const uint32_t P25CAI_CHANNEL        = 0x00000004;
const uint32_t P25CAI_POWER_dBm      = 0x00000008;

/*
 * Meta-information for a P25CAI-encapsulated frame.
 */
struct p25cai_info {
   uint32_t seq_no;          /* frame sequence number (always present) */
   uint32_t present;         /* bitmap indicating which optional fields are present (always present) */
   uint32_t timestamp_ms;    /* timestamp in units of 1ms */
   uint32_t frequency_kHz;   /* frequency of transmission in kHz */
   uint16_t channel;         /* logical channel number in network order */
   int16_t  power_dBm;       /* transmit power level/received signal strength indicator in dBm */
};

/*
 * Parse a buffer containing a P25CAI-encapsulated frame.
 *
 * \param buf_sz The size of the buffer.
 * \param buf Pointer to the buffer containing the encapsulated frame
 * \param info Non-null pointer to the p25cai_info to receive the meta-data.
 * \return A pointer to the encapsulated P25 frame.
 */
extern const uint8_t*
p25cai_parse(size_t buf_sz, const uint8_t *buf, struct p25cai_info *info);

/*
 * Format a buffer so that it contains a P25CAI encapsulation header.
 *
 * \param buf_sz The size of the buffer.
 * \param buf The buffer to receive the encapsulation header.
 * \param info The p25cai_info containing the frame meta-data.
 * \return The number of bytes written into the buffer. 
 */
extern size_t
p25cai_format(size_t buf_sz, uint8_t *buf, struct p25cai_info *info);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDED_P25CAI_ENCAPSULATION_H */
