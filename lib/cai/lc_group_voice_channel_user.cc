#include <cai/lc_group_voice_channel_user.h>

using namespace CAI;
using namespace type;

lc_group_voice_channel_user::lc_group_voice_channel_user(uint64_t bits) :
   link_control(bits)
{
}

snapshot&
lc_group_voice_channel_user::take_snapshot(snapshot& s) const
{
   link_control::take_snapshot(s);
   s.add("lc_group", group_address());
   s.add("lc_source", source_address());
   s.add("lc_options", service_options());
}

uint16_t
lc_group_voice_channel_user::group_address() const
{
   static const size_t GROUP_BITS[] = {
      32, 33, 34, 35, 36, 37, 38, 39,
      40, 41, 42, 43, 44, 45, 46, 47
   };
   static const size_t GROUP_BITS_SZ = sizeof(GROUP_BITS) / sizeof(GROUP_BITS_SZ);
   return bits().extract(GROUP_BITS_SZ, GROUP_BITS);
}

uint8_t
lc_group_voice_channel_user::service_options() const
{
   static const size_t OPTION_BITS[] = {
      16, 17, 18, 19, 20, 21, 22, 23,
   };
   static const size_t OPTION_BITS_SZ = sizeof(OPTION_BITS) / sizeof(OPTION_BITS_SZ);
   return bits().extract(OPTION_BITS_SZ, OPTION_BITS);
}

uint32_t
lc_group_voice_channel_user::source_address() const
{
   static const size_t source_BITS[] = {
      48, 49, 50, 51, 52, 53, 54, 55,
      56, 57, 58, 59, 60, 61, 62, 63,
//      64, 65, 66, 67, 68, 69, 70, 71
   };
   static const size_t source_BITS_SZ = sizeof(source_BITS) / sizeof(source_BITS_SZ);
   return bits().extract(source_BITS_SZ, source_BITS);
}
