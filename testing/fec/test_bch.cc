#define __STDC_LIMIT_MACROS
#include <bch.h>
#include <tia_bch.h>

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/test_tools.hpp>

#include <cstdio>
using std::printf;

/* Swab data from TIA output format into a uint64_t.
 *
 */
uint64_t
to_uint64(const uint16_t *codewords)
{
   return static_cast<uint64_t>(codewords[3]) |
      (static_cast<uint64_t>(codewords[2]) << 16) |
      (static_cast<uint64_t>(codewords[1]) << 32) |
      (static_cast<uint64_t>(codewords[0]) << 48);

}

BOOST_AUTO_TEST_SUITE(bch_test_suite)

/*
 * Compares against well-known BCH-encoded NID values from page 73-75
 * of the TSB-102.BAAB conformance spec. This is a sanity check for
 * both the encoder under test and the standard tia_bch_64_encode test
 * function.
 */
BOOST_AUTO_TEST_CASE(encode_conformance_spec_values)
{
   /* The following NID values are recovered from the dumps shown in
    * the conformance spec. There's a certain amount of bit-bashing to
    * go from the printed representation to the normal form used here.
    */
   static const uint64_t nids[] = {
      0x023338ec549b5718LL,
      0x031375f06aa25dbcLL,
      0x0323277eb2987bd0LL,
      0x0433dc9fb0e5f170LL,
      0x11439252875bdeeaLL,
      0x205359e10bfe6e6cLL,
      0x40b3d893d1880b08LL,
      0x41138284474466daLL,
      0x4643bf739a9e64eaLL,
      0x51635a0366bbbc1cLL,
      0x5853cd06778755aaLL,
      0x8113e44dc2aafb4eLL,
      0x023338ec549b5718LL,
      0x031375f06aa25dbcLL,
      0x0323277eb2987bd0LL,
      0x0433dc9fb0e5f170LL,
      0x11439252875bdeeaLL,
      0x205359e10bfe6e6cLL,
      0x40b3d893d1880b08LL,
      0x41138284474466daLL,
      0x4643bf739a9e64eaLL,
      0x51635a0366bbbc1cLL,
      0x5853cd06778755aaLL,
      0x8113e44dc2aafb4eLL
   };

   const size_t nof_items = sizeof(nids) / sizeof(nids[0]);
   for(size_t i = 0; i < nof_items; ++i) {
      uint64_t expected = nids[i];
      uint16_t val = expected >> 48;
      uint64_t actual = bch_64_encode(val);

      uint16_t codewords[4];
      tia_bch_64_encode(val, codewords);
      uint64_t standard = to_uint64(codewords);

      BOOST_CHECK_EQUAL(actual, standard);
      BOOST_CHECK_EQUAL(actual, expected);

      if(actual != expected) {
         printf("  actual: %016lX\n", actual);
         printf("expected: %016lX\n", expected);
      }
   }
}

/*
 * Test encoding works for all valid codewords by comparing results
 * against the TIA-provided encoder (which we now assume to be
 * correct).
 */
BOOST_AUTO_TEST_CASE(encode_against_tia_standard)
{
   for(uint32_t i = 0; i < UINT16_MAX; ++i) {
      uint16_t codewords[4];
      tia_bch_64_encode(i, codewords);
      uint64_t expected = to_uint64(codewords);
      uint64_t actual = bch_64_encode(i);
      BOOST_CHECK_EQUAL(actual, expected);
   }
}

/*
 * Test that known codewords are decoded properly.
 */
BOOST_AUTO_TEST_CASE(decode_conformance_spec_codewords)
{
   /* See bitconv.scm for the processing that recovers the following
    * NID values from the raw octet stream as shown in the conformance
    * spec.
    */
   static const uint64_t nids[] = {
      0x023338ec549b5718LL,
      0x031375f06aa25dbcLL,
      0x0323277eb2987bd0LL,
      0x0433dc9fb0e5f170LL,
      0x11439252875bdeeaLL,
      0x205359e10bfe6e6cLL,
      0x40b3d893d1880b08LL,
      0x41138284474466daLL,
      0x4643bf739a9e64eaLL,
      0x51635a0366bbbc1cLL,
      0x5853cd06778755aaLL,
      0x8113e44dc2aafb4eLL,
      0x023338ec549b5718LL,
      0x031375f06aa25dbcLL,
      0x0323277eb2987bd0LL,
      0x0433dc9fb0e5f170LL,
      0x11439252875bdeeaLL,
      0x205359e10bfe6e6cLL,
      0x40b3d893d1880b08LL,
      0x41138284474466daLL,
      0x4643bf739a9e64eaLL,
      0x51635a0366bbbc1cLL,
      0x5853cd06778755aaLL,
      0x8113e44dc2aafb4eLL
   };

   const size_t nof_items = sizeof(nids) / sizeof(nids[0]);
   for(size_t i = 0; i < nof_items; ++i) {
      uint64_t expected = nids[i];
      uint64_t actual = expected;
      size_t errs = bch_64_decode(actual);
      BOOST_CHECK_EQUAL(errs, 0);
      BOOST_CHECK_EQUAL(actual, expected);
   }
}

/*
 * Test decoding works for all valid codewords by comparing results
 * against the input.
 */
BOOST_AUTO_TEST_CASE(decode_valid_codewords)
{
   for(uint32_t i = 0; i < UINT16_MAX; ++i) {
      uint64_t expected = bch_64_encode(i);
      uint64_t actual = expected;
      size_t errs = bch_64_decode(actual);
      BOOST_CHECK_EQUAL(errs, 0);
      BOOST_CHECK_EQUAL(actual, expected);
   }
}

/*
 * Test decoding works for all valid codewords by comparing results
 * against the input.
 */
BOOST_AUTO_TEST_CASE(decode_damaged_codewords)
{
   for(uint32_t i = 0; i < UINT16_MAX; ++i) {
      uint64_t expected = bch_64_encode(i);
      uint64_t actual = expected;
      const uint64_t damage = 0xf;
      actual ^= damage;
      size_t errs = bch_64_decode(actual);
      BOOST_CHECK_EQUAL(errs, 4);
      BOOST_CHECK_EQUAL(actual, expected);
   }
}

BOOST_AUTO_TEST_SUITE_END()
