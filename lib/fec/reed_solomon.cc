/* -*- mode: C++ -*- */

/*
 * Copyright 2010 Steve Glass
 * 
 * This file is part of OP25.
 * 
 * OP25 is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * OP25 is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
 * License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with OP25; see the file COPYING.  If not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Boston, MA
 * 02110-1301, USA.
 */

#include <fec/reed_solomon.h>

using namespace FEC;

int
multgf26(int b, int c)
{
   int aout, a5temp;
   int tempa, tempb, tempc;
   int t[6], a[6];
   int i, j;
   a[0]=a[1]=a[2]=a[3]=a[4]=a[5]=0;
   for( i=0; i<6; i++) {
      tempc = ( c>>(5-i) ) & 0x01;
      for( j=0; j<6; j++) {
         tempb = ( b>>j ) & 0x01;
         t[j] = tempc & tempb;
      }
      a5temp = a[5];
      a[5] = t[5] ^ a[4];
      a[4] = t[4] ^ a[3];
      a[3] = t[3] ^ a[2];
      a[2] = t[2] ^ a[1];
      a[1] = t[1] ^ a[0] ^ a5temp;
      a[0] = t[0] ^ a5temp;
   }
   aout = 0;
   for( i=0; i<6; i++ ) {
      aout += (a[i]<<i);
   }
   return(aout);
}

void
FEC::reed_solomon_24_12_encode(int *in_word, int *code_word)
{
   static const int RS_24_12[12][24] = {
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 062, 044, 003, 025, 014, 016, 027, 003, 053, 004, 036, 047, 
      0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 011, 012, 011, 011, 016, 064, 067, 055, 001, 076, 026, 073, 
      0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 003, 001, 005, 075, 014, 006, 020, 044, 066, 006, 070, 066, 
      0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 021, 070, 027, 045, 016, 067, 023, 064, 073, 033, 044, 021, 
      0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 030, 022, 003, 075, 015, 015, 033, 015, 051, 003, 053, 050, 
      0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 001, 041, 027, 056, 076, 064, 021, 053, 004, 025, 001, 012, 
      0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 061, 076, 021, 055, 076, 001, 063, 035, 030, 013, 064, 070, 
      0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 024, 022, 071, 056, 021, 035, 073, 042, 057, 074, 043, 076, 
      0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 072, 042, 005, 020, 043, 047, 033, 056, 001, 016, 013, 076, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 072, 014, 065, 054, 035, 025, 041, 016, 015, 040, 071, 026, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 073, 065, 036, 061, 042, 022, 017, 004, 044, 020, 025, 005, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 071, 005, 055, 003, 071, 034, 060, 011, 074, 002, 041, 050
   };

   int temp, i, j;
   for(i=0; i < 24; i++) {
      temp = 0;
      for(j=0; j<12; j++) {
         temp ^= multgf26 (in_word[j], RS_24_12[j][i]);
      }
      code_word[i] = temp & 0x03f;
   }
}

void
FEC::reed_solomon_24_16_encode(int *in_word, int *code_word)
{
   static const int RS_24_16[16][24] = {
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 051, 045, 067, 015, 064, 067, 052, 012, 
      0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 057, 025, 063, 073, 071, 022, 040, 015, 
      0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 005, 001, 031, 004, 016, 054, 025, 076, 
      0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 073, 007, 047, 014, 041, 077, 047, 011, 
      0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 075, 015, 051, 051, 017, 067, 017, 057, 
      0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 020, 032, 014, 042, 075, 042, 070, 054, 
      0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 002, 075, 043, 005, 001, 040, 012, 064, 
      0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 024, 074, 015, 072, 024, 026, 074, 061, 
      0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 042, 064, 007, 022, 061, 020, 040, 065, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 032, 032, 055, 041, 057, 066, 021, 077, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 065, 036, 025, 007, 050, 016, 040, 051, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 064, 006, 054, 032, 076, 046, 014, 036, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 062, 063, 074, 070, 005, 027, 037, 046, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 055, 043, 034, 071, 057, 076, 050, 064, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 024, 023, 023, 005, 050, 070, 042, 023, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 067, 075, 045, 060, 057, 024, 006, 026
   };

   int temp, i, j;
   for(i=0; i<24; i++)
   {
      temp = 0;
      for(j=0; j<16; j++)
      {
         temp ^= multgf26 ( in_word[j], RS_24_16[j][i] );
      }
      code_word[i] = temp&0x03f;
   }
}

void
FEC::reed_solomon_36_20_encode(int *in_word, int *code_word)
{
   static const int RS_36_20[20][36] = {
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 074, 037, 034, 006, 002, 007, 044, 064, 026, 014, 026, 044, 054, 013, 077, 005, 
      0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 004, 017, 050, 024, 011, 005, 030, 057, 033, 003, 002, 002, 015, 016, 025, 026, 
      0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 007, 023, 037, 046, 056, 075, 043, 045, 055, 021, 050, 031, 045, 027, 071, 062, 
      0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 026, 005, 007, 063, 063, 027, 063, 040, 006, 004, 040, 045, 047, 030, 075, 007, 
      0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 023, 073, 073, 041, 072, 034, 021, 051, 067, 016, 031, 074, 011, 021, 012, 021, 
      0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 024, 051, 025, 023, 022, 041, 074, 066, 074, 065, 070, 036, 067, 045, 064, 001, 
      0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 052, 033, 014, 002, 020, 006, 014, 025, 052, 023, 035, 074, 075, 075, 043, 027, 
      0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 055, 062, 056, 025, 073, 060, 015, 030, 013, 017, 020, 002, 070, 055, 014, 047, 
      0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 054, 051, 032, 065, 077, 012, 054, 013, 035, 032, 056, 012, 075, 001, 072, 063, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 074, 041, 030, 041, 043, 022, 051, 006, 064, 033, 003, 047, 027, 012, 055, 047, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 054, 070, 011, 003, 013, 022, 016, 057, 003, 045, 072, 031, 030, 056, 035, 022, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 051, 007, 072, 030, 065, 054, 006, 021, 036, 063, 050, 061, 064, 052, 001, 060, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 001, 065, 032, 070, 013, 044, 073, 024, 012, 052, 021, 055, 012, 035, 014, 072, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 011, 070, 005, 010, 065, 024, 015, 077, 022, 024, 024, 074, 007, 044, 007, 046, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 006, 002, 065, 011, 041, 020, 045, 042, 046, 054, 035, 012, 040, 064, 065, 033, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 034, 031, 001, 015, 044, 064, 016, 024, 052, 016, 006, 062, 020, 013, 055, 057, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 063, 043, 025, 044, 077, 063, 017, 017, 064, 014, 040, 074, 031, 072, 054, 006, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 071, 021, 070, 044, 056, 004, 030, 074, 004, 023, 071, 070, 063, 045, 056, 043, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 002, 001, 053, 074, 002, 014, 052, 074, 012, 057, 024, 063, 015, 042, 052, 033, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 034, 035, 002, 023, 021, 027, 022, 033, 064, 042, 005, 073, 051, 046, 073, 060
   };

   int temp, i, j;
   for(i=0; i<36; i++)
   {
      temp = 0;
      for(j=0; j<20; j++)
      {
         temp ^= multgf26 ( in_word[j], RS_36_20[j][i] );
      }
      code_word[i] = temp&0x03f;
   }
}

void
FEC::rs_24_12_decode(uint8_t *codeword, uint8_t *decoded)
{
	int i;

	/* TODO: make less fake */

	/* Just grab the first 9 bytes (12 sets of six bits) */
	for (i = 0; i < 9; i++)
		decoded[i] = codeword[i];
}

void
FEC::rs_24_16_decode(uint8_t *codeword, uint8_t *decoded)
{
	int i;

	/* TODO: make less fake */
	/* Just grab the first 12 bytes (16 sets of six bits) */
	for (i = 0; i < 12; i++)
		decoded[i] = codeword[i];
}

void
FEC::rs_36_20_decode(uint8_t *codeword, uint8_t *decoded)
{
	int i;

	/* TODO: make less fake */

	/* Just grab the first 15 bytes (20 sets of six bits) */
	for (i = 0; i < 15; i++)
		decoded[i] = codeword[i];
}

