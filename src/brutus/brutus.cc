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

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdint.h>
#include <strings.h>
#include <sysexits.h>

#include <openssl/rc4.h>

using namespace std;

typedef uint8_t block[8];

void
block_to_str(block l, string& s)
{
   ostringstream os;
   for(size_t i = 0; i < sizeof(l); ++i) {
      os << hex << setw(2) << setfill('0') << static_cast<uint16_t>(l[i]);
   }
   s = os.str();
}

size_t
match(const uint8_t target[], const uint8_t keystream[], size_t keystream_sz)
{
   size_t n = 0;
   for(size_t i = 0; i < keystream_sz; ++i) {
      uint8_t bits = target[i] ^ keystream[i];
      for(size_t j = 0; j < 8; ++j) {
         if(bits & (1 << j)) {
            ++n;
         }
      }
   }
   return n;
}

int
main(int ac, char **av) 
{
   static uint8_t known_plaintext[] = {
      0x04, 0x0c, 0xfd, 0x7b, 0xfb, 0x7d, 0xf2, 0x7b, 0x3d, 0x9e, 0x45
   };

   static uint8_t known_ciphertext[] = {
      0xf0, 0x0c, 0x24, 0x07, 0xed, 0x83, 0xe7, 0x1f, 0x6a, 0xb6, 0x51
   };

   static const size_t CIPHERTEXT_SZ = sizeof(known_ciphertext);

   static uint8_t key[] = {
      0x01, 0x23, 0x45, 0x67, 0x89,                   // Key
      0x45, 0x80, 0x25, 0x08, 0x63, 0xd0, 0x17, 0x72, // MI
   };

   static const size_t KEY_SZ = sizeof(key);

   /* Unlike DES we need to generate sufficient keystream to decrypt
    * the octets of interest. This may prove to be important in the
    * paper.
    */

   for(size_t i = 0; i < (1 << 20); ++i) {
      RC4_KEY k;
      // ToDo: paste i into key
      RC4_set_key(&k, sizeof(key), key);

      uint8_t plaintext[64];
      const size_t PLAINTEXT_SZ = sizeof(plaintext);

      uint8_t ciphertext[64];
      const size_t CIPHERTEXT_SZ = sizeof(ciphertext);

      RC4(&k, CIPHERTEXT_SZ, plaintext, ciphertext);
   }

   return EX_OK;
}
