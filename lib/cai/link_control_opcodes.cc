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

#include <cai/link_control_opcodes.h>

using namespace CAI;
using type::mapping;

static const mapping::value_type link_control_opcodes[] = {
   mapping::value_type(0, "Group Voice Channel User"),
   mapping::value_type(2, "Group Voice Channel Update"),
   mapping::value_type(3, "Unit to Unit Voice Channel User"),
   mapping::value_type(4, "Group Voice Channel Update - Explicit"),
   mapping::value_type(5, "Unit to Unit Answer Request "),
   mapping::value_type(7, "Telephone Interconnect Answer Request"),
   mapping::value_type(15, "Call Termination/Cancellation"),
   mapping::value_type(16, "Group Affiliation Query"),
   mapping::value_type(17, "Unit Registration Command"),
   mapping::value_type(18, "Unit Authentication Command"),
   mapping::value_type(19, "Status Query"),
   mapping::value_type(20, "Status Update"),
   mapping::value_type(21, "Message Update"),
   mapping::value_type(22, "Call Alert"),
   mapping::value_type(23, "Extended Function Command"),
   mapping::value_type(24, "Channel Identifier Update"),
   mapping::value_type(25, "Channel Identifier Update - Explicit"),
   mapping::value_type(32, "System Service Broadcast"),
   mapping::value_type(33, "Secondary Control Channel Broadcast"),
   mapping::value_type(34, "Adjacent Site Status Broadcast"),
   mapping::value_type(35, "RFSS Status Broadcast"),
   mapping::value_type(36, "Network Status Broadcast"),
   mapping::value_type(37, "Protection Parameter Broadcast"),
   mapping::value_type(38, "Secondary Control Channel Broadcast - Explicit"),
   mapping::value_type(39, "Adjacent Site Status Broadcast - Explicit"),
   mapping::value_type(40, "RFSS Status Broadcast - Explicit"),
   mapping::value_type(41, "Network Status Broadcast - Explicit")
};
static const size_t link_control_opcodes_sz = sizeof(link_control_opcodes) / sizeof(link_control_opcodes[0]);
const mapping CAI::LINK_CONTROL_OPCODES(&link_control_opcodes[0], &link_control_opcodes[link_control_opcodes_sz]);
