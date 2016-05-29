/*
 * Raspberry Pi PIC Programmer using GPIO connector
 * https://github.com/WallaceIT/picberry
 * Copyright 2016 Francesco Valla
 * 
 * hex-to-c.py script is Copyright Serge Vakulenko (pic32prog project)
 * https://github.com/sergev/pic32prog
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <vector>

using namespace std;

vector<uint32_t> pe_loader = {
	0x3c07dead, // lui a3, 0xdead
	0x3c06ff20, // lui a2, 0xff20
	0x3c05ff20, // lui al, 0xff20
	// here1
	0x8cc40000, // lw a0, 0 (a2)
	0x8cc30000, // lw v1, 0 (a2)
	0x1067000b, // beq v1, a3, <here3>
	0x00000000, // nop
	0x1060fffb, // beqz v1, <here1>
	0x00000000, // nop
	// here2
	0x8ca20000, // lw v0, 0 (a1)
	0x2463ffff, // addiu v1, v1, -1
	0xac820000, // sw v0, 0 (a0)
	0x24840004, // addiu a0, a0, 4
	0x1460fffb, // bnez v1, <here2>
	0x00000000, // nop
	0x1000fff3, // b <here1>
	0x00000000, // nop
	// here3
	0x3c02a000, // lui v0, 0xa000
	0x34420900, // ori v0, v0, 0x900
	0x00400008, // jr v0
	0x00000000  // nop
};

/*
 * Programming executive for PIC32MX1/MX2 series.
 * RIPE_11_000301.hex
 */
vector<uint32_t> pic32_pemx1 = {
/*0000*/ 0x3c1ca000, 0x279c7ff0, 0x3c1da000, 0x37bd08fc,
/*0010*/ 0x3c08a000, 0x25080be9, 0x01000008, 0x00000000,
/*0020*/ 0x6e0035aa, 0xb20b2513, 0x2203ea8e, 0xeb8eb30a,
/*0030*/ 0x9c402b04, 0xeaeeb709, 0x9c401002, 0x2202ea4f,
/*0040*/ 0x6a01e820, 0xeea346c1, 0x61ed4484, 0x6a00e820,
/*0050*/ 0x1fc00bfc, 0xbfc00bfc, 0x7fffffff, 0xb3042506,
/*0060*/ 0x45af9c40, 0x4484db40, 0xe8a02dfb, 0xff20000c,
/*0070*/ 0x6f00b20b, 0x6103ea83, 0xea8db20a, 0xb30a1002,
/*0080*/ 0x6782e469, 0x2506456f, 0x436fa440, 0xe75ded6f,
/*0090*/ 0x2dfa4481, 0xe8206a00, 0x6500dee0, 0x3fffffff,
/*00a0*/ 0xa0000000, 0xc0000000, 0x1c0064c3, 0x6500037b,
/*00b0*/ 0xe8a06443, 0xd40564f5, 0x2536d504, 0x50219004,
/*00c0*/ 0x68206101, 0xea026a00, 0xb41b6008, 0xb5196770,
/*00d0*/ 0x9dc0436f, 0x4484dcc0, 0x70202bfa, 0xb3166111,
/*00e0*/ 0x60035300, 0xed6cb515, 0xb4151002, 0x1c00e395,
/*00f0*/ 0x94050373, 0x97052a1a, 0x47614f7f, 0x1010d305,
/*0100*/ 0xe9026900, 0xb50c600d, 0xe6a93628, 0x1c009405,
/*0110*/ 0x9aa0037b, 0x93052a0a, 0x43844121, 0x17f1d405,
/*0120*/ 0xe21f9204, 0x2fcad704, 0x64756a00, 0x6500e8a0,
/*0130*/ 0xff200000, 0xa0000008, 0x1fffffff, 0x40000000,
/*0140*/ 0xb50d64c3, 0x67c5b70b, 0x9f406b1f, 0x5300436f,
/*0150*/ 0x46c4de40, 0x550060fa, 0x60036745, 0xed4cb507,
/*0160*/ 0xb3071002, 0x1c00e575, 0x65000373, 0xe8a06443,
/*0170*/ 0xff200000, 0xa0000008, 0x1fffffff, 0x40000000,
/*0180*/ 0x64f4f008, 0x69006704, 0x1c00250a, 0x6790036d,
/*0190*/ 0x93092206, 0xe9634121, 0x4800f400, 0x647461f6,
/*01a0*/ 0x6500e8a0, 0x1c0064c3, 0x6500036b, 0xe8a06443,
/*01b0*/ 0x64f5f00c, 0x6704677d, 0xc3906c00, 0xf7ffc391,
/*01c0*/ 0x18006c1f, 0x672503be, 0xea03b20a, 0xb40a6103,
/*01d0*/ 0x1002ec0d, 0xe0b1b509, 0x03d01800, 0x180067b1,
/*01e0*/ 0x650003d7, 0xde40960c, 0x64756a00, 0x6500e8a0,
/*01f0*/ 0x3fffffff, 0xa0000000, 0xc0000000, 0x6a0064f6,
/*0200*/ 0xd2046b01, 0x6704d305, 0xd2066725, 0xb432214b,
/*0210*/ 0xb5306b1f, 0x9dc0436f, 0xdcc05300, 0x60f94484,
/*0220*/ 0x2c059405, 0x039d1c00, 0xd2046500, 0x6f001002,
/*0230*/ 0x9204d705, 0x67702203, 0xd3064b80, 0x2e0b9606,
/*0240*/ 0x5300b325, 0xb5256003, 0x1002ed6c, 0xe395b424,
/*0250*/ 0x03831c00, 0x49e06790, 0x5120487f, 0x61d64001,
/*0260*/ 0x6b1fb420, 0x436fb51b, 0x53009de0, 0x4484dce0,
/*0270*/ 0x1c0060f9, 0x6500039d, 0x2203d204, 0x4a806750,
/*0280*/ 0x9306d206, 0xb3172b0b, 0x60035300, 0xed6cb513,
/*0290*/ 0xb6131002, 0x1c00e3d5, 0x67900383, 0x49e0487f,
/*02a0*/ 0x17b44001, 0x039d1c00, 0x2a026500, 0x240a9406,
/*02b0*/ 0x9206b30d, 0xdbe06f02, 0xdb402202, 0x48801006,
/*02c0*/ 0x1003db00, 0x9206b508, 0x6a00dd40, 0xe8a06476,
/*02d0*/ 0xff200000, 0xa0000008, 0x1fffffff, 0x40000000,
/*02e0*/ 0xa0000088, 0xff20000c, 0xb54b64e7, 0x9d80b649,
/*02f0*/ 0x6f03f7c1, 0x32723382, 0xdee06702, 0xb547e811,
/*0300*/ 0x33429d40, 0xea313362, 0xd3045b0d, 0x6050d205,
/*0310*/ 0x3768b243, 0x9e80e759, 0x9d80ec80, 0x9da0d406,
/*0320*/ 0x026a1800, 0x1040d507, 0x18009d80, 0xd4060290,
/*0330*/ 0x1800103b, 0x650002a9, 0x9d801037, 0x18009505,
/*0340*/ 0xd40602a0, 0xf3001031, 0x10336b01, 0x5b019d60,
/*0350*/ 0xd30667b8, 0x102d33a4, 0xd4069d80, 0x35ca9dc0,
/*0360*/ 0x02bf1800, 0x1020d505, 0xd4069d80, 0x35ea9de0,
/*0370*/ 0x026d1800, 0x1018d505, 0xd4069d80, 0x18009da0,
/*0380*/ 0xd5050248, 0x9d801011, 0xd406060a, 0x18009da0,
/*0390*/ 0xd50502ac, 0x6c001009, 0x9d80d40b, 0xd406060b,
/*03a0*/ 0x18009da0, 0xd505025c, 0x10036762, 0x10016b00,
/*03b0*/ 0x92046b03, 0x61057207, 0x32403240, 0xea6deb31,
/*03c0*/ 0x720a1005, 0x35406106, 0xea0d32a0, 0xdb40b315,
/*03d0*/ 0x72021796, 0x36406094, 0x34c0b512, 0x6f022302,
/*03e0*/ 0xdd80eced, 0x72019204, 0x2b056106, 0x18009406,
/*03f0*/ 0x95050257, 0x72081784, 0x2b026103, 0x1006920a,
/*0400*/ 0xf77f720c, 0xf77f611c, 0x920b2b1a, 0x1777dd40,
/*0410*/ 0xbf883030, 0xbf80f220, 0xff200000, 0xa0000f64,
/*0420*/ 0xff20000c, 0x34844000, 0x3c05bf81, 0xaca4f400,
/*0430*/ 0x40034800, 0x40074800, 0x00e33023, 0x2cc200f0,
/*0440*/ 0x1440fffc, 0x00000000, 0x3c08bf80, 0x3508f400,
/*0450*/ 0x3c09aa99, 0x35296655, 0x3c0a5566, 0x354a99aa,
/*0460*/ 0x3c0b0000, 0x356b8000, 0xad090010, 0xad0a0010,
/*0470*/ 0xad0b0008, 0x8ca8f400, 0x31038000, 0x1460fffd,
/*0480*/ 0x00000000, 0x00000000, 0x00000000, 0x00000000,
/*0490*/ 0x00000000, 0x240b4000, 0x3c0abf81, 0xad4bf404,
/*04a0*/ 0x8ca9f400, 0x03e00008, 0x31222000, 0x08000349,
/*04b0*/ 0x2404000e, 0x00801821, 0x3c02bf81, 0x24040004,
/*04c0*/ 0xac43f420, 0x08000349, 0x00000000, 0x00801821,
/*04d0*/ 0x3c06bf81, 0x3c02bf81, 0x24040003, 0xacc3f420,
/*04e0*/ 0xac45f440, 0x08000349, 0x00000000, 0x00801821,
/*04f0*/ 0x3c06bf81, 0x3c02bf81, 0x24040001, 0xacc3f420,
/*0500*/ 0xac45f430, 0x08000349, 0x00000000, 0x3c06bf81,
/*0510*/ 0xacc4f420, 0x24034003, 0x3c04bf81, 0x3c02bf81,
/*0520*/ 0xac85f440, 0xac43f400, 0x40034800, 0x40084800,
/*0530*/ 0x01033823, 0x2ce500f0, 0x14a0fffc, 0x00000000,
/*0540*/ 0x3c08bf80, 0x3508f400, 0x3c09aa99, 0x35296655,
/*0550*/ 0x3c0a5566, 0x354a99aa, 0x3c0b0000, 0x356b8000,
/*0560*/ 0xad090010, 0xad0a0010, 0xad0b0008, 0x03e00008,
/*0570*/ 0x00001021, 0x3c04bf81, 0x8c83f400, 0x30628000,
/*0580*/ 0x1440fffd, 0x00000000, 0x00000000, 0x00000000,
/*0590*/ 0x00000000, 0x00000000, 0x24074000, 0x3c06bf81,
/*05a0*/ 0xacc7f404, 0x8c85f400, 0x03e00008, 0x30a22000,
/*05b0*/ 0xb01164a1, 0x32e06f00, 0x67626d00, 0x67c5eb31,
/*05c0*/ 0xea6e6745, 0x329e3442, 0x67a434a4, 0x46c13364,
/*05d0*/ 0x2204ed31, 0x7401f022, 0xed3167b8, 0xeb315608,
/*05e0*/ 0x47e161ef, 0x5700f100, 0x4004d8a0, 0x642161e4,
/*05f0*/ 0x6500e8a0, 0xa0000008, 0x671c64e3, 0xf0106b00,
/*0600*/ 0xf010d870, 0x1800c894, 0x650003ac, 0xf0106a01,
/*0610*/ 0x6463d850, 0x6500e8a0, 0xf01067bc, 0xec11ad74,
/*0620*/ 0xee3167c3, 0xec4e32c2, 0x3688b705, 0x9c40e6f1,
/*0630*/ 0xeb4e3360, 0xcd74f010, 0x6500e8a0, 0xa0000008,
/*0640*/ 0x672464f4, 0x2507450f, 0x1800a180, 0x400f03c6,
/*0650*/ 0x4121ea0f, 0x64742af9, 0x6500e8a0, 0xf010675c,
/*0660*/ 0xe8a0aa54,
/*0664*/ 0xa0000c29, 0xa0000c4d, 0xa0000c59, 0xa0000c1b,
/*0674*/ 0xa0000c33, 0xa0000c3b, 0xa0000c79, 0xa0000c47,
/*0684*/ 0xa0000c87, 0xa0000c69, 0xa0000cad, 0xa0000cb1,
/*0694*/ 0xa0000c97
};

/*
 * Programming executive for PIC32MX3/4/5/6/7 series.
 * Created by hex-to-c.py script from RIPE_06_000201.hex.
 */
vector<uint32_t> pic32_pemx3 = {
/*0000*/ 0x3c1ca000, 0x279c7ff0, 0x3c1da000, 0x37bd08fc,
/*0010*/ 0x3c08a000, 0x250810f0, 0x01000008, 0x00000000,
/*0020*/ 0x3c06bf88, 0x90c86160, 0x3c05bf88, 0x35070040,
/*0030*/ 0xa0c76160, 0x90a46140, 0x2402ffbf, 0x00821824,
/*0040*/ 0xa0a36140, 0x03e00008, 0x00000000, 0x3c06bf88,
/*0050*/ 0x90c86160, 0x2405ffbf, 0x01053824, 0xa0c76160,
/*0060*/ 0x3c03bf88, 0x90646140, 0x00851024, 0xa0626140,
/*0070*/ 0x03e00008, 0x00000000, 0x3c06bf88, 0x90c86161,
/*0080*/ 0x3c05bf88, 0x35070001, 0xa0c76161, 0x90a46141,
/*0090*/ 0x2402fffe, 0x00821824, 0xa0a36141, 0x03e00008,
/*00a0*/ 0x00000000, 0x3c06bf88, 0x90c86161, 0x2405fffe,
/*00b0*/ 0x01053824, 0xa0c76161, 0x3c03bf88, 0x90646141,
/*00c0*/ 0x00851024, 0xa0626141, 0x03e00008, 0x00000000,
/*00d0*/ 0x00052882, 0x10a0001b, 0x00003821, 0x3c061fc0,
/*00e0*/ 0x3c03bfc0, 0x3c027fff, 0x34c92ffc, 0x34682ffc,
/*00f0*/ 0x344bffff, 0x10000006, 0x240affff, 0x8c990000,
/*0100*/ 0x172b000e, 0x00000000, 0x10c0000e, 0x24840004,
/*0110*/ 0x0089c026, 0x00887826, 0x2f0d0001, 0x2dee0001,
/*0120*/ 0x24e70001, 0x01ae6025, 0x1580fff4, 0x00e5302b,
/*0130*/ 0x8c820000, 0x104afff4, 0x00000000, 0x03e00008,
/*0140*/ 0x24020001, 0x03e00008, 0x00001021, 0x3c04ff20,
/*0150*/ 0x8c830000, 0x2c620002, 0x10400003, 0x24040001,
/*0160*/ 0xaf838014, 0x00002021, 0x03e00008, 0x00801021,
/*0170*/ 0x10a00007, 0x3c02ff20, 0x3443000c, 0x8c860000,
/*0180*/ 0x24a5ffff, 0xac660000, 0x14a0fffc, 0x24840004,
/*0190*/ 0x03e00008, 0x00000000, 0x3c083fff, 0x3507ffff,
/*01a0*/ 0x00e4182b, 0x3c02a000, 0x00821025, 0x10600003,
/*01b0*/ 0x00003821, 0x3c09c000, 0x00891021, 0x00402021,
/*01c0*/ 0x10a00007, 0x24a3ffff, 0x2405ffff, 0x908a0000,
/*01d0*/ 0x2463ffff, 0x00ea3821, 0x1465fffc, 0x24840001,
/*01e0*/ 0x00001021, 0x03e00008, 0xacc70000, 0x08000540,
/*01f0*/ 0x00000000, 0x27bdffd0, 0xafb50024, 0xafb40020,
/*0200*/ 0xafb20018, 0xafbf002c, 0xafb60028, 0xafb3001c,
/*0210*/ 0xafb10014, 0xafb00010, 0x00a0a021, 0x00809021,
/*0220*/ 0x10a00024, 0x3c15ff20, 0x3c021fff, 0x3456ffff,
/*0230*/ 0x2a830081, 0x24130080, 0x0283980b, 0x0013282a,
/*0240*/ 0x10a00008, 0x3c06a000, 0x24c40210, 0x02601821,
/*0250*/ 0x8ea70000, 0x2463ffff, 0xac870000, 0x1460fffc,
/*0260*/ 0x24840004, 0x24040080, 0x5264001d, 0x3c05a000,
/*0270*/ 0x10a0000d, 0x00008821, 0x3c09a000, 0x25300210,
/*0280*/ 0x8e050000, 0x02402021, 0x0c000540, 0x26310001,
/*0290*/ 0x26100004, 0x0233182a, 0x14400007, 0x26520004,
/*02a0*/ 0x5460fff8, 0x8e050000, 0x0293a023, 0x1680ffe1,
/*02b0*/ 0x2a830081, 0x00001021, 0x8fbf002c, 0x8fb60028,
/*02c0*/ 0x8fb50024, 0x8fb40020, 0x8fb3001c, 0x8fb20018,
/*02d0*/ 0x8fb10014, 0x8fb00010, 0x03e00008, 0x27bd0030,
/*02e0*/ 0x24a30210, 0x04600003, 0x02c32824, 0x3c084000,
/*02f0*/ 0x00682821, 0x0c000538, 0x02402021, 0x1440ffee,
/*0300*/ 0x0293a023, 0x1680ffca, 0x26520200, 0x1000ffea,
/*0310*/ 0x00001021, 0x3c02a000, 0x24470210, 0x3c06ff20,
/*0320*/ 0x00e02821, 0x2403007f, 0x8cc80000, 0x2463ffff,
/*0330*/ 0xaca80000, 0x0461fffc, 0x24a50004, 0x3c064000,
/*0340*/ 0x00e01821, 0x04e10004, 0x00e62821, 0x3c051fff,
/*0350*/ 0x34a7ffff, 0x00672824, 0x08000538, 0x00000000,
/*0360*/ 0x27bdffe0, 0xafb20018, 0xafb10014, 0xafb00010,
/*0370*/ 0xafbf001c, 0x00a09021, 0x00808021, 0x14a00007,
/*0380*/ 0x00008821, 0x8fbf001c, 0x8fb20018, 0x8fb10014,
/*0390*/ 0x8fb00010, 0x03e00008, 0x27bd0020, 0x02002021,
/*03a0*/ 0x0c000532, 0x26310001, 0x26101000, 0x1040fff5,
/*03b0*/ 0x0232182b, 0x1460fffa, 0x02002021, 0x8fbf001c,
/*03c0*/ 0x8fb20018, 0x8fb10014, 0x8fb00010, 0x03e00008,
/*03d0*/ 0x27bd0020, 0x08000530, 0x00000000, 0x8f828014,
/*03e0*/ 0x27bdffb8, 0xafb7003c, 0xafb60038, 0xafb00020,
/*03f0*/ 0xafbf0040, 0xafb50034, 0xafb40030, 0xafb3002c,
/*0400*/ 0xafb20028, 0xafb10024, 0x00808021, 0x00a0b821,
/*0410*/ 0x00c0b021, 0xa3a00018, 0x10400041, 0xa3a00019,
/*0420*/ 0x00058a02, 0x3c050001, 0x240a0f00, 0x3c0bbf88,
/*0430*/ 0x3c09bf88, 0x340884cf, 0x3c06bf88, 0x34a41021,
/*0440*/ 0x3c03bf88, 0xad6a3034, 0xad2a3038, 0xacc83040,
/*0450*/ 0xac643050, 0x1a200016, 0x32e600ff, 0x3c073fff,
/*0460*/ 0x34f5ffff, 0x3c14a000, 0x3c13c000, 0x24120003,
/*0470*/ 0x02b0682b, 0x02146025, 0x02132821, 0x24070002,
/*0480*/ 0x018d280a, 0x02c02021, 0x24060100, 0x0c0005b8,
/*0490*/ 0xafb20010, 0x00403821, 0x2631ffff, 0x1440003b,
/*04a0*/ 0x26100100, 0x1e20fff3, 0x02b0682b, 0x32e600ff,
/*04b0*/ 0x10c0000e, 0x3c123fff, 0x3651ffff, 0x3c0fa000,
/*04c0*/ 0x0230702b, 0x11c00003, 0x020f2825, 0x3c13c000,
/*04d0*/ 0x02132821, 0x24070002, 0x02c02021, 0x24100003,
/*04e0*/ 0x0c0005b8, 0xafb00010, 0x00403821, 0x10e00033,
/*04f0*/ 0x24020001, 0x8fbf0040, 0x8fb7003c, 0x8fb60038,
/*0500*/ 0x8fb50034, 0x8fb40030, 0x8fb3002c, 0x8fb20028,
/*0510*/ 0x8fb10024, 0x8fb00020, 0x03e00008, 0x27bd0048,
/*0520*/ 0x0c00058a, 0x3404ffff, 0x3c1f3fff, 0x37f9ffff,
/*0530*/ 0x3c18a000, 0x0330a82b, 0x12a00003, 0x02182025,
/*0540*/ 0x3c02c000, 0x02022021, 0x0c0005a1, 0x02e02821,
/*0550*/ 0x0c0005b6, 0x00000000, 0xaec20000, 0x8fbf0040,
/*0560*/ 0x8fb7003c, 0x8fb60038, 0x8fb50034, 0x8fb40030,
/*0570*/ 0x8fb3002c, 0x8fb20028, 0x8fb10024, 0x8fb00020,
/*0580*/ 0x00001021, 0x03e00008, 0x27bd0048, 0x8fbf0040,
/*0590*/ 0x8fb7003c, 0x8fb60038, 0x8fb50034, 0x8fb40030,
/*05a0*/ 0x8fb3002c, 0x8fb20028, 0x8fb10024, 0x8fb00020,
/*05b0*/ 0x24020001, 0x03e00008, 0x27bd0048, 0x02c02021,
/*05c0*/ 0x27a50018, 0x24140003, 0x24060002, 0x24070002,
/*05d0*/ 0x0c0005b8, 0xafb40010, 0x8fbf0040, 0x8fb7003c,
/*05e0*/ 0x8fb60038, 0x8fb50034, 0x8fb40030, 0x8fb3002c,
/*05f0*/ 0x8fb20028, 0x8fb10024, 0x8fb00020, 0x0002102b,
/*0600*/ 0x03e00008, 0x27bd0048, 0x27bdffc8, 0xafb7002c,
/*0610*/ 0xafb50024, 0xafb3001c, 0xafb20018, 0xafb10014,
/*0620*/ 0xafb00010, 0xafbf0034, 0xafbe0030, 0xafb60028,
/*0630*/ 0xafb40020, 0x00a08821, 0x00809021, 0x0000a821,
/*0640*/ 0x24170001, 0x3c10ff20, 0x10a00039, 0x00009821,
/*0650*/ 0x3c02a000, 0x3c031fff, 0x24560210, 0x347effff,
/*0660*/ 0x02c02021, 0x2403007f, 0x8e050000, 0x2463ffff,
/*0670*/ 0xac850000, 0x0461fffc, 0x24840004, 0x12e00046,
/*0680*/ 0x00000000, 0x0000b821, 0x2644fe00, 0x0095980b,
/*0690*/ 0x56600009, 0x2631ff80, 0x3c084000, 0x03d63024,
/*06a0*/ 0x01162821, 0x2ac70000, 0x00c7280b, 0x0c000548,
/*06b0*/ 0x02402021, 0x2631ff80, 0x2a290080, 0x1520001a,
/*06c0*/ 0x26520200, 0x3c0ba000, 0x256a1948, 0x8d540000,
/*06d0*/ 0x2403007f, 0x02802021, 0x8e0c0000, 0x2463ffff,
/*06e0*/ 0xac8c0000, 0x0461fffc, 0x24840004, 0x0c000562,
/*06f0*/ 0x00000000, 0x264dfe00, 0x01a2980b, 0x16600008,
/*0700*/ 0x0040a821, 0x3c184000, 0x2a8f0000, 0x03d47024,
/*0710*/ 0x03142821, 0x01cf280b, 0x0c000548, 0x02402021,
/*0720*/ 0x2631ff80, 0x26520200, 0x1620ffce, 0x02c02021,
/*0730*/ 0x0c000562, 0x0013a02b, 0x0002882b, 0x02348025,
/*0740*/ 0x12000019, 0x3c17ff20, 0x3c16ff20, 0x36c4000c,
/*0750*/ 0x24150002, 0xac950000, 0x52600022, 0x2653fe00,
/*0760*/ 0xac930000, 0x8fbf0034, 0x8fbe0030, 0x8fb7002c,
/*0770*/ 0x8fb60028, 0x8fb50024, 0x8fb40020, 0x8fb3001c,
/*0780*/ 0x8fb20018, 0x8fb10014, 0x8fb00010, 0x00001021,
/*0790*/ 0x03e00008, 0x27bd0038, 0x0c000562, 0x00000000,
/*07a0*/ 0x1000ffb9, 0x0040a821, 0x36f2000c, 0xae400000,
/*07b0*/ 0x8fbf0034, 0x8fbe0030, 0x8fb7002c, 0x8fb60028,
/*07c0*/ 0x8fb50024, 0x8fb40020, 0x8fb3001c, 0x8fb20018,
/*07d0*/ 0x8fb10014, 0x8fb00010, 0x00001021, 0x03e00008,
/*07e0*/ 0x27bd0038, 0xac930000, 0x1000ffdf, 0x8fbf0034,
/*07f0*/ 0x27bdffc0, 0x3c02bf88, 0x24040fc3, 0xafbf0038,
/*0800*/ 0xafb10034, 0xafb00030, 0xac443030, 0x8c433030,
/*0810*/ 0x106400c5, 0x24050001, 0xaf808014, 0x3c09bf80,
/*0820*/ 0x3528f220, 0x8d070000, 0x3c06a000, 0x7cf13b00,
/*0830*/ 0x24d01908, 0x3c0dff20, 0x8dac0000, 0x240b0001,
/*0840*/ 0x000c3402, 0x3185ffff, 0x2cca0010, 0xaf8b8010,
/*0850*/ 0xafa60010, 0x11400006, 0xafa50014, 0x0006c080,
/*0860*/ 0x03107821, 0x8dee0000, 0x01c00008, 0x00000000,
/*0870*/ 0x24050003, 0x2402000f, 0x30a4ffff, 0x10c2002a,
/*0880*/ 0x3c03000f, 0x24040007, 0x10c40094, 0x2408000a,
/*0890*/ 0x10c8009a, 0x3c0c000a, 0x240d0002, 0x10cdffe5,
/*08a0*/ 0x0006cc00, 0x37230002, 0x3c1fff20, 0x0065c80b,
/*08b0*/ 0x37e6000c, 0xacd90000, 0x8fa30010, 0x2ca40001,
/*08c0*/ 0x38780001, 0x2f0f0001, 0x01e47024, 0x15c00091,
/*08d0*/ 0x38650008, 0x2ca70001, 0x00e41024, 0x10400005,
/*08e0*/ 0x386a000c, 0x8fa20028, 0xacc20000, 0x1000ffd2,
/*08f0*/ 0x3c0dff20, 0x2d490001, 0x01244024, 0x5100ffce,
/*0900*/ 0x3c0dff20, 0x8fa2002c, 0xacc20000, 0x1000ffca,
/*0910*/ 0x3c0dff20, 0x8f858014, 0x2402000f, 0x30a4ffff,
/*0920*/ 0x14c2ffd8, 0x3c03000f, 0x3c05ff20, 0x00833825,
/*0930*/ 0x34a6000c, 0xacc70000, 0x1000ffbf, 0x3c0dff20,
/*0940*/ 0xafa0002c, 0x3c03ff20, 0x8c640000, 0x27a6002c,
/*0950*/ 0xafa40018, 0x8c7f0000, 0x03e02821, 0xafbf0014,
/*0960*/ 0x0c0002a6, 0x00000000, 0x8fa60010, 0x1000ffc1,
/*0970*/ 0x00402821, 0x0c000293, 0x00000000, 0x8fa60010,
/*0980*/ 0x1000ffbc, 0x00402821, 0x1000ffba, 0x00002821,
/*0990*/ 0x3c0dff20, 0x8da40000, 0xafa40018, 0x8dac0000,
/*09a0*/ 0x000c5882, 0x01602821, 0x0c0002bd, 0xafab0014,
/*09b0*/ 0x8fa60010, 0x1000ffaf, 0x00402821, 0xafa00028,
/*09c0*/ 0x3c19ff20, 0x8f240000, 0x27a60028, 0xafa40018,
/*09d0*/ 0x8f380000, 0x03002821, 0x0c000337, 0xafb80014,
/*09e0*/ 0x8fa60010, 0x1000ffa3, 0x00402821, 0x1000ffa1,
/*09f0*/ 0x24050201, 0x3c0fff20, 0x8de40000, 0xafa40018,
/*0a00*/ 0x8dee0000, 0x01c02821, 0x0c000274, 0xafae0014,
/*0a10*/ 0x8fa60010, 0x1000ff97, 0x00402821, 0x3c02ff20,
/*0a20*/ 0x8c460000, 0x00c02021, 0x0c000318, 0xafa60018,
/*0a30*/ 0x8fa60010, 0x1000ff8f, 0x00402821, 0x0c000335,
/*0a40*/ 0x00000000, 0x8fa60010, 0x1000ff8a, 0x00402821,
/*0a50*/ 0x3c1fff20, 0x8fe40000, 0xafa40018, 0x8ff90000,
/*0a60*/ 0x03202821, 0x0c0002bb, 0xafb9001c, 0x8fa60010,
/*0a70*/ 0x1000ff80, 0x00402821, 0x3c0aff20, 0x8d440000,
/*0a80*/ 0xafa40018, 0x8d490000, 0x00094082, 0x01002821,
/*0a90*/ 0x0c0003c2, 0xafa80014, 0x8fa60010, 0x1000ff75,
/*0aa0*/ 0x00402821, 0x3c05ff20, 0x8ca70000, 0x24050002,
/*0ab0*/ 0x0007280b, 0x1000ff6f, 0xafa70018, 0x3c04ff20,
/*0ac0*/ 0x8c830000, 0x00602021, 0x0c000305, 0xafa30018,
/*0ad0*/ 0x8fa60010, 0x1000ff67, 0x00402821, 0x30a4ffff,
/*0ae0*/ 0x3c030007, 0x3c05ff20, 0x00833825, 0x34a6000c,
/*0af0*/ 0xacc70000, 0x1000ff50, 0x3c0dff20, 0x3c0bff20,
/*0b00*/ 0x022c5025, 0x3569000c, 0xad2a0000, 0x1000ff4a,
/*0b10*/ 0x3c0dff20, 0x8fa40018, 0x0c00029c, 0x8fa50014,
/*0b20*/ 0x1000ff45, 0x3c0dff20, 0x1000ff3c, 0xaf858014,
/*0b30*/ 0x03e00008, 0x00001021, 0x34844000, 0x3c05bf81,
/*0b40*/ 0xaca4f400, 0x40034800, 0x40074800, 0x00e33023,
/*0b50*/ 0x2cc200f0, 0x1440fffc, 0x00000000, 0x3c08bf80,
/*0b60*/ 0x3508f400, 0x3c09aa99, 0x35296655, 0x3c0a5566,
/*0b70*/ 0x354a99aa, 0x3c0b0000, 0x356b8000, 0xad090010,
/*0b80*/ 0xad0a0010, 0xad0b0008, 0x8ca8f400, 0x31038000,
/*0b90*/ 0x1460fffd, 0x00000000, 0x00000000, 0x00000000,
/*0ba0*/ 0x00000000, 0x00000000, 0x240b4000, 0x3c0abf81,
/*0bb0*/ 0xad4bf404, 0x8ca9f400, 0x03e00008, 0x31222000,
/*0bc0*/ 0x0800050e, 0x2404000e, 0x00801821, 0x3c02bf81,
/*0bd0*/ 0x24040004, 0xac43f420, 0x0800050e, 0x00000000,
/*0be0*/ 0x00803021, 0x3c02bf81, 0x3c03bf81, 0x24040003,
/*0bf0*/ 0xac46f420, 0xac65f440, 0x0800050e, 0x00000000,
/*0c00*/ 0x00803021, 0x3c02bf81, 0x3c03bf81, 0x24040001,
/*0c10*/ 0xac46f420, 0xac65f430, 0x0800050e, 0x00000000,
/*0c20*/ 0x3c06bf81, 0xacc4f420, 0x3c03bf81, 0x24044003,
/*0c30*/ 0x3c02bf81, 0xac65f440, 0xac44f400, 0x40034800,
/*0c40*/ 0x40084800, 0x01033823, 0x2ce500f0, 0x14a0fffc,
/*0c50*/ 0x00000000, 0x3c08bf80, 0x3508f400, 0x3c09aa99,
/*0c60*/ 0x35296655, 0x3c0a5566, 0x354a99aa, 0x3c0b0000,
/*0c70*/ 0x356b8000, 0xad090010, 0xad0a0010, 0xad0b0008,
/*0c80*/ 0x03e00008, 0x00001021, 0x3c04bf81, 0x8c83f400,
/*0c90*/ 0x30628000, 0x1440fffd, 0x00000000, 0x00000000,
/*0ca0*/ 0x00000000, 0x00000000, 0x00000000, 0x24074000,
/*0cb0*/ 0x3c06bf81, 0xacc7f404, 0x8c85f400, 0x03e00008,
/*0cc0*/ 0x30a22000, 0x3c02a000, 0x24490210, 0x00004021,
/*0cd0*/ 0x00082200, 0x3083ffff, 0x00002821, 0x24060007,
/*0ce0*/ 0x00056040, 0x00a35826, 0x39871021, 0x7c0b5620,
/*0cf0*/ 0x05400002, 0x30e5ffff, 0x3185ffff, 0x00036840,
/*0d00*/ 0x24c6ffff, 0x04c1fff6, 0x31a3ffff, 0x25080001,
/*0d10*/ 0x29030100, 0xad250000, 0x1460ffed, 0x25290004,
/*0d20*/ 0x03e00008, 0x00000000, 0x27bdffe8, 0xafbf0010,
/*0d30*/ 0xa784801c, 0x0c000571, 0xaf808018, 0x8fbf0010,
/*0d40*/ 0x24020001, 0x27bd0018, 0x03e00008, 0xaf828018,
/*0d50*/ 0x9786801c, 0x308b00ff, 0x7ccc3a00, 0x016c5026,
/*0d60*/ 0x3c09a000, 0x000a3880, 0x25280210, 0x00e82021,
/*0d70*/ 0x8c850000, 0x00061200, 0x00451826, 0x03e00008,
/*0d80*/ 0xa783801c, 0x27bdffe0, 0xafb10014, 0xafb00010,
/*0d90*/ 0xafbf001c, 0xafb20018, 0x00808821, 0x10a00008,
/*0da0*/ 0x24b0ffff, 0x2412ffff, 0x92240000, 0x2610ffff,
/*0db0*/ 0x0c000594, 0x26310001, 0x5612fffc, 0x92240000,
/*0dc0*/ 0x8fbf001c, 0x8fb20018, 0x8fb10014, 0x8fb00010,
/*0dd0*/ 0x03e00008, 0x27bd0020, 0x03e00008, 0x9782801c,
/*0de0*/ 0x0007c040, 0x3c08a000, 0x03077821, 0x8d0a194c,
/*0df0*/ 0x000f7180, 0x01ca4021, 0x27bdffe8, 0x00e04821,
/*0e00*/ 0x3c0abf88, 0x24071000, 0x240d0080, 0x240c0040,
/*0e10*/ 0x3c0bbf88, 0x34038000, 0x3c02bf88, 0xad4d3034,
/*0e20*/ 0xafbf0010, 0xad0c0018, 0xad673004, 0xac433008,
/*0e30*/ 0x00803821, 0x91190000, 0x7f2401c0, 0x1480fffd,
/*0e40*/ 0x8fae0028, 0x3c02bf88, 0x352b00c0, 0x240d0038,
/*0e50*/ 0x240cffff, 0x24030003, 0x3c1f4000, 0xad0e0000,
/*0e60*/ 0xad0d0014, 0xad0c0024, 0xad433034, 0xac4b3038,
/*0e70*/ 0x04a10004, 0x00bf1021, 0x3c0f1fff, 0x35eaffff,
/*0e80*/ 0x00aa1024, 0x3c054000, 0xad020030, 0x04e10004,
/*0e90*/ 0x00e51021, 0x3c041fff, 0x3498ffff, 0x00f81024,
/*0ea0*/ 0xad020040, 0xad060090, 0x8d070090, 0x01202021,
/*0eb0*/ 0xad070060, 0x8d060060, 0x24050002, 0xad060050,
/*0ec0*/ 0x0c0005f5, 0x00003021, 0x8fbf0010, 0x03e00008,
/*0ed0*/ 0x27bd0018, 0x00045040, 0x3c08a000, 0x01444821,
/*0ee0*/ 0x8d04194c, 0x00093980, 0x00e44821, 0x24030080,
/*0ef0*/ 0x240200ff, 0xad220024, 0x00007821, 0xad230008,
/*0f00*/ 0x0006502b, 0xad230018, 0x10a00031, 0x00000000,
/*0f10*/ 0x240b0001, 0x10ab0013, 0x24030001, 0x8d2c0050,
/*0f20*/ 0x1580002d, 0x24070100, 0x8d2d0060, 0x11a00002,
/*0f30*/ 0x24030100, 0x8d230060, 0x8d2e0090, 0x11c00002,
/*0f40*/ 0x24040100, 0x8d240090, 0x00e3102b, 0x00e2180a,
/*0f50*/ 0x0064c821, 0x2738ffff, 0x0304001b, 0x008001f4,
/*0f60*/ 0x00001812, 0x2463ffff, 0x240e0001, 0x240d0004,
/*0f70*/ 0x240c0080, 0x240bffff, 0x8d240020, 0x30980003,
/*0f80*/ 0x7c880080, 0x17000017, 0x7c8700c0, 0x14e00010,
/*0f90*/ 0x00000000, 0x11000008, 0x00000000, 0x10ae000c,
/*0fa0*/ 0x00000000, 0x50600015, 0x240f0003, 0xad2d0024,
/*0fb0*/ 0x2463ffff, 0xad2c0018, 0x1140ffef, 0x00000000,
/*0fc0*/ 0x24c6ffff, 0x14cbffec, 0x00000000, 0x240f0005,
/*0fd0*/ 0x03e00008, 0x01e01021, 0x8d270050, 0x1000ffd2,
/*0fe0*/ 0x00000000, 0x7c850000, 0x10a0fff9, 0x240f0002,
/*0ff0*/ 0x240f0001, 0x03e00008, 0x01e01021, 0x03e00008,
/*1000*/ 0x01e01021,
/*1004*/ 0x0201cdab, 0xa00013bc, 0xa00013a4, 0xa0001378,
/*1014*/ 0xa0001350, 0xa000133c, 0xa000131c, 0xa00012f4,
/*1024*/ 0xa00012ec, 0xa00012bc, 0xa0001290, 0xa0001288,
/*1034*/ 0xa0001274, 0xa0001240, 0xa0001170, 0xa0001170,
/*1044*/ 0xa0001214,
/*1048*/ 0xa0000010,
/*104c*/ 0xbf883060
};

/*
 * Programming executive for PIC32MZ series.
 * Created by hex-to-c.py script from RIPE_15_000504.hex.
 */
vector<uint32_t> pic32_pemz = {
/*0000*/ 0x3c1ca000, 0x279c7ff0, 0x3c1da000, 0x37bd08fc,
/*0010*/ 0x3c08a000, 0x25081020, 0x01000008, 0x00000000,
/*0020*/ 0x27bdffe8, 0xafbf0014, 0x0c0004f0, 0x00000000,
/*0030*/ 0x8fbf0014, 0x03e00008, 0x27bd0018, 0x27bdffd8,
/*0040*/ 0xafbf0024, 0x3c02ff20, 0x8c430000, 0xafa30010,
/*0050*/ 0x8c430000, 0xafa30014, 0x8c430000, 0xafa30018,
/*0060*/ 0x8c420000, 0xafa2001c, 0x0c0004fb, 0x27a50010,
/*0070*/ 0x8fbf0024, 0x03e00008, 0x27bd0028, 0x27bdffe8,
/*0080*/ 0xafbf0014, 0x3c02a000, 0x24422000, 0x00402821,
/*0090*/ 0x24470800, 0x3c06ff20, 0x8cc30000, 0xac430000,
/*00a0*/ 0x24420004, 0x5447fffd, 0x8cc30000, 0x3c02a000,
/*00b0*/ 0x24422000, 0x04400005, 0x7ca5e000, 0x3c024000,
/*00c0*/ 0x3c05a000, 0x24a52000, 0x00a22821, 0x0c000510,
/*00d0*/ 0x00000000, 0x8fbf0014, 0x03e00008, 0x27bd0018,
/*00e0*/ 0x27bdffc8, 0xafbf0034, 0xafb70030, 0xafb6002c,
/*00f0*/ 0xafb50028, 0xafb40024, 0xafb30020, 0xafb2001c,
/*0100*/ 0xafb10018, 0xafb00014, 0x10a00044, 0x00a0a821,
/*0110*/ 0x00808821, 0x3c13a000, 0x26732000, 0x3c174000,
/*0120*/ 0x0277b821, 0x7e76e000, 0x2ab40201, 0x24020200,
/*0130*/ 0x02b4100b, 0x1840000a, 0x0040a021, 0x02601021,
/*0140*/ 0x00142880, 0x02652821, 0x3c04ff20, 0x8c830000,
/*0150*/ 0xac430000, 0x24420004, 0x1445fffc, 0x00000000,
/*0160*/ 0x24020200, 0x12820009, 0x26820003, 0x2a920000,
/*0170*/ 0x0292100a, 0x00029083, 0x00129080, 0x1e40000c,
/*0180*/ 0x00008021, 0x080002b6, 0x0214102a, 0x06600002,
/*0190*/ 0x02c02821, 0x02e02821, 0x0c000510, 0x02202021,
/*01a0*/ 0x1440001f, 0x26310800, 0x080002c3, 0x02b4a823,
/*01b0*/ 0x00102880, 0x02202021, 0x0c0004fb, 0x02652821,
/*01c0*/ 0x14400017, 0x26100004, 0x0212102a, 0x1440fff8,
/*01d0*/ 0x26310010, 0x0214102a, 0x5040000c, 0x02b4a823,
/*01e0*/ 0x00109080, 0x02729021, 0x02202021, 0x0c0004f0,
/*01f0*/ 0x8e450000, 0x1440000a, 0x26100001, 0x26310004,
/*0200*/ 0x1614fff9, 0x26520004, 0x02b4a823, 0x16a0ffc7,
/*0210*/ 0x2ab40201, 0x080002c8, 0x00001021, 0x00001021,
/*0220*/ 0x8fbf0034, 0x8fb70030, 0x8fb6002c, 0x8fb50028,
/*0230*/ 0x8fb40024, 0x8fb30020, 0x8fb2001c, 0x8fb10018,
/*0240*/ 0x8fb00014, 0x03e00008, 0x27bd0038, 0x27bdffe0,
/*0250*/ 0xafbf001c, 0xafb20018, 0xafb10014, 0x10a0000a,
/*0260*/ 0xafb00010, 0x00a09021, 0x00808821, 0x00008021,
/*0270*/ 0x0c00051b, 0x02202021, 0x10400003, 0x26100001,
/*0280*/ 0x1612fffb, 0x26314000, 0x8fbf001c, 0x8fb20018,
/*0290*/ 0x8fb10014, 0x8fb00010, 0x03e00008, 0x27bd0020,
/*02a0*/ 0x27bdffe8, 0xafbf0014, 0x0c000524, 0x00000000,
/*02b0*/ 0x8fbf0014, 0x03e00008, 0x27bd0018, 0x00052882,
/*02c0*/ 0x10a00011, 0x00001021, 0x8c830000, 0x2402ffff,
/*02d0*/ 0x1462000b, 0x2406ffff, 0x080002fb, 0x00001021,
/*02e0*/ 0x8c830000, 0x54660008, 0x24020001, 0x24420001,
/*02f0*/ 0x1445fffb, 0x24840004, 0x03e00008, 0x00001021,
/*0300*/ 0x03e00008, 0x24020001, 0x03e00008, 0x00000000,
/*0310*/ 0x10a00007, 0x00001021, 0x3c06ff20, 0x8c830000,
/*0320*/ 0xacc3000c, 0x24420001, 0x1445fffc, 0x24840004,
/*0330*/ 0x03e00008, 0x00000000, 0x27bdffb8, 0xafbf0044,
/*0340*/ 0xafb70040, 0xafb6003c, 0xafb50038, 0xafb40034,
/*0350*/ 0xafb30030, 0xafb2002c, 0xafb10028, 0xafb00024,
/*0360*/ 0x00808021, 0x00a0b821, 0xa3a00018, 0xa3a00019,
/*0370*/ 0x8f828010, 0x10400035, 0x00c09021, 0x3c040001,
/*0380*/ 0x24841021, 0x24050010, 0x0c0005a2, 0x340684cf,
/*0390*/ 0x00178a02, 0x1a200013, 0x32e600ff, 0x3c134000,
/*03a0*/ 0x3c15c000, 0x3c16a000, 0x24140003, 0x0213102b,
/*03b0*/ 0x50400002, 0x02152821, 0x02162825, 0xafb40010,
/*03c0*/ 0x02402021, 0x24060100, 0x0c000635, 0x24070002,
/*03d0*/ 0x1440002f, 0x2631ffff, 0x1620fff4, 0x26100100,
/*03e0*/ 0x32e600ff, 0x10c00011, 0x24020003, 0x3c024000,
/*03f0*/ 0x0202102b, 0x50400004, 0x3c05c000, 0x3c05a000,
/*0400*/ 0x08000343, 0x02052825, 0x02052821, 0x24020003,
/*0410*/ 0xafa20010, 0x02402021, 0x0c000635, 0x24070002,
/*0420*/ 0x5440001c, 0x24020001, 0x24020003, 0xafa20010,
/*0430*/ 0x02402021, 0x27a50018, 0x24060002, 0x0c000635,
/*0440*/ 0x24070002, 0x08000365, 0x0002102b, 0x0c000598,
/*0450*/ 0x3404ffff, 0x3c024000, 0x0202102b, 0x50400004,
/*0460*/ 0x3c04c000, 0x3c04a000, 0x0800035d, 0x02042025,
/*0470*/ 0x02042021, 0x0c00056c, 0x02e02821, 0x0c00055d,
/*0480*/ 0x00000000, 0xae420000, 0x08000365, 0x00001021,
/*0490*/ 0x24020001, 0x8fbf0044, 0x8fb70040, 0x8fb6003c,
/*04a0*/ 0x8fb50038, 0x8fb40034, 0x8fb30030, 0x8fb2002c,
/*04b0*/ 0x8fb10028, 0x8fb00024, 0x03e00008, 0x27bd0048,
/*04c0*/ 0x3c024000, 0x0082102b, 0x10400004, 0x3c02c000,
/*04d0*/ 0x3c02a000, 0x08000378, 0x00822025, 0x00822021,
/*04e0*/ 0x10a00009, 0x00852821, 0x00801021, 0x00001821,
/*04f0*/ 0x90470000, 0x24420001, 0x1445fffd, 0x00671821,
/*0500*/ 0x08000384, 0xacc30000, 0x00001821, 0xacc30000,
/*0510*/ 0x03e00008, 0x00001021, 0x27bdffc0, 0xafbf003c,
/*0520*/ 0xafbe0038, 0xafb70034, 0xafb60030, 0xafb5002c,
/*0530*/ 0xafb40028, 0xafb30024, 0xafb20020, 0xafb1001c,
/*0540*/ 0xafb00018, 0x00809021, 0x14a00037, 0x00a08021,
/*0550*/ 0x080003d9, 0x0000a021, 0x8c830000, 0xac430000,
/*0560*/ 0x24420004, 0x1445fffc, 0x00000000, 0x14c00004,
/*0570*/ 0x00000000, 0x0c00054d, 0x00000000, 0x00409821,
/*0580*/ 0x56600001, 0x2654f800, 0x56800007, 0x2610fe00,
/*0590*/ 0x06200002, 0x7ea5e000, 0x8fa50010, 0x0c00052b,
/*05a0*/ 0x02402021, 0x2610fe00, 0x2a020200, 0x14400019,
/*05b0*/ 0x26550800, 0x02c01021, 0x02c0b821, 0x26c50800,
/*05c0*/ 0x3c04ff20, 0x8c830000, 0xac430000, 0x24420004,
/*05d0*/ 0x1445fffc, 0x00000000, 0x0c00054d, 0x00000000,
/*05e0*/ 0x10400002, 0x00409821, 0x0240a021, 0x56800007,
/*05f0*/ 0x2610fe00, 0x06c00002, 0x7ee5e000, 0x02de2821,
/*0600*/ 0x0c00052b, 0x02a02021, 0x2610fe00, 0x080003c6,
/*0610*/ 0x26b20800, 0x02a09021, 0x12000012, 0x00003021,
/*0620*/ 0x080003d5, 0x02201021, 0x0000a021, 0x24060001,
/*0630*/ 0x00009821, 0x3c11a000, 0x26312000, 0x3c1e4000,
/*0640*/ 0x023e1021, 0xafa20010, 0x3c16a000, 0x26d62800,
/*0650*/ 0x02201021, 0x0220a821, 0x26250800, 0x08000396,
/*0660*/ 0x3c04ff20, 0x0c00054d, 0x00000000, 0x14400005,
/*0670*/ 0x24030002, 0x1680001d, 0x3c02ff20, 0x080003ed,
/*0680*/ 0x00000000, 0x3c02ff20, 0xac43000c, 0x12800005,
/*0690*/ 0x2652f800, 0x3c02ff20, 0xac54000c, 0x080003ef,
/*06a0*/ 0x00001021, 0x3c02ff20, 0xac52000c, 0x080003ef,
/*06b0*/ 0x00001021, 0xac40000c, 0x00001021, 0x8fbf003c,
/*06c0*/ 0x8fbe0038, 0x8fb70034, 0x8fb60030, 0x8fb5002c,
/*06d0*/ 0x8fb40028, 0x8fb30024, 0x8fb20020, 0x8fb1001c,
/*06e0*/ 0x8fb00018, 0x03e00008, 0x27bd0040, 0xac43000c,
/*06f0*/ 0x080003e6, 0x3c02ff20, 0x3c02ff20, 0x8c420000,
/*0700*/ 0x2c430002, 0x50600004, 0x24020001, 0xaf828010,
/*0710*/ 0x03e00008, 0x00001021, 0x03e00008, 0x00000000,
/*0720*/ 0x27bdffd0, 0xafbf002c, 0xafb40028, 0xafb30024,
/*0730*/ 0xafb20020, 0xafb1001c, 0xafb00018, 0x3c03bf81,
/*0740*/ 0x24020fc3, 0xac621030, 0x8c631030, 0x54620003,
/*0750*/ 0xaf808010, 0x24020001, 0xaf828010, 0x3c02bf80,
/*0760*/ 0x8c540020, 0x3c13a000, 0x267310a4, 0x7e943b00,
/*0770*/ 0x3c02000a, 0x0282a025, 0x3c02ff20, 0x8c510000,
/*0780*/ 0x00118402, 0x2e02000e, 0x1040006a, 0x3231ffff,
/*0790*/ 0x00101080, 0x02621021, 0x8c420000, 0x00400008,
/*07a0*/ 0x00000000, 0xa0001110, 0xa0001154, 0xa000116c,
/*07b0*/ 0xa00010dc, 0xa0001128, 0xa0001138, 0xa00011b4,
/*07c0*/ 0xa0001248, 0xa00011d4, 0xa0001190, 0xa0001314,
/*07d0*/ 0xa0001224, 0xa00011fc, 0xa00010f8, 0x3c02ff20,
/*07e0*/ 0x8c520000, 0x8c450000, 0x0c000248, 0x02402021,
/*07f0*/ 0x0800049b, 0x2403000a, 0x3c02ff20, 0x8c520000,
/*0800*/ 0x0c00024f, 0x02402021, 0x0800049b, 0x2403000a,
/*0810*/ 0x3c02ff20, 0x8c520000, 0x0c00025f, 0x02402021,
/*0820*/ 0x0800049b, 0x2403000a, 0x0c0002e8, 0x00000000,
/*0830*/ 0x0800049b, 0x2403000a, 0x3c02ff20, 0x8c520000,
/*0840*/ 0x02402021, 0x0c0002d3, 0x02202821, 0x0800049b,
/*0850*/ 0x2403000a, 0x3c02ff20, 0x8c520000, 0x52400042,
/*0860*/ 0x24020002, 0x0800049a, 0x00001021, 0x3c02ff20,
/*0870*/ 0x8c520000, 0x8c510000, 0x00118882, 0x02402021,
/*0880*/ 0x0c000386, 0x02202821, 0x0800049b, 0x2403000a,
/*0890*/ 0x3c02ff20, 0x8c520000, 0x8c510000, 0x00118882,
/*08a0*/ 0x02402021, 0x0c000278, 0x02202821, 0x0800049b,
/*08b0*/ 0x2403000a, 0x3c02ff20, 0x8c520000, 0x8c510000,
/*08c0*/ 0x02402021, 0x0c0002ef, 0x02202821, 0x0800049b,
/*08d0*/ 0x2403000a, 0xafa00010, 0x3c02ff20, 0x8c520000,
/*08e0*/ 0x8c510000, 0x02402021, 0x02202821, 0x0c00030e,
/*08f0*/ 0x27a60010, 0x0800049b, 0x2403000a, 0xafa00014,
/*0900*/ 0x3c02ff20, 0x8c520000, 0x8c510000, 0x02402021,
/*0910*/ 0x02202821, 0x0c000370, 0x27a60014, 0x0800049b,
/*0920*/ 0x2403000a, 0x0c0003fe, 0x00000000, 0x0800049b,
/*0930*/ 0x2403000a, 0x24020007, 0x1602000a, 0x24030003,
/*0940*/ 0x08000494, 0x3c020007, 0x24030504, 0x3c020007,
/*0950*/ 0x00621825, 0x3c02ff20, 0xac43000c, 0x0800041f,
/*0960*/ 0x3c02ff20, 0x24020003, 0x2403000a, 0x16030005,
/*0970*/ 0x24030002, 0x3c02ff20, 0xac54000c, 0x0800041f,
/*0980*/ 0x3c02ff20, 0x5203ff7d, 0x3c02ff20, 0x14400003,
/*0990*/ 0x00101c00, 0x080004a8, 0x00002021, 0x24040002,
/*09a0*/ 0x00832025, 0x3c03ff20, 0xac64000c, 0x24030001,
/*09b0*/ 0x16030008, 0x24030008, 0x5440ff70, 0x3c02ff20,
/*09c0*/ 0x02402021, 0x0c000304, 0x02202821, 0x0800041f,
/*09d0*/ 0x3c02ff20, 0x16030007, 0x2403000c, 0x1440ff67,
/*09e0*/ 0x3c02ff20, 0x8fa30010, 0xac43000c, 0x0800041f,
/*09f0*/ 0x3c02ff20, 0x5603ff61, 0x3c02ff20, 0x1440ff5f,
/*0a00*/ 0x3c02ff20, 0x8fa30014, 0xac43000c, 0x0800041f,
/*0a10*/ 0x3c02ff20, 0x0800049a, 0x00001021, 0x3c02bf80,
/*0a20*/ 0xac440600, 0x34844000, 0xac440600, 0x3c02bf80,
/*0a30*/ 0xac400610, 0x3c08bf80, 0x35080600, 0x3c09aa99,
/*0a40*/ 0x35296655, 0x3c0a5566, 0x354a99aa, 0x3c0b0000,
/*0a50*/ 0x356b8000, 0x3c0c0000, 0x358c8080, 0xad090010,
/*0a60*/ 0xad0a0010, 0xad0c0090, 0x00000000, 0xad090010,
/*0a70*/ 0xad0a0010, 0xad0b0008, 0x3c03bf80, 0x8c620600,
/*0a80*/ 0x30428000, 0x1440fffd, 0x00000000, 0x00000000,
/*0a90*/ 0x00000000, 0x00000000, 0x00000000, 0x24034000,
/*0aa0*/ 0x3c02bf80, 0xac430604, 0x3c02bf80, 0x8c420600,
/*0ab0*/ 0x03e00008, 0x30422000, 0x03e00008, 0x00001021,
/*0ac0*/ 0x27bdffe8, 0xafbf0014, 0x3c02bf80, 0xac440620,
/*0ad0*/ 0x3c02bf80, 0xac450630, 0x0c0004c7, 0x24040001,
/*0ae0*/ 0x8fbf0014, 0x03e00008, 0x27bd0018, 0x27bdffe8,
/*0af0*/ 0xafbf0014, 0x3c02bf80, 0xac440620, 0x8ca30000,
/*0b00*/ 0x3c02bf80, 0xac430630, 0x8ca30004, 0x3c02bf80,
/*0b10*/ 0xac430640, 0x8ca30008, 0x3c02bf80, 0xac430650,
/*0b20*/ 0x8ca3000c, 0x3c02bf80, 0xac430660, 0x0c0004c7,
/*0b30*/ 0x24040002, 0x8fbf0014, 0x03e00008, 0x27bd0018,
/*0b40*/ 0x27bdffe8, 0xafbf0014, 0x3c02bf80, 0xac440620,
/*0b50*/ 0x3c02bf80, 0xac450670, 0x0c0004c7, 0x24040003,
/*0b60*/ 0x8fbf0014, 0x03e00008, 0x27bd0018, 0x27bdffe8,
/*0b70*/ 0xafbf0014, 0x3c02bf80, 0xac440620, 0x0c0004c7,
/*0b80*/ 0x24040004, 0x8fbf0014, 0x03e00008, 0x27bd0018,
/*0b90*/ 0x27bdffe8, 0xafbf0014, 0x0c0004c7, 0x2404000e,
/*0ba0*/ 0x8fbf0014, 0x03e00008, 0x27bd0018, 0x3c02bf80,
/*0bb0*/ 0xac440620, 0x3c02bf80, 0xac450670, 0x3c02bf80,
/*0bc0*/ 0x24030003, 0xac430600, 0x24034003, 0xac430600,
/*0bd0*/ 0x3c02bf80, 0xac400610, 0x3c08bf80, 0x35080600,
/*0be0*/ 0x3c09aa99, 0x35296655, 0x3c0a5566, 0x354a99aa,
/*0bf0*/ 0x3c0b0000, 0x356b8000, 0x3c0c0000, 0x358c8080,
/*0c00*/ 0xad090010, 0xad0a0010, 0xad0c0090, 0x00000000,
/*0c10*/ 0xad090010, 0xad0a0010, 0xad0b0008, 0x00000000,
/*0c20*/ 0x00000000, 0x00000000, 0x00000000, 0x03e00008,
/*0c30*/ 0x00001021, 0x3c03bf80, 0x8c620600, 0x30428000,
/*0c40*/ 0x1440fffd, 0x00000000, 0x00000000, 0x00000000,
/*0c50*/ 0x00000000, 0x00000000, 0x24034000, 0x3c02bf80,
/*0c60*/ 0xac430604, 0x3c02bf80, 0x8c420600, 0x03e00008,
/*0c70*/ 0x30422000, 0x03e00008, 0x97828014, 0x308400ff,
/*0c80*/ 0x97828014, 0x00021a02, 0x00831826, 0x00031880,
/*0c90*/ 0x3c05a000, 0x24a52000, 0x00651821, 0x8c630000,
/*0ca0*/ 0x00021200, 0x00621026, 0x03e00008, 0xa7828014,
/*0cb0*/ 0x27bdffe0, 0xafbf001c, 0xafb10018, 0xafb00014,
/*0cc0*/ 0x10a00007, 0x00808021, 0x00858821, 0x92040000,
/*0cd0*/ 0x0c00055f, 0x26100001, 0x5611fffd, 0x92040000,
/*0ce0*/ 0x8fbf001c, 0x8fb10018, 0x8fb00014, 0x03e00008,
/*0cf0*/ 0x27bd0020, 0x3c07a000, 0x24e72000, 0x00003021,
/*0d00*/ 0x24080100, 0x00062200, 0x3084ffff, 0x24030008,
/*0d10*/ 0x00001021, 0x00822826, 0x7c052e20, 0x04a10004,
/*0d20*/ 0x00021040, 0x38421021, 0x0800058d, 0x3042ffff,
/*0d30*/ 0x3042ffff, 0x2463ffff, 0x10600003, 0x00042040,
/*0d40*/ 0x08000585, 0x3084ffff, 0xace20000, 0x24c60001,
/*0d50*/ 0x14c8ffec, 0x24e70004, 0x03e00008, 0x00000000,
/*0d60*/ 0x27bdffe8, 0xafbf0014, 0xaf808018, 0x0c00057d,
/*0d70*/ 0xa7848014, 0x24020001, 0xaf828018, 0x8fbf0014,
/*0d80*/ 0x03e00008, 0x27bd0018, 0x24031f00, 0x3c02bf81,
/*0d90*/ 0xac431034, 0x24a5ffff, 0x00052a00, 0x3c02bf81,
/*0da0*/ 0xac451038, 0x3c02bf81, 0xac461040, 0x3c02bf81,
/*0db0*/ 0xac441050, 0x03e00008, 0x00000000, 0x24020040,
/*0dc0*/ 0xac820018, 0x24031000, 0x3c02bf81, 0xac431004,
/*0dd0*/ 0x34038000, 0x3c02bf81, 0xac431008, 0x8c820000,
/*0de0*/ 0x30420080, 0x1440fffd, 0x00000000, 0x03e00008,
/*0df0*/ 0x00000000, 0x04830003, 0x3c024000, 0x03e00008,
/*0e00*/ 0x7c82e000, 0x03e00008, 0x00821021, 0x03e00008,
/*0e10*/ 0x3c020001, 0x27bdffd0, 0xafbf002c, 0xafb50028,
/*0e20*/ 0xafb40024, 0xafb30020, 0xafb2001c, 0xafb10018,
/*0e30*/ 0xafb00014, 0x00a09821, 0x00c09021, 0x00041180,
/*0e40*/ 0x00042200, 0x00822023, 0x3c11bf81, 0x26311060,
/*0e50*/ 0x02248821, 0x240200ff, 0xae220024, 0x24020080,
/*0e60*/ 0xae220008, 0xae220018, 0x10a00051, 0x00001021,
/*0e70*/ 0x24020001, 0x50a20022, 0x24140001, 0x8e220050,
/*0e80*/ 0x10400004, 0x00000000, 0x8e350050, 0x080005e8,
/*0e90*/ 0x00000000, 0x0c0005c3, 0x00000000, 0x0040a821,
/*0ea0*/ 0x8e220060, 0x10400004, 0x00000000, 0x8e340060,
/*0eb0*/ 0x080005f1, 0x00000000, 0x0c0005c3, 0x00000000,
/*0ec0*/ 0x0040a021, 0x8e220090, 0x10400004, 0x00000000,
/*0ed0*/ 0x8e220090, 0x080005fa, 0x0295182b, 0x0c0005c3,
/*0ee0*/ 0x00000000, 0x0295182b, 0x02a3a00b, 0x2694ffff,
/*0ef0*/ 0x0282a021, 0x0282001b, 0x004001f4, 0x0000a012,
/*0f00*/ 0x2682ffff, 0x02403821, 0x24080001, 0x240a0004,
/*0f10*/ 0x24090080, 0x8e260020, 0x8e250020, 0x7ca50040,
/*0f20*/ 0x8e230020, 0x7c6300c0, 0x8e240020, 0x7c840080,
/*0f30*/ 0x7cd00004, 0x7cb00844, 0x7c901084, 0x7c7018c4,
/*0f40*/ 0x32030003, 0x50600006, 0x32030008, 0x32040001,
/*0f50*/ 0x50800017, 0x24020002, 0x0800062c, 0x24020001,
/*0f60*/ 0x14600010, 0x32040004, 0x10800008, 0x00000000,
/*0f70*/ 0x5268000f, 0x00001021, 0x5040000d, 0x24020003,
/*0f80*/ 0xae2a0024, 0xae290018, 0x2442ffff, 0x1240ffe1,
/*0f90*/ 0x00000000, 0x10e00005, 0x24e7ffff, 0x08000605,
/*0fa0*/ 0x00000000, 0x0800062c, 0x00001021, 0x24020005,
/*0fb0*/ 0x8fbf002c, 0x8fb50028, 0x8fb40024, 0x8fb30020,
/*0fc0*/ 0x8fb2001c, 0x8fb10018, 0x8fb00014, 0x03e00008,
/*0fd0*/ 0x27bd0030, 0x27bdffd0, 0xafbf002c, 0xafb50028,
/*0fe0*/ 0xafb40024, 0xafb30020, 0xafb2001c, 0xafb10018,
/*0ff0*/ 0xafb00014, 0x00808821, 0x00a0a021, 0x00c0a821,
/*1000*/ 0x00e09021, 0x00071180, 0x00078200, 0x02021023,
/*1010*/ 0x3c10bf81, 0x26101060, 0x02028021, 0x3c13bf81,
/*1020*/ 0x24020080, 0xae621034, 0x0c0005af, 0x02002021,
/*1030*/ 0x8e020000, 0x8fa30040, 0x7c620804, 0xae020000,
/*1040*/ 0x24020038, 0xae020014, 0x2402ffff, 0xae020024,
/*1050*/ 0x24020007, 0xae621034, 0x364300c0, 0x3c02bf81,
/*1060*/ 0xac431038, 0x0c0005bd, 0x02802021, 0xae020030,
/*1070*/ 0x0c0005bd, 0x02202021, 0xae020040, 0xae150090,
/*1080*/ 0x8e020090, 0xae020060, 0x8e020060, 0xae020050,
/*1090*/ 0x02402021, 0x24050002, 0x0c0005c5, 0x00003021,
/*10a0*/ 0x8fbf002c, 0x8fb50028, 0x8fb40024, 0x8fb30020,
/*10b0*/ 0x8fb2001c, 0x8fb10018, 0x8fb00014, 0x03e00008,
/*10c0*/ 0x27bd0030,
/*10c4*/ 0x0504cdab, 0xbf811060,
/*10cc*/ 0xa0002000, 0x00001000, 0x00000000, 0x00000000
};