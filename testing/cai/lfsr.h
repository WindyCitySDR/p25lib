#ifndef LFSR_H
#define LFSR_H

#include <stdint.h>
#include <string>

typedef uint16_t lfsr[4];

/*
 * Convert string to lfsr representation.
 */
extern void str_to_lfsr(std::string s, lfsr l);

/*
 * Convert lfsr to string representation.
 */
extern void lfsr_to_str(lfsr l, std::string& s);

/*
 * Clock the LFSR by 8 positions.
 */
extern void clock_lfsr(lfsr octets);

#endif // LFSR_H
