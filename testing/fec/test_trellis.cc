#include <fec/trellis.h>

#include <algorithm>
#include <boost/test/auto_unit_test.hpp>
#include <boost/test/test_tools.hpp>

using namespace FEC;
using namespace std;

BOOST_AUTO_TEST_SUITE(trellis_encoder_test_suite)

/*
 * Test 1/2 rate encoding produces appropriate sized output.
 */
BOOST_AUTO_TEST_CASE(half_rate_encoding)
{
   vector<dibit> in(48,0);
   vector<nybble> out(trellis_1_2_encode(in));
   BOOST_CHECK_EQUAL(out.size(), in.size() + 1);  
}

/*
 * Test 1/2 rate encoding works on zero-sized input.
 */
BOOST_AUTO_TEST_CASE(half_rate_encoding_empty)
{
   vector<dibit> in;
   vector<nybble> out(trellis_1_2_encode(in));
   // NB flushing the state machine always creates a single dibit output
   BOOST_CHECK_EQUAL(out.size(), 1);
}

/*
 * Test that 1/2 rate encode/decode cycle leads to the same output.
 */
BOOST_AUTO_TEST_CASE(half_rate_decoding_undamaged)
{
   vector<dibit> in(96);
   vector<dibit> out(trellis_1_2_decode(trellis_1_2_encode(in)));
   BOOST_CHECK_EQUAL(in.size(), out.size());
   for(size_t i = 0; i < in.size(); ++i) {
      BOOST_CHECK_EQUAL(in[i], out[i]);
   }
}

/*
 * Test that an encode/decode cycle leads to the same output.
 */
BOOST_AUTO_TEST_CASE(half_rate_decoding_random_undamaged)
{
   vector<dibit> in(196);
   for(size_t i = 0; i < in.size(); ++i) {
      const uint8_t DIBIT_MASK = 0x3;
      in[i] = i & DIBIT_MASK;
   }
   random_shuffle(&in[0], &in[in.size()]);

   vector<dibit> out(trellis_1_2_decode(trellis_1_2_encode(in)));
   BOOST_CHECK_EQUAL(in.size(), out.size());
   for(size_t i = 0; i < in.size(); ++i) {
      BOOST_CHECK_EQUAL(in[i], out[i]);
   }
}

/*
 * Test that decode catches obvious decode error.
 */
BOOST_AUTO_TEST_CASE(half_rate_decoding_error)
{
   vector<dibit> in(96,0);
   BOOST_CHECK_THROW(vector<nybble> out(trellis_1_2_decode(in)), std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()
