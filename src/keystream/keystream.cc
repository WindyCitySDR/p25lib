#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <openssl/des.h>
#include <stdint.h>
#include <sstream>
#include <string>
#include <string.h>
#include <sysexits.h>

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

int
main(int ac, char **av)
{
   int result;

   DES_key_schedule ks;
   static uint8_t key[] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
   result = DES_set_key_checked(reinterpret_cast<const_DES_cblock*>(key), &ks);
   if(0 == result) {

#if 0
      static uint8_t mi[8] = { 0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF }; 
#else
      static uint8_t mi[8] = { 0x45, 0x80, 0x25, 0x08, 0x63, 0xd0, 0x17, 0x72 }; 
#endif
      const_DES_cblock *iv = reinterpret_cast<const_DES_cblock*>(mi);

      cout << "See page 26 of TIA/EIA-102.AAAD and compare outputs" << endl;
      int num = 0;
      for(size_t i = 0; i < 29; ++i) {
         string s;
         block_to_str(reinterpret_cast<uint8_t*>(iv), s);
         cout << setw(2) << i << ": " << s << endl;
         uint8_t plaintext[8];
         uint8_t ciphertext[8];
         bzero(plaintext, sizeof(plaintext));
         DES_ofb64_encrypt(plaintext, ciphertext, 8, &ks, iv, &num);

      }

   } else {
      DES_key_schedule ks;
      cerr << "error: DES_set_key_checked(&key, &ks) returned " << result << endl;
      exit(EX_SOFTWARE);
   }

   return 0;
}
