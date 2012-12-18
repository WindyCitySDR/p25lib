#include <cai/tsdu.h>

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/test_tools.hpp>

using namespace CAI;

BOOST_AUTO_TEST_SUITE(message_indicator_test_suite)

/*
 * Test payload accessor returns what its given.
 */
BOOST_AUTO_TEST_CASE(payload_accessors)
{
   tsdu du;
   union tsdu::payload in;
   for(size_t i = 0; i < sizeof(in); ++i) {
      in.raw[i] = i;
   }
   du.payload(in);
   union tsdu::payload out(du.payload());
   for(size_t i = 0; i < sizeof(out); ++i) {
      BOOST_CHECK_EQUAL(in.raw[i], out.raw[i]);
   }
}

BOOST_AUTO_TEST_SUITE_END()
