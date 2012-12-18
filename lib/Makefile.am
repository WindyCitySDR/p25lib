# Copyright 2010-2011 Stephen Glass.
# 
# This file is part of OP25
# 
# OP25 is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# OP25 is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.

lib_LTLIBRARIES = libp25.la

libp25_la_SOURCES= \
	type/bit_vector.cc \
	type/dump.cc \
	type/mapping.cc \
	type/python_snapshot.cc \
	type/simple_snapshot.cc \
	type/snapshot.cc \
	fec/bch.cc \
	fec/golay.cc \
	fec/hamming.cc \
	fec/trellis.cc \
	cai/abstract_data_unit.cc \
	cai/algids.cc \
	cai/cipher.cc \
	cai/data_unit.cc \
	cai/data_unit_factory.cc \
	cai/data_unit_handler.cc \
	cai/duids.cc \
	cai/hdu.cc \
	cai/ldu1.cc \
	cai/ldu2.cc \
	cai/link_control.cc \
	cai/logfile_du_handler.cc \
	cai/message_indicator.cc \
	cai/lc_group_voice_channel_user.cc \
	cai/link_control_opcodes.cc \
	cai/mfids.cc \
	cai/nacs.cc \
	cai/p25cai_encapsulation.cc \
	cai/pdu.cc \
	cai/tdu.cc \
	cai/tdu_with_link_control.cc \
	cai/tsdu.cc \
	cai/voice_data_unit.cc \
	imbe/aux_sub.cc \
	imbe/basicop2.cc \
	imbe/ch_decode.cc \
	imbe/ch_encode.cc \
	imbe/dc_rmv.cc \
	imbe/decode.cc \
	imbe/dsp_sub.cc \
	imbe/encode.cc \
	imbe/math_sub.cc \
	imbe/pe_lpf.cc \
	imbe/pitch_est.cc \
	imbe/pitch_ref.cc \
	imbe/qnt_sub.cc \
	imbe/rand_gen.cc \
	imbe/sa_decode.cc \
	imbe/sa_encode.cc \
	imbe/sa_enh.cc \
	imbe/tbls.cc \
	imbe/uv_synt.cc \
	imbe/v_synt.cc \
	imbe/v_uv_det.cc

libp25_ladir = $(includedir)/p25

nobase_libp25_la_HEADERS= \
	type/bit_vector.h \
	type/dump.h \
	type/mapping.h \
	type/python_snapshot.h \
	type/simple_snapshot.h \
	type/snapshot.h \
	fec/bch.h \
	fec/golay.h \
	fec/hamming.h \
	fec/trellis.h \
	cai/abstract_data_unit.h \
	cai/algids.h \
	cai/cipher.h \
	cai/data_unit.h \
	cai/data_unit_handler.h \
	cai/duids.h \
	cai/hdu.h \
	cai/ldu1.h \
	cai/ldu2.h \
	cai/link_control.h \
	cai/link_control_opcodes.h \
	cai/logfile_du_handler.h \
	cai/message_indicator.h \
	cai/mfids.h \
	cai/nacs.h \
	cai/p25cai_encapsulation.h \
	cai/pdu.h \
	cai/tdu.h \
	cai/tdu_with_link_control.h \
	cai/tsdu.h \
	cai/voice_data_unit.h \
	imbe/imbe.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = p25.pc
