/*
 * Project 25 IMBE Encoder/Decoder Fixed-Point implementation
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


#ifndef _DSP_SUB
#define _DSP_SUB


#define CNST_0_5_Q1_15  0x4000
#define CNST_0_5_Q5_11  0x0400
#define CNST_1_0_Q1_15  0x7FFF


//-----------------------------------------------------------------------------
//	PURPOSE:
//				Perform inverse DCT
//
//
//  INPUT:
//              in     -  pointer to input data
//              m_lim  -  input data's size
//              i_lim  -  result's size
//              out    -  pointer to save result 
//
//	OUTPUT:
//		None
//
//	RETURN:
//		        Saved in out result of conversion
//
//-----------------------------------------------------------------------------
void idct(int16_t *in, int16_t m_lim, int16_t i_lim, int16_t *out);


//-----------------------------------------------------------------------------
//	PURPOSE:
//				Perform DCT
//
//
//  INPUT:
//              in     -  pointer to input data
//              m_lim  -  input data's size
//              i_lim  -  result's size
//              out    -  pointer to save result 
//
//	OUTPUT:
//		None
//
//	RETURN:
//		        Saved in out result of conversion
//
//-----------------------------------------------------------------------------
void dct(int16_t *in, int16_t m_lim, int16_t i_lim, int16_t *out);

#define FFTLENGTH 256


void fft_init();
void fft(int16_t *datam1, int16_t nn, int16_t isign);

void c_fft(int16_t * farray_ptr);

#endif
