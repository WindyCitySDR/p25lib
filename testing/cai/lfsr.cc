#include <lfsr.h>

#include <cstddef>
#include <string>
#include <strings.h>

using namespace std;

void
str_to_lfsr(string s, lfsr l)
{
   bzero(l, sizeof(l));
   for(size_t i = 0; i < 64; ++i) {
      size_t word = i / 16;
      size_t bit = 15 - (i % 16);
      if('1' == s[i]) {
         l[word] |= 1u << bit;
      }
   }
}

void
lfsr_to_str(lfsr l, string& s)
{
   s.clear();
   s.resize(64);
   for(size_t i = 0; i < 64; ++i) {
      size_t word = i / 16;
      uint16_t bit = 15 - (i % 16);
      s[i] = (l[word] & (1 << bit) ? '1' : '0');
   }
}

void
clock_lfsr(lfsr l)
{
   for(size_t i = 0; i < 8; ++i) {
      uint16_t x = l[0] ^ (l[0] << 2) ^ (l[1] << 2) ^ (l[1] << 10) ^ ((l[2] >> 6) & 0x0300) ^ (l[2] << 5) ^ (l[3] << 1);
      for(size_t j = 0; j < 3; ++j) {
         l[j] = ((l[j] << 8) & 0xff00) | ((l[j+1] >> 8) & 0x00ff);
      }
      l[3] = ((l[3] << 8) & 0xff00) | ((x >> 8) & 0x00ff);
   }
}
