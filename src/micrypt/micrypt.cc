#include <cai/message_indicator.h>

#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <openssl/des.h>
#include <stdint.h>
#include <sstream>
#include <string>
#include <string.h>
#include <strings.h>
#include <sysexits.h>

using namespace CAI;
using namespace std;

typedef uint8_t block[8];

uint8_t
hex_value(char c)
{
   c = tolower(c);
   return (('0' <= c && c <= '9') ? c - '0' : c - 'a' + 0xa);
}

void
str_to_block(string s, block l)
{
   bzero(l, sizeof(l));
   const size_t NOF_NYBBLES = min(static_cast<size_t>(16), s.size());
   const size_t OFS = 16 - NOF_NYBBLES;
   for(size_t i = 0; i < NOF_NYBBLES; ++i) {
      const size_t N = i + OFS;
      size_t octet = N / 2;
      size_t lo = N % 2;
      l[octet] |= hex_value(s[i]) << (lo ? 0 : 4);
   }
}

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
   if(2 == ac) {
      int result;

      DES_key_schedule ks;
      uint8_t key[] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
      DES_set_odd_parity(reinterpret_cast<const_DES_cblock*>(key));
      result = DES_set_key_checked(reinterpret_cast<const_DES_cblock*>(key), &ks);
      if(0 == result) {

         uint8_t mi[8];
         str_to_block(av[1], mi);
         const_DES_cblock *iv = reinterpret_cast<const_DES_cblock*>(mi);
         uint8_t zeroes[8];
         uint8_t out[8];

         string s;
         message_indicator next_mi(av[1]);
         next_mi.clock(64);

         cout << "next: " << static_cast<string>(next_mi) << endl;

         int num = 0;
         for(size_t i = 0; i < 27; ++i) {
            bzero(zeroes, sizeof(zeroes));
            DES_ofb64_encrypt(zeroes, out, 8, &ks, iv, &num);
            block_to_str(mi, s);
            cout << setw(2) << i << ": " << s << endl;

            block_to_str(mi,s);
            MI next(s);
            next.clock(64);

            cout << "Next: " << static_cast<string>(next) << endl;
         }


      } else {
         DES_key_schedule ks;
         cerr << "error: DES_set_key_checked(&key, &ks) returned " << result << endl;
         exit(EX_SOFTWARE);
      }

   } else {
      cerr << "usage: " << av[0] << " MI" << endl;
      exit(EX_USAGE);
   }
   return 0;
}
