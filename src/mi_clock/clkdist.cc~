#include <cai/message_indicator.h>

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <sysexits.h>

using namespace CAI;
using namespace std;

int
main(int ac, char **av)
{
   cout << "See page 10 of TIA/EIA-102.AAAD and compare outputs" << endl;
   try {
      message_indicator mi("1234567890ABCDEF");
      for(size_t i = 0; i < 30; ++i) {
         cout << setw(2) << i << ": ";
         cout << static_cast<string>(mi) << " ";
         mi.clock(64);
         cout << static_cast<string>(mi) << endl;
      }
   } catch(std::exception& x) {
      cerr << x.what();
      exit(EX_SOFTWARE);
   }
   return EX_OK;
}
