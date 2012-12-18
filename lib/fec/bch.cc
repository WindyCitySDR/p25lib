/* -*- mode: C++ -*- */

/*
 * Copyright 2010-2011 Steve Glass
 * Copyright 2010 KA1RBI 
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

#define __STDC_LIMIT_MACROS
#include <fec/bch.h>

using namespace FEC;

uint64_t
FEC::bch_63_16_encode(uint16_t value)
{
   static const uint64_t encoding_matrix[] = {
      0x8000cd930bdd3b2aLL,
      0x4000ab5a8e33a6beLL,
      0x2000983e4cc4e874LL,
      0x10004c1f2662743aLL,
      0x0800eb9c98ec0136LL,
      0x0400b85d47ab3bb0LL,
      0x02005c2ea3d59dd8LL,
      0x01002e1751eaceecLL,
      0x0080170ba8f56776LL,
      0x0040c616dfa78890LL,
      0x0020630b6fd3c448LL,
      0x00103185b7e9e224LL,
      0x000818c2dbf4f112LL,
      0x0004c1f2662743a2LL,
      0x0002ad6a38ce9afbLL,
      0x00019b2617ba7657LL
   };

   uint64_t cw = 0LL;
   for(uint8_t i=0; i < 16; ++i) {
      if(value & (1 << (15 - i))) {
         cw ^= encoding_matrix[i];
      }
   }
   return cw;
}

#define NOF(X) (sizeof(X) / sizeof(X[0]))

uint16_t
FEC::bch_63_16_decode(uint64_t codeword, uint8_t *nof_errs)
{
   const size_t N = 63;
   const size_t K = 16;
   const size_t T = 11;
   const size_t TWO_T = 2 * T;
  
   uint8_t cw[8];
   for(size_t i = 0; i < sizeof(cw); ++i) {
      cw[i] = (codeword >> ((7 - i) * 8)) & 0xff;
   }

 	static const int GF_EXP[64] = {
      1, 2, 4, 8, 16, 32, 3, 6, 12, 24, 48, 35, 5, 10, 20, 40,
      19, 38, 15, 30, 60, 59, 53, 41, 17, 34, 7, 14, 28, 56, 51, 37,
      9, 18, 36, 11, 22, 44, 27, 54, 47, 29, 58, 55, 45, 25, 50, 39,
      13, 26, 52, 43, 21, 42, 23, 46, 31, 62, 63, 61, 57, 49, 33, 0
   };

   static const int GF_LOG[64] = {
      -1, 0, 1, 6, 2, 12, 7, 26, 3, 32, 13, 35, 8, 48, 27, 18,
      4, 24, 33, 16, 14, 52, 36, 54, 9, 45, 49, 38, 28, 41, 19, 56,
      5, 62, 25, 11, 34, 31, 17, 47, 15, 23, 53, 51, 37, 44, 55, 40,
      10, 61, 46, 30, 50, 22, 39, 43, 29, 60, 42, 21, 20, 59, 57, 58
   };

   uint8_t nerrs = 0;
   int syndromes[TWO_T];
   for(size_t i = 0; i < NOF(syndromes); ++i) {
      syndromes[i] = 0;
      for(size_t j = 0; j < N; ++j) {
         if(cw[j]) {
            syndromes[i] ^= GF_EXP[((i + 1) * j) % 63];
         }
      }
      if(syndromes[i]) {
         ++nerrs;
      }
      syndromes[i] = GF_LOG[syndromes[i]];
   }

   if(nerrs) {

      int elp[24][TWO_T];
      int discrepancy[23], L[24], uLu[24];
      int root[K], locn[K];
      int i,j,U,q,count;

      // L[0]
      L[0] = 0;
      uLu[0] = -1;
      discrepancy[0] = 0;
      elp[0][0] = 0;

      // L[1]
      L[1] = 0;
      uLu[1] = 0;
      discrepancy[1] = syndromes[0];
      elp[1][0] = 1;

      // setup first two rows of elp matrix
      for(i = 1; i <= 21; i++) {
         elp[0][i] = -1;
         elp[1][i] = 0;
      }

      U = 0;
      do {
         U = U + 1;
         if(-1 == discrepancy[U]) {
            L[U + 1] = L[U];
            for(i = 0; i <= L[U]; i++) {
               elp[U + 1][i] = elp[U][i];
               elp[U][i] = GF_LOG[elp[U][i]];
            }
         } else {

            // search for words with greatest uLu(q) for which d(q)!=0
            q = U - 1;
            while((-1 == discrepancy[q]) && (q > 0)) {
               q = q - 1;
            }
            // have found first non-zero d(q)
            if(q > 0) {
               j = q;
               do {
                  j = j - 1;
                  if((discrepancy[j] != -1) && (uLu[q] < uLu[j])) {
                     q = j;
                  }
               } while(j > 0);
            }

            // store degree of new elp polynomial
            if(L[U] > L[q] + U - q) {
               L[U + 1] = L[U];
            } else {
               L[U + 1] = L[q] + U - q;
            }

            // form new elp(x)
            for(i = 0; i <= 21; i++) {
               elp[U + 1][i] = 0;
            }
            for(i = 0; i <= L[q]; i++) {
               if(elp[q][i] != -1) {
                  elp[U + 1][i + U - q] = GF_EXP[(discrepancy[U] + 63 - discrepancy[q] + elp[q][i]) % 63];
               }
            }
            for(i = 0; i <= L[U]; i++) {
               elp[U + 1][i] = elp[U + 1][i] ^ elp[U][i];
               elp[U][i] = GF_LOG[elp[U][i]];
            }
         }
         uLu[U + 1] = U - L[U + 1];

         // form (u+1)th discrepancy
         if(U < TWO_T) {
            // no discrepancy computed on last iteration
            if(syndromes[U] != -1) {
               discrepancy[U + 1] = GF_EXP[syndromes[U]];
            } else {
               discrepancy[U + 1] = 0;
            }
            for(i = 1; i <= L[U + 1]; i++) {
               if((syndromes[U - i] != -1) && (elp[U + 1][i] != 0)) {
                  discrepancy[U + 1] ^= GF_EXP[(syndromes[U - i] + GF_LOG[elp[U + 1][i]]) % 63];
               }
            }
            // convert d(u+1) into index form */
            discrepancy[U + 1] = GF_LOG[discrepancy[U + 1]];
         }
      } while((U < 22) && (L[U + 1] <= 11));

      ++U;
      if(L[U] <= 11) {
         // Can correct errors
         // put elp into index form
         for(i = 0; i <= L[U]; i++) {
            elp[U][i] = GF_LOG[elp[U][i]];
         }

         //Chien search: find roots of the error location polynomial
         int reg[12];
         for(i = 1; i <= L[U]; i++) {
            reg[i] = elp[U][i];
         }
         count = 0;
         for(i = 1; i <= 63; i++) {
            q = 1;
            for(j = 1; j <= L[U]; j++) {
               if( reg[j] != -1) {
                  reg[j] =(reg[j] + j) % 63;
                  q = q ^ GF_EXP[reg[j]];
               }
            }
            if(0 == q) {
               //store root and error location number indices
               root[count] = i;
               locn[count] = 63 - i;
               ++count;
            }
         }
         if(count == L[U]) {
            // no. roots = degree of elp hence <= t errors
            for(i = 0; i <= L[U] - 1; i++) {
               cw[locn[i]] = cw[locn[i]] ^ 1;
            }
            nerrs = count;
         } else {
            nerrs = UINT8_MAX;
         }
      } else {
         nerrs = UINT8_MAX;
      }
   }

   if(nof_errs) {
      *nof_errs = nerrs;
   }

   uint16_t val = cw[0];
   val <<= 8;
   val |= cw[1];

   return val;
}
