/*
 * Project 25 IMBE Vocoder Fixed-Point implementation
 * Developed by Pavel Yazev E-mail: pyazev@gmail.com
 * Version 1.0 (c) Copyright 2009
 * 
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * The software is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this; see the file COPYING.  If not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Boston, MA
 * 02110-1301, USA.
 */

#ifndef INCLUDED_IMBE_IMBE_H
#define INCLUDED_IMBE_IMBE_H

#include <stddef.h>
#include <stdint.h>

const size_t FRAME             = 160; // Number samples in frame
const size_t NUM_HARMS_MAX     =  56; // Maximum number of harmonics
const size_t NUM_HARMS_MIN     =   9; // Minimum number of harmonics
const size_t NUM_BANDS_MAX     =  12; // Maximum number of bands
const size_t MAX_BLOCK_LEN     =  10; // Maximum length of block used during spectral amplitude encoding
const size_t NUM_PRED_RES_BLKS =   6; // Number of Prediction Residual Blocks
const size_t PE_LPF_ORD        =  21; // Order of Pitch estimation LPF 
const size_t PITCH_EST_FRAME   = 301; // Pitch estimation frame size
const size_t B_NUM             = (NUM_HARMS_MAX - 1);

struct IMBE_PARAM
{
	int16_t e_p;
	int16_t pitch;               // Q14.2
	int16_t ref_pitch;           // Q8.8 
	int32_t fund_freq;
	int16_t num_harms;
	int16_t num_bands;
	int16_t v_uv_dsn[NUM_HARMS_MAX];
	int16_t b_vec[NUM_HARMS_MAX + 3];
	int16_t bit_alloc[B_NUM + 4];
	int16_t sa[NUM_HARMS_MAX];
	int16_t l_uv;
	int16_t div_one_by_num_harm;
	int16_t div_one_by_num_harm_sh;
};

struct Cmplx16 
{
	int16_t re;
	int16_t im;
};

extern void decode_init();
extern void decode(IMBE_PARAM *imbe_param, int16_t *frame_vector, int16_t *snd);

extern void encode_init();
extern void encode(IMBE_PARAM *imbe_param, int16_t *frame_vector, int16_t *snd);

#endif // INCLUDED_IMBE_IMBE_H
