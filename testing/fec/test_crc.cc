#include <fec/crc.h>
#include <apco_crc.h>

#include <algorithm>
#include <boost/crc.hpp>
#include <boost/test/auto_unit_test.hpp>
#include <boost/test/test_tools.hpp>

using namespace FEC;
using namespace std;

BOOST_AUTO_TEST_SUITE(crc_test_suite)

/*
 * Test encoding works as expected.
 */
BOOST_AUTO_TEST_CASE(crc_ccitt_against_apco)
{
   const uint8_t test_vector_8[] = {
      0x6f, 0x26, 0xba, 0xd9, 0xb1, 0xc6, 0x0e, 0x9c, 0xbc, 0x6c
   };

   const uint16_t test_vector_16[] = {
      0x6f, 0x26, 0xba, 0xd9, 0xb1, 0xc6, 0x0e, 0x9c, 0xbc, 0x6c
   };

//   NOTE: we should be using crc_ccitt_type but it conflicts with the conformance spec
//   boost::crc_ccitt_type crc;
   boost::crc_optimal<16, 0x1021, 0x0000, 0xffff, false, false> crc;
   crc.process_bytes(test_vector_8, sizeof(test_vector_8));
   BOOST_CHECK_EQUAL(apco_crc_ccitt(test_vector_16), crc.checksum());
}

BOOST_AUTO_TEST_SUITE_END()

