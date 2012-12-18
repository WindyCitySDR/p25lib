#include <type/dump.h>

#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <strings.h>
#include <sysexits.h>

#include <openssl/rc4.h>

using namespace std;
using type::dump;

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

   static uint8_t known_ciphertext[][11] = {
      { 0x83, 0xa5, 0x6b, 0x34, 0x4d, 0xf7, 0xd6, 0x68, 0x9d, 0x0c, 0xdb },
      { 0x36, 0x39, 0xd4, 0x26, 0x46, 0x93, 0x4b, 0x98, 0x81, 0x98, 0x0b },
      { 0x03, 0x74, 0x4d, 0x1b, 0x0f, 0x4b, 0xbd, 0x59, 0x77, 0xca, 0xf9 },
      { 0x2b, 0x8c, 0x10, 0x42, 0xe2, 0x8e, 0x1d, 0x6e, 0xaf, 0xda, 0x88 },
      { 0xd4, 0xa0, 0xdf, 0x3f, 0x08, 0x49, 0x97, 0xc4, 0xe9, 0xa4, 0x48 },
      { 0xdb, 0x80, 0x95, 0x74, 0xf3, 0xed, 0x9c, 0xdf, 0xfa, 0xe6, 0xe0 },
      { 0x8e, 0x1a, 0xe6, 0x48, 0xe5, 0x58, 0x64, 0xb8, 0xbf, 0x46, 0x34 },
      { 0xf0, 0x0c, 0x24, 0x07, 0xed, 0x83, 0xe7, 0x1f, 0x6a, 0xb6, 0x51 },
      { 0x7e, 0xdd, 0x4e, 0x7b, 0xaa, 0xb5, 0x08, 0x3d, 0x74, 0xdc, 0x39 },
   };
   static const size_t CIPHERTEXT_SZ = 11;

   for(size_t text=0; text < 9; ++text) {

      uint8_t known_keystream[8][CIPHERTEXT_SZ];
      for(size_t i = 0; i < 8; ++i) {
         for(int16_t j = CIPHERTEXT_SZ - 1; 0 <= j; --j) {
            known_keystream[i][j] = ((known_plaintext[j] ^ known_ciphertext[text][j]) << i) | ((known_plaintext[j+1] ^ known_ciphertext[text][j+1]) >> (8 - i));
         }
      }

      static uint8_t key[] = {
         0x01, 0x23, 0x45, 0x67, 0x89,                   // Key
         0x45, 0x80, 0x25, 0x08, 0x63, 0xd0, 0x17, 0x72, // MI
      };

      static const size_t KEY_SZ = sizeof(key);
      RC4_KEY k;
      RC4_set_key(&k, sizeof(key), key);
      uint8_t zeroes[2048];
      const size_t ZEROES_SZ = sizeof(zeroes);
      bzero(zeroes, ZEROES_SZ);
      uint8_t keystream[4096];
      const size_t KEYSTREAM_SZ = sizeof(keystream);
      bzero(keystream, KEYSTREAM_SZ);
      RC4(&k, KEYSTREAM_SZ, zeroes, keystream);

      const size_t THRESHOLD = 20;
      for(size_t i = 0; i < KEYSTREAM_SZ - CIPHERTEXT_SZ; ++i) {
         for(size_t j = 0; j < 8; ++j) {
            size_t n = match(known_keystream[j], &keystream[i], CIPHERTEXT_SZ - 1);
            if(n < THRESHOLD) {
               cout << dec << setw(3) << i << "/" << j << ":" << n << endl;
               cout << dump(CIPHERTEXT_SZ, known_keystream[j]) << endl;
               cout << dump(CIPHERTEXT_SZ, &keystream[i]) << endl;
            }
         }
      }

   }
   return EX_OK;
}
