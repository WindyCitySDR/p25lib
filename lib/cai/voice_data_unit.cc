/* -*- mode: C++ -*- */

/*
 * Copyright 2008-2010 Steve Glass
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

#include <cai/voice_data_unit.h>
#include <fec/golay.h>
#include <fec/hamming.h>
#include <type/assertions.h>

#include <iomanip>
#include <sstream>
#include <stdexcept>

using namespace CAI;
using namespace std;
using namespace type;

using FEC::golay_23_12_encode;
using FEC::golay_23_12_decode;
using FEC::hamming_15_11_encode;
using FEC::hamming_15_11_decode;

voice_data_unit::~voice_data_unit()
{
}

void
voice_data_unit::apply_FEC()
{
   // non-voice payload
   apply_short_hamming_FEC();
   // voice payload
   apply_hamming_FEC();
   apply_golay_FEC();
}

void
voice_data_unit::compute_FEC()
{
   // voice payload
   compute_golay_FEC();
   compute_hamming_FEC();
   // non-voice payload
   compute_short_hamming_FEC();   
}

uint16_t
voice_data_unit::reqd_frame_size()
{
   return 1728;
}

voice_codeword
voice_data_unit::short_codeword(size_t n) const
{
   const size_t SHORT_CODEWORD_SZ = 88;
   voice_codeword vcw(SHORT_CODEWORD_SZ);
   // ToDo: PN substitution and FEC
   return vcw;
}

void
voice_data_unit::short_codeword(size_t n, const voice_codeword& vcw)
{
   // ToDo: implement me!
}

static const size_t VOICE_CODEWORD_SZ = 144;
static const size_t VOICE_CODEWORD_BITS[][VOICE_CODEWORD_SZ] = {

   { 114, 121, 126, 133, 138, 147, 152, 159, 164, 171, 176, 183, 188, 195, 200, 207, 212, 221, 226, 233, 238, 245, 250,
     257, 115, 120, 127, 132, 139, 146, 153, 158, 165, 170, 177, 182, 189, 194, 201, 206, 213, 220, 227, 232, 239, 244,
     251, 256, 116, 123, 128, 135, 140, 149, 154, 161, 166, 173, 178, 185, 190, 197, 202, 209, 216, 223, 228, 235, 240,
     247, 252, 259, 117, 122, 129, 134, 141, 148, 155, 160, 167, 172, 179, 184, 191, 196, 203, 208, 217, 222, 229, 234,
     241, 246, 253, 258, 118, 125, 130, 137, 144, 151, 156, 163, 168, 175, 180,
     187, 192, 199, 204, 211, 218, 225, 230, 237, 242, 249, 254, 261, 119, 124,
     131, 136, 145, 150, 157, 162, 169, 174, 181, 186, 193, 198, 205, 210, 219,
     224, 231, 236, 243, 248, 255, 260 },

   { 262, 269, 274, 281, 288, 295, 300, 307, 312, 319, 324, 331, 336, 343, 348, 355, 362, 369, 374, 381, 386, 393, 398,
     405, 263, 268, 275, 280, 289, 294, 301, 306, 313, 318, 325, 330, 337, 342, 349, 354, 363, 368, 375, 380, 387, 392,
     399, 404, 264, 271, 276, 283, 290, 297, 302, 309, 314, 321, 326, 333, 338, 345, 350, 357, 364, 371, 376, 383, 388,
     395, 400, 407, 265, 270, 277, 282, 291, 296, 303, 308, 315, 320, 327, 332, 339, 344, 351, 356, 365, 370, 377, 382,
     389, 394, 401, 406, 266, 273, 278, 285, 292, 299, 304, 311, 316, 323, 328,
     335, 340, 347, 352, 361, 366, 373, 378, 385, 390, 397, 402, 409, 267, 272,
     279, 284, 293, 298, 305, 310, 317, 322, 329, 334, 341, 346, 353, 360, 367,
     372, 379, 384, 391, 396, 403, 408 },

   { 452, 459, 464, 471, 476, 483, 488, 495, 500, 509, 514, 521, 526, 533, 538, 545, 550, 557, 562, 569, 576, 583, 588,
     595, 453, 458, 465, 470, 477, 482, 489, 494, 501, 508, 515, 520, 527, 532, 539, 544, 551, 556, 563, 568, 577, 582,
     589, 594, 454, 461, 466, 473, 478, 485, 490, 497, 504, 511, 516, 523, 528, 535, 540, 547, 552, 559, 564, 571, 578,
     585, 590, 597, 455, 460, 467, 472, 479, 484, 491, 496, 505, 510, 517, 522, 529, 534, 541, 546, 553, 558, 565, 570,
     579, 584, 591, 596, 456, 463, 468, 475, 480, 487, 492, 499, 506, 513, 518,
     525, 530, 537, 542, 549, 554, 561, 566, 573, 580, 587, 592, 599, 457, 462,
     469, 474, 481, 486, 493, 498, 507, 512, 519, 524, 531, 536, 543, 548, 555,
     560, 567, 572, 581, 586, 593, 598 },

   { 640, 649, 654, 661, 666, 673, 678, 685, 690, 697, 702, 709, 714, 723, 728, 735, 740, 747, 752, 759, 764, 771, 776,
     783, 641, 648, 655, 660, 667, 672, 679, 684, 691, 696, 703, 708, 715, 722, 729, 734, 741, 746, 753, 758, 765, 770,
     777, 782, 642, 651, 656, 663, 668, 675, 680, 687, 692, 699, 704, 711, 716, 725, 730, 737, 742, 749, 754, 761, 766,
     773, 778, 785, 643, 650, 657, 662, 669, 674, 681, 686, 693, 698, 705, 710, 717, 724, 731, 736, 743, 748, 755, 760,
     767, 772, 779, 784, 644, 653, 658, 665, 670, 677, 682, 689, 694, 701, 706,
     713, 720, 727, 732, 739, 744, 751, 756, 763, 768, 775, 780, 787, 645, 652,
     659, 664, 671, 676, 683, 688, 695, 700, 707, 712, 721, 726, 733, 738, 745,
     750, 757, 762, 769, 774, 781, 786 },

   { 830, 837, 842, 849, 854, 861, 868, 875, 880, 887, 892, 899, 904, 911, 916, 923, 928, 937, 942, 949, 954, 961, 966,
     973, 831, 836, 843, 848, 855, 860, 869, 874, 881, 886, 893, 898, 905, 910, 917, 922, 929, 936, 943, 948, 955, 960,
     967, 972, 832, 839, 844, 851, 856, 865, 870, 877, 882, 889, 894, 901, 906, 913, 918, 925, 930, 939, 944, 951, 956,
     963, 968, 975, 833, 838, 845, 850, 857, 864, 871, 876, 883, 888, 895, 900, 907, 912, 919, 924, 931, 938, 945, 950,
     957, 962, 969, 974, 834, 841, 846, 853, 858, 867, 872, 879, 884, 891, 896,
     903, 908, 915, 920, 927, 932, 941, 946, 953, 958, 965, 970, 977, 835, 840,
     847, 852, 859, 866, 873, 878, 885, 890, 897, 902, 909, 914, 921, 926, 933,
     940, 947, 952, 959, 964, 971, 976 },

   { 1020, 1027, 1032, 1039, 1044, 1051, 1056, 1063, 1068, 1075, 1082, 1089,
     1094, 1101, 1106, 1113, 1118, 1125, 1130, 1137, 1142, 1149, 1156, 1163,
     1021, 1026, 1033, 1038, 1045, 1050, 1057, 1062, 1069, 1074, 1083, 1088,
     1095, 1100, 1107, 1112, 1119, 1124, 1131, 1136, 1143, 1148, 1157, 1162,
     1022, 1029, 1034, 1041, 1046, 1053, 1058, 1065, 1070, 1077, 1084, 1091,
     1096, 1103, 1108, 1115, 1120, 1127, 1132, 1139, 1144, 1153, 1158, 1165,
     1023, 1028, 1035, 1040, 1047, 1052, 1059, 1064, 1071, 1076, 1085, 1090,
     1097, 1102, 1109, 1114, 1121, 1126, 1133, 1138, 1145, 1152, 1159, 1164,
     1024, 1031, 1036, 1043, 1048, 1055, 1060, 1067, 1072, 1081, 1086, 1093,
     1098, 1105, 1110, 1117, 1122, 1129, 1134, 1141, 1146, 1155, 1160, 1167,
     1025, 1030, 1037, 1042, 1049, 1054, 1061, 1066, 1073, 1080, 1087, 1092,
     1099, 1104, 1111, 1116, 1123, 1128, 1135, 1140, 1147, 1154, 1161, 1166 },

   { 1208, 1215, 1220, 1229, 1234, 1241, 1246, 1253, 1258, 1265, 1270, 1277,
     1282, 1289, 1296, 1303, 1308, 1315, 1320, 1327, 1332, 1339, 1344, 1351,
     1209, 1214, 1221, 1228, 1235, 1240, 1247, 1252, 1259, 1264, 1271, 1276,
     1283, 1288, 1297, 1302, 1309, 1314, 1321, 1326, 1333, 1338, 1345, 1350,
     1210, 1217, 1224, 1231, 1236, 1243, 1248, 1255, 1260, 1267, 1272, 1279,
     1284, 1291, 1298, 1305, 1310, 1317, 1322, 1329, 1334, 1341, 1346, 1353,
     1211, 1216, 1225, 1230, 1237, 1242, 1249, 1254, 1261, 1266, 1273, 1278,
     1285, 1290, 1299, 1304, 1311, 1316, 1323, 1328, 1335, 1340, 1347, 1352,
     1212, 1219, 1226, 1233, 1238, 1245, 1250, 1257, 1262, 1269, 1274, 1281,
     1286, 1293, 1300, 1307, 1312, 1319, 1324, 1331, 1336, 1343, 1348, 1355,
     1213, 1218, 1227, 1232, 1239, 1244, 1251, 1256, 1263, 1268, 1275, 1280,
     1287, 1292, 1301, 1306, 1313, 1318, 1325, 1330, 1337, 1342, 1349, 1354 },

   { 1398, 1405, 1410, 1417, 1422, 1429, 1434, 1443, 1448, 1455, 1460, 1467,
     1472, 1479, 1484, 1491, 1496, 1503, 1508, 1517, 1522, 1529, 1534, 1541,
     1399, 1404, 1411, 1416, 1423, 1428, 1435, 1442, 1449, 1454, 1461, 1466,
     1473, 1478, 1485, 1490, 1497, 1502, 1509, 1516, 1523, 1528, 1535, 1540,
     1400, 1407, 1412, 1419, 1424, 1431, 1436, 1445, 1450, 1457, 1462, 1469,
     1474, 1481, 1486, 1493, 1498, 1505, 1512, 1519, 1524, 1531, 1536, 1543,
     1401, 1406, 1413, 1418, 1425, 1430, 1437, 1444, 1451, 1456, 1463, 1468,
     1475, 1480, 1487, 1492, 1499, 1504, 1513, 1518, 1525, 1530, 1537, 1542,
     1402, 1409, 1414, 1421, 1426, 1433, 1440, 1447, 1452, 1459, 1464, 1471,
     1476, 1483, 1488, 1495, 1500, 1507, 1514, 1521, 1526, 1533, 1538, 1545,
     1403, 1408, 1415, 1420, 1427, 1432, 1441, 1446, 1453, 1458, 1465, 1470,
     1477, 1482, 1489, 1494, 1501, 1506, 1515, 1520, 1527, 1532, 1539, 1544 },
      
   { 1578, 1587, 1592, 1599, 1604, 1611, 1616, 1623, 1628, 1635, 1640, 1647,
     1652, 1661, 1666, 1673, 1678, 1685, 1690, 1697, 1702, 1709, 1714, 1721,
     1579, 1586, 1593, 1598, 1605, 1610, 1617, 1622, 1629, 1634, 1641, 1646,
     1653, 1660, 1667, 1672, 1679, 1684, 1691, 1696, 1703, 1708, 1715, 1720,
     1580, 1589, 1594, 1601, 1606, 1613, 1618, 1625, 1630, 1637, 1642, 1649,
     1656, 1663, 1668, 1675, 1680, 1687, 1692, 1699, 1704, 1711, 1716, 1723,
     1581, 1588, 1595, 1600, 1607, 1612, 1619, 1624, 1631, 1636, 1643, 1648,
     1657, 1662, 1669, 1674, 1681, 1686, 1693, 1698, 1705, 1710, 1717, 1722,
     1584, 1591, 1596, 1603, 1608, 1615, 1620, 1627, 1632, 1639, 1644, 1651,
     1658, 1665, 1670, 1677, 1682, 1689, 1694, 1701, 1706, 1713, 1718, 1725,
     1585, 1590, 1597, 1602, 1609, 1614, 1621, 1626, 1633, 1638, 1645, 1650,
     1659, 1664, 1671, 1676, 1683, 1688, 1695, 1700, 1707, 1712, 1719, 1724 },

};

static const size_t NOF_VOICE_CODEWORDS = sizeof(VOICE_CODEWORD_BITS) / sizeof(VOICE_CODEWORD_BITS[0]);

voice_codeword
voice_data_unit::long_codeword(size_t n) const
{
   voice_codeword vcw(VOICE_CODEWORD_SZ);
   for(size_t i = 0; i < VOICE_CODEWORD_SZ; ++i) {
      vcw[i] = frame_body()[VOICE_CODEWORD_BITS[n][i]];
   }
   return vcw;
}

void
voice_data_unit::long_codeword(size_t n, const voice_codeword& vcw)
{
   for(size_t i = 0; i < VOICE_CODEWORD_SZ; ++i) {
      frame_body()[VOICE_CODEWORD_BITS[n][i]] = vcw[i];
   }
}

static const size_t LSD_BITS[] = {
   1562, 1563, 1564, 1565, 1566, 1567, 1568, 1569,
   1546, 1547, 1548, 1549, 1550, 1551, 1552, 1553,
};
static const size_t LSD_BITS_SZ = sizeof(LSD_BITS) / sizeof(LSD_BITS[0]);

uint16_t
voice_data_unit::low_speed_data() const
{
   frame_body().extract(LSD_BITS_SZ, LSD_BITS);
}

void
voice_data_unit::low_speed_data(uint16_t lsd)
{
   frame_body().insert(LSD_BITS_SZ, LSD_BITS, lsd);
}

voice_data_unit::voice_data_unit(const bit_vector& frame_body) :
   abstract_data_unit(frame_body)
{
   CHECK_SIZE(frame_body.size(), reqd_frame_size());
}

static const size_t NOF_GOLAY_CODEWORDS = 4;
static const size_t GOLAY_CODEWORD_SZ = 23;
static const size_t GOLAY_VALUE_SZ = 12;

void
voice_data_unit::apply_golay_FEC()
{   
   bit_vector& frame(frame_body());
   for(size_t i = 0; i < NOF_VOICE_CODEWORDS; ++i) {
      for(size_t j = 0; j < NOF_GOLAY_CODEWORDS; ++j) {
         uint32_t cw = frame.extract(GOLAY_CODEWORD_SZ, &VOICE_CODEWORD_BITS[i][j * GOLAY_CODEWORD_SZ]);
         uint16_t val = golay_23_12_decode(val);
         frame.insert(GOLAY_VALUE_SZ, &VOICE_CODEWORD_BITS[i][j * GOLAY_CODEWORD_SZ], val);
      }
   }
}

void
voice_data_unit::compute_golay_FEC()
{
   bit_vector& frame(frame_body());
   for(size_t i = 0; i < NOF_VOICE_CODEWORDS; ++i) {
      for(size_t j = 0; j < NOF_GOLAY_CODEWORDS; ++j) {
         uint16_t val = frame.extract(GOLAY_VALUE_SZ, &VOICE_CODEWORD_BITS[i][j * GOLAY_CODEWORD_SZ]);
         uint32_t cw = golay_23_12_encode(val);
         frame.insert(GOLAY_CODEWORD_SZ, &VOICE_CODEWORD_BITS[i][j * GOLAY_CODEWORD_SZ], cw);
      }
   }
}

static const size_t NOF_HAMMING_CODEWORDS = 3;
static const size_t HAMMING_CODEWORD_SZ = 15;
static const size_t HAMMING_VALUE_SZ = 11;

void
voice_data_unit::apply_hamming_FEC()
{   
   bit_vector& frame(frame_body());
   const size_t ofs = NOF_GOLAY_CODEWORDS * GOLAY_CODEWORD_SZ;
   for(size_t i = 0; i < NOF_VOICE_CODEWORDS; ++i) {
      for(size_t j = 0; j < NOF_HAMMING_CODEWORDS; ++j) {
         uint16_t cw = frame.extract(HAMMING_CODEWORD_SZ, &VOICE_CODEWORD_BITS[i][ofs + j * HAMMING_CODEWORD_SZ]);
         uint16_t val = hamming_15_11_decode(cw);
         frame.insert(HAMMING_VALUE_SZ, &VOICE_CODEWORD_BITS[i][ofs + j * HAMMING_CODEWORD_SZ], val);
      }
   }
}

void
voice_data_unit::compute_hamming_FEC()
{
   bit_vector& frame(frame_body());
   const size_t ofs = NOF_GOLAY_CODEWORDS * GOLAY_CODEWORD_SZ;
   for(size_t i = 0; i < NOF_VOICE_CODEWORDS; ++i) {
      for(size_t j = 0; j < NOF_HAMMING_CODEWORDS; ++j) {
         uint16_t val = frame.extract(HAMMING_VALUE_SZ, &VOICE_CODEWORD_BITS[i][ofs + j * HAMMING_CODEWORD_SZ]);
         uint16_t cw = hamming_15_11_encode(val);
         frame.insert(HAMMING_CODEWORD_SZ, &VOICE_CODEWORD_BITS[i][ofs + j * HAMMING_CODEWORD_SZ], cw);
      }
   }
}

static const size_t NOF_SHORT_HAMMING_CODEWORDS = 24;
static const size_t SHORT_HAMMING_CODEWORD_SZ = 10;
static const size_t SHORT_HAMMING_VALUE_SZ = 6;
static const size_t SHORT_HAMMING_CODEWORD_BITS[NOF_SHORT_HAMMING_CODEWORDS][SHORT_HAMMING_CODEWORD_SZ] = {
   { 410,	411,	412,	413,	414,	415,	416,	417,	418,	419 },
   { 420,	421,	422,	423,	424,	425,	426,	427,	428,	429 },
   { 432,	433,	434,	435,	436,	437,	438,	439,	440,	441 },
   { 442,	443,	444,	445,	446,	447,	448,	449,	450,	451 },
   { 600,	601,	602,	603,	604,	605,	606,	607,	608,	609 },
   { 610,	611,	612,	613,	614,	615,	616,	617,	618,	619 },
   { 620,	621,	622,	623,	624,	625,	626,	627,	628,	629 },
   { 630,	631,	632,	633,	634,	635,	636,	637,	638,	639 },
   { 788,	789,	792,	793,	794,	795,	796,	797,	798,	799 },
   { 800,	801,	802,	803,	804,	805,	806,	807,	808,	809 },
   { 810,	811,	812,	813,	814,	815,	816,	817,	818,	819 },
   { 820,	821,	822,	823,	824,	825,	826,	827,	828,	829 },
   { 978,	979,	980,	981,	982,	983,	984,	985,	986,	987 },
   { 988,	989,	990,	991,	992,	993,	994,	995,	996,	997 },
   { 998,	999,	1000,	1001,	1002,	1003,	1004,	1005,	1008,	1009 },
   { 1010,	1011,	1012,	1013,	1014,	1015,	1016,	1017,	1018,	1019 },
   { 1168,	1169,	1170,	1171,	1172,	1173,	1174,	1175,	1176,	1177 },
   { 1178,	1179,	1180,	1181,	1182,	1183,	1184,	1185,	1186,	1187 },
   { 1188,	1189,	1190,	1191,	1192,	1193,	1194,	1195,	1196,	1197 },
   { 1198,	1199,	1200,	1201,	1202,	1203,	1204,	1205,	1206,	1207 },
   { 1356,	1357,	1358,	1359,	1360,	1361,	1362,	1363,	1364,	1365 },
   { 1368,	1369,	1370,	1371,	1372,	1373,	1374,	1375,	1376,	1377 },
   { 1378,	1379,	1380,	1381,	1382,	1383,	1384,	1385,	1386,	1387 },
   { 1388,	1389,	1390,	1391,	1392,	1393,	1394,	1395,	1396,	1397 }
};

void
voice_data_unit::apply_short_hamming_FEC()
{   
   bit_vector& frame(frame_body());
   for(size_t i = 0; i < NOF_SHORT_HAMMING_CODEWORDS; ++i) {
      uint16_t val = frame.extract(SHORT_HAMMING_VALUE_SZ, SHORT_HAMMING_CODEWORD_BITS[i]);
      uint16_t cw = hamming_15_11_encode(cw);
      frame.insert(SHORT_HAMMING_CODEWORD_SZ, SHORT_HAMMING_CODEWORD_BITS[i], cw);
   }   
}

void
voice_data_unit::compute_short_hamming_FEC()
{   
   bit_vector& frame(frame_body());
   for(size_t i = 0; i < NOF_SHORT_HAMMING_CODEWORDS; ++i) {
      uint16_t cw = frame.extract(SHORT_HAMMING_CODEWORD_SZ, SHORT_HAMMING_CODEWORD_BITS[i]);
      uint16_t val = hamming_15_11_decode(cw);
      frame.insert(SHORT_HAMMING_VALUE_SZ, SHORT_HAMMING_CODEWORD_BITS[i], val);
   }   
}

static const size_t NOF_CYCLIC_CODE_CODEWORDS = 2;
static const size_t CYCLIC_CODE_CODEWORD_SZ = 16;
static const size_t CYCLIC_CODE_VALUE_SZ = 8;
static const size_t CYCLIC_CODE_CODEWORD_BITS[NOF_CYCLIC_CODE_CODEWORDS][CYCLIC_CODE_CODEWORD_SZ] = {
   1546, 1547, 1548, 1549, 1550, 1551, 1552, 1553, 1554, 1555, 1556, 1557, 1558, 1559, 1560, 1561,
   1562, 1563, 1564, 1565, 1566, 1567, 1568, 1569, 1570, 1571, 1572, 1573, 1574, 1575, 1576, 1577,
};

void
voice_data_unit::apply_cyclic_code()
{
   // ToDo: implement me!
}

void
voice_data_unit::compute_cyclic_code()
{
   // ToDo: implement me!
}
