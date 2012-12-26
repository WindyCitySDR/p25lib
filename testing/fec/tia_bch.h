#ifndef INCLUDED_TIA_BCH_H
#define INCLUDED_TIA_BCH_H

#include <stdint.h>

/*
 * APCO P25 TIA_BCH(64,16,23) encoder from TSB-102.BAAB.
 */
extern void tia_bch_64_encode(uint16_t in_word, uint16_t *code_word_out);

#endif /* INCLUDED_TIA_BCH_H */
