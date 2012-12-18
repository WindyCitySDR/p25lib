#include <cai/message_indicator.h>
#include <lfsr.h>

#include <iostream>
#include <iomanip>
using namespace std;

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/test_tools.hpp>

using namespace CAI;

BOOST_AUTO_TEST_SUITE(message_indicator_test_suite)

/*
 * Test that clocking works as expected.
 */
BOOST_AUTO_TEST_CASE(decoding_undamaged)
{
   const string START("0000000000000000000000000000000000000000000000000000000000000001");
   string s(START);
   message_indicator mi(START);
   const size_t NREPS = 1 << 20;
   for(size_t i = 0; i < NREPS; ++i) {
      lfsr l;
      str_to_lfsr(s, l);
      clock_lfsr(l);

      lfsr_to_str(l, s);
      mi.clock(64);
      BOOST_CHECK_EQUAL(s, static_cast<string>(mi));  
   }
}

BOOST_AUTO_TEST_SUITE_END()
