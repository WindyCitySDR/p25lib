#include <cai/lc_group_voice_channel_user.h>
#include <cai/link_control.h>
#include <cai/link_control_opcodes.h>
#include <type/assertions.h>

using namespace CAI;
using namespace type;

link_control_sptr
link_control::create(uint64_t bits)
{
   uint8_t opcode = (bits >> 56) & 0x3;
   link_control_sptr lc;
   switch(opcode) {
   case 0x0:
      lc = link_control_sptr(new lc_group_voice_channel_user(bits));
      break;
   default:
      lc = link_control_sptr(new link_control(bits));
      break;
   }
   return lc;
}

link_control::~link_control()
{
}

link_control::operator uint64_t() const
{
   // ToDo: return d_bits.extract();

   return 0;
}

snapshot&
link_control::take_snapshot(snapshot& s) const
{
   static const size_t LCF_BITS[] = {
      0, 1, 2, 3, 4, 5, 6, 7
   };
   static const size_t LCF_D_BITSSZ = sizeof(LCF_BITS) / sizeof(LCF_BITS[0]);
 
   uint8_t lcf = d_bits.extract(LCF_D_BITSSZ, LCF_BITS);
   bool prot = lcf & 0x80;
   s.add("lc_prot", prot ? "TRUE" : "FALSE");
   bool sf = lcf & 0x40;
   s.add("lc_sf", sf ? "TRUE" : "FALSE");
   uint8_t opcode = lcf & 0x3f;
   s.add("lc_opcode", lookup(LINK_CONTROL_OPCODES, opcode));
   return s;
}

link_control::link_control(uint64_t bits) :
   d_bits(64)
{
   for(size_t i = 0; i < 64; ++i) {
      d_bits[i] = (((bits >> (63 - i)) & 0x1) == 0x1);
   }
}

const bit_vector
link_control::bits() const
{
   return d_bits;
}
