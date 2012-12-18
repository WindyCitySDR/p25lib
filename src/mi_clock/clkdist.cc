#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <sysexits.h>

using namespace CAI;
using namespace std;

#define BIT(X) UINT64_C(1 << X)

int
main(int ac, char **av)
{
   try {

      const uint64_t TAPS = BIT(63) | BIT(61) | BIT(45) | BIT(37) | BIT(26) | BIT(14);

      bits_ <<= 1;
      bits_ |= bit;

   } catch(std::exception& x) {
      cerr << x.what();
      exit(EX_SOFTWARE);
   }
   return EX_OK;
}
