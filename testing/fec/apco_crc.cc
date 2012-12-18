/******************************************************************************
Name: crc.c Author: Al Wilson
Date: 8/4/93 History: 8/4/93 New
This module contains three functions: crc_ccitt ( pointer )	encodes the header parity check
crc_9 ( num, pointer ) encodes the confirmed data block parity check
crc_32 ( length, pointer )	encodes the data parity check
The pointer points to a list of integers. The 32 bit pointer is a variable length list. The first two functions return a 16 bit and a 9 bit result respectively. The last function returns a 32 bit long integer result.
The arguments must follow the following rules.
crc_ccitt crc_9
pointer
num pointer
-- must point to an array of 10 octets
-- is a 7-bit serial number for the data block -- must point to an array of 16 octets
length pointer
Revision A	22
-- indicates the length of the array, 1..512 -- must point to an array of (length) octets
crc_32
******************************************************************************/

#include "apco_crc.h"

#define G_16 ((1<<12)|(1<<5)|1)

uint16_t
apco_crc_ccitt(const uint16_t *ptr)
{
   uint16_t temp = 0;
   for (int i=0; i<10; i++) {
      for (int j=7; j>=0; j--) {
         if ( ( (temp >> 15) ^ ((*(ptr+i)) >> j) ) & 1 )
            temp = (temp << 1) ^ G_16;
         else
            temp = temp << 1;
      } 
   } 
   temp = ( temp & 0xffff ) ^ 0xffff;
   return ( temp );
}

#define G_9 ((1<<6)|(1<<4)|(1<<3)|1)
#define G_32 0x04c11db7
