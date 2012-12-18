/******************************************************************************
Name: crc.h Author: Al Wilson
Date: 8/4/93 History: 8/4/93 New
This module declares three functions:
crc_ccitt ( pointer )	encodes the header parity check
crc_9 ( num, pointer ) encodes the confirmed data block parity check
crc_32 ( length, pointer )	encodes the data parity check

The pointer points to a list of integers. The 32 bit pointer is a
variable length list. The first two functions return a 16 bit and a 9
bit result respectively. The last function returns a 32 bit long
integer result.
******************************************************************************/

#ifndef CRC_H
#define CRC_H

#include <stdint.h>

extern uint16_t apco_crc_ccitt(const uint16_t *);
extern uint16_t apco_crc_9(int, uint16_t *);
extern uint32_t apco_crc_32(int, uint16_t *);

#endif
