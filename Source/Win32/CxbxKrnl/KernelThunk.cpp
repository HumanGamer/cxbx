// ******************************************************************
// *
// *    .,-:::::    .,::      .::::::::.    .,::      .:
// *  ,;;;'````'    `;;;,  .,;;  ;;;'';;'   `;;;,  .,;; 
// *  [[[             '[[,,[['   [[[__[[\.    '[[,,[['  
// *  $$$              Y$$$P     $$""""Y$$     Y$$$P    
// *  `88bo,__,o,    oP"``"Yo,  _88o,,od8P   oP"``"Yo,  
// *    "YUMMMMMP",m"       "Mm,""YUMMMP" ,m"       "Mm,
// *
// *   Cxbx->Win32->CxbxKrnl->KernelThunkTable.cpp
// *
// *  This file is part of the Cxbx project.
// *
// *  Cxbx and Cxbe are free software; you can redistribute them
// *  and/or modify them under the terms of the GNU General Public
// *  License as published by the Free Software Foundation; either
// *  version 2 of the license, or (at your option) any later version.
// *
// *  This program is distributed in the hope that it will be useful,
// *  but WITHOUT ANY WARRANTY; without even the implied warranty of
// *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// *  GNU General Public License for more details.
// *
// *  You should have recieved a copy of the GNU General Public License
// *  along with this program; see the file COPYING.
// *  If not, write to the Free Software Foundation, Inc.,
// *  59 Temple Place - Suite 330, Bostom, MA 02111-1307, USA.
// *
// *  (c) 2002-2003 Aaron Robinson <caustik@caustik.com>
// *
// *  All rights reserved
// *
// ******************************************************************
#define _CXBXKRNL_INTERNAL
#define _XBOXKRNL_LOCAL_

// prevent name collisions
namespace xboxkrnl
{
    #include <xboxkrnl/xboxkrnl.h>
};

#include "Cxbx.h"
#include "Emu.h"

//
// Enable "#define PANIC(numb) numb" if you wish to find out what
// kernel export the application is attempting to call. The app
// will crash at the thunk number (i.e. PsCreateSystemThread:0xFF)
//
// For general use, you should probably just enable the other
// option "#define PANIC(numb) cxbx_panic"
//
//#define PANIC(numb) EmuPanic
#define PANIC(numb) numb

// kernel thunk table
extern "C" CXBXKRNL_API uint32 KernelThunkTable[367] =
{
    (uint32)PANIC(0x0000),                          // 0x0000 (0)
    (uint32)PANIC(0x0001),                          // 0x0001 (1)
    (uint32)PANIC(0x0002),                          // 0x0002 (2)
    (uint32)PANIC(0x0003),                          // 0x0003 (3)
    (uint32)PANIC(0x0004),                          // 0x0004 (4)
    (uint32)PANIC(0x0005),                          // 0x0005 (5)
    (uint32)PANIC(0x0006),                          // 0x0006 (6)
    (uint32)PANIC(0x0007),                          // 0x0007 (7)
    (uint32)PANIC(0x0008),                          // 0x0008 (8)
    (uint32)PANIC(0x0009),                          // 0x0009 (9)
    (uint32)PANIC(0x000A),                          // 0x000A (10)
    (uint32)PANIC(0x000B),                          // 0x000B (11)
    (uint32)PANIC(0x000C),                          // 0x000C (12)
    (uint32)PANIC(0x000D),                          // 0x000D (13)
    (uint32)&xboxkrnl::ExAllocatePool,              // 0x000E (14)
    (uint32)PANIC(0x000F),                          // 0x000F (15)
    (uint32)PANIC(0x0010),                          // 0x0010 (16)
    (uint32)PANIC(0x0011),                          // 0x0011 (17)
    (uint32)PANIC(0x0012),                          // 0x0012 (18)
    (uint32)PANIC(0x0013),                          // 0x0013 (19)
    (uint32)PANIC(0x0014),                          // 0x0014 (20)
    (uint32)PANIC(0x0015),                          // 0x0015 (21)
    (uint32)PANIC(0x0016),                          // 0x0016 (22)
    (uint32)PANIC(0x0017),                          // 0x0017 (23)
    (uint32)&xboxkrnl::ExQueryNonVolatileSetting,   // 0x0018 (24)
    (uint32)PANIC(0x0019),                          // 0x0019 (25)
    (uint32)PANIC(0x001A),                          // 0x001A (26)
    (uint32)PANIC(0x001B),                          // 0x001B (27)
    (uint32)PANIC(0x001C),                          // 0x001C (28)
    (uint32)PANIC(0x001D),                          // 0x001D (29)
    (uint32)PANIC(0x001E),                          // 0x001E (30)
    (uint32)PANIC(0x001F),                          // 0x001F (31)
    (uint32)PANIC(0x0020),                          // 0x0020 (32)
    (uint32)PANIC(0x0021),                          // 0x0021 (33)
    (uint32)PANIC(0x0022),                          // 0x0022 (34)
    (uint32)PANIC(0x0023),                          // 0x0023 (35)
    (uint32)PANIC(0x0024),                          // 0x0024 (36)
    (uint32)&xboxkrnl::FscSetCacheSize,             // 0x0025 (37)
    (uint32)PANIC(0x0026),                          // 0x0026 (38)
    (uint32)PANIC(0x0027),                          // 0x0027 (39)
    (uint32)PANIC(0x0028),                          // 0x0028 (40)
    (uint32)PANIC(0x0029),                          // 0x0029 (41)
    (uint32)PANIC(0x002A),                          // 0x002A (42)
    (uint32)PANIC(0x002B),                          // 0x002B (43)
    (uint32)PANIC(0x002C),                          // 0x002C (44)
    (uint32)PANIC(0x002D),                          // 0x002D (45)
    (uint32)PANIC(0x002E),                          // 0x002E (46)
    (uint32)PANIC(0x002F),                          // 0x002F (47)
    (uint32)PANIC(0x0030),                          // 0x0030 (48)
    (uint32)&xboxkrnl::HalReturnToFirmware,         // 0x0031 (49)
    (uint32)PANIC(0x0032),                          // 0x0032 (50)
    (uint32)PANIC(0x0033),                          // 0x0033 (51)
    (uint32)PANIC(0x0034),                          // 0x0034 (52)
    (uint32)PANIC(0x0035),                          // 0x0035 (53)
    (uint32)PANIC(0x0036),                          // 0x0036 (54)
    (uint32)PANIC(0x0037),                          // 0x0037 (55)
    (uint32)PANIC(0x0038),                          // 0x0038 (56)
    (uint32)PANIC(0x0039),                          // 0x0039 (57)
    (uint32)PANIC(0x003A),                          // 0x003A (58)
    (uint32)PANIC(0x003B),                          // 0x003B (59)
    (uint32)PANIC(0x003C),                          // 0x003C (60)
    (uint32)PANIC(0x003D),                          // 0x003D (61)
    (uint32)PANIC(0x003E),                          // 0x003E (62)
    (uint32)PANIC(0x003F),                          // 0x003F (63)
    (uint32)PANIC(0x0040),                          // 0x0040 (64)
    (uint32)PANIC(0x0041),                          // 0x0041 (65)
    (uint32)&xboxkrnl::IoCreateFile,                // 0x0042 (66)
    (uint32)&xboxkrnl::IoCreateSymbolicLink,        // 0x0043 (67)
    (uint32)PANIC(0x0044),                          // 0x0044 (68)
    (uint32)&xboxkrnl::IoDeleteSymbolicLink,        // 0x0045 (69)
    (uint32)PANIC(0x0046),                          // 0x0046 (70)
    (uint32)PANIC(0x0047),                          // 0x0047 (71)
    (uint32)PANIC(0x0048),                          // 0x0048 (72)
    (uint32)PANIC(0x0049),                          // 0x0049 (73)
    (uint32)PANIC(0x004A),                          // 0x004A (74)
    (uint32)PANIC(0x004B),                          // 0x004B (75)
    (uint32)PANIC(0x004C),                          // 0x004C (76)
    (uint32)PANIC(0x004D),                          // 0x004D (77)
    (uint32)PANIC(0x004E),                          // 0x004E (78)
    (uint32)PANIC(0x004F),                          // 0x004F (79)
    (uint32)PANIC(0x0050),                          // 0x0050 (80)
    (uint32)PANIC(0x0051),                          // 0x0051 (81)
    (uint32)PANIC(0x0052),                          // 0x0052 (82)
    (uint32)PANIC(0x0053),                          // 0x0053 (83)
    (uint32)PANIC(0x0054),                          // 0x0054 (84)
    (uint32)PANIC(0x0055),                          // 0x0055 (85)
    (uint32)PANIC(0x0056),                          // 0x0056 (86)
    (uint32)PANIC(0x0057),                          // 0x0057 (87)
    (uint32)PANIC(0x0058),                          // 0x0058 (88)
    (uint32)PANIC(0x0059),                          // 0x0059 (89)
    (uint32)PANIC(0x005A),                          // 0x005A (90)
    (uint32)PANIC(0x005B),                          // 0x005B (91)
    (uint32)PANIC(0x005C),                          // 0x005C (92)
    (uint32)PANIC(0x005D),                          // 0x005D (93)
    (uint32)PANIC(0x005E),                          // 0x005E (94)
    (uint32)PANIC(0x005F),                          // 0x005F (95)
    (uint32)PANIC(0x0060),                          // 0x0060 (96)
    (uint32)PANIC(0x0061),                          // 0x0061 (97)
    (uint32)PANIC(0x0062),                          // 0x0062 (98)
    (uint32)&xboxkrnl::KeDelayExecutionThread,      // 0x0063 (99)
    (uint32)PANIC(0x0064),                          // 0x0064 (100)
    (uint32)PANIC(0x0065),                          // 0x0065 (101)
    (uint32)PANIC(0x0066),                          // 0x0066 (102)
    (uint32)PANIC(0x0067),                          // 0x0067 (103)
    (uint32)PANIC(0x0068),                          // 0x0068 (104)
    (uint32)PANIC(0x0069),                          // 0x0069 (105)
    (uint32)PANIC(0x006A),                          // 0x006A (106)
    (uint32)&xboxkrnl::KeInitializeDpc,             // 0x006B (107)
    (uint32)PANIC(0x006C),                          // 0x006C (108)
    (uint32)PANIC(0x006D),                          // 0x006D (109)
    (uint32)PANIC(0x006E),                          // 0x006E (110)
    (uint32)PANIC(0x006F),                          // 0x006F (111)
    (uint32)PANIC(0x0070),                          // 0x0070 (112)
    (uint32)&xboxkrnl::KeInitializeTimerEx,         // 0x0071 (113)
    (uint32)PANIC(0x0072),                          // 0x0072 (114)
    (uint32)PANIC(0x0073),                          // 0x0073 (115)
    (uint32)PANIC(0x0074),                          // 0x0074 (116)
    (uint32)PANIC(0x0075),                          // 0x0075 (117)
    (uint32)PANIC(0x0076),                          // 0x0076 (118)
    (uint32)PANIC(0x0077),                          // 0x0077 (119)
    (uint32)PANIC(0x0078),                          // 0x0078 (120)
    (uint32)PANIC(0x0079),                          // 0x0079 (121)
    (uint32)PANIC(0x007A),                          // 0x007A (122)
    (uint32)PANIC(0x007B),                          // 0x007B (123)
    (uint32)PANIC(0x007C),                          // 0x007C (124)
    (uint32)PANIC(0x007D),                          // 0x007D (125)
    (uint32)&xboxkrnl::KeQueryPerformanceCounter,   // 0x007E (126)
    (uint32)&xboxkrnl::KeQueryPerformanceFrequency, // 0x007F (127)
    (uint32)&xboxkrnl::KeQuerySystemTime,           // 0x0080 (128)
    (uint32)PANIC(0x0081),                          // 0x0081 (129)
    (uint32)PANIC(0x0082),                          // 0x0082 (130)
    (uint32)PANIC(0x0083),                          // 0x0083 (131)
    (uint32)PANIC(0x0084),                          // 0x0084 (132)
    (uint32)PANIC(0x0085),                          // 0x0085 (133)
    (uint32)PANIC(0x0086),                          // 0x0086 (134)
    (uint32)PANIC(0x0087),                          // 0x0087 (135)
    (uint32)PANIC(0x0088),                          // 0x0088 (136)
    (uint32)PANIC(0x0089),                          // 0x0089 (137)
    (uint32)PANIC(0x008A),                          // 0x008A (138)
    (uint32)PANIC(0x008B),                          // 0x008B (139)
    (uint32)PANIC(0x008C),                          // 0x008C (140)
    (uint32)PANIC(0x008D),                          // 0x008D (141)
    (uint32)PANIC(0x008E),                          // 0x008E (142)
    (uint32)PANIC(0x008F),                          // 0x008F (143)
    (uint32)PANIC(0x0090),                          // 0x0090 (144)
    (uint32)PANIC(0x0091),                          // 0x0091 (145)
    (uint32)PANIC(0x0092),                          // 0x0092 (146)
    (uint32)PANIC(0x0093),                          // 0x0093 (147)
    (uint32)PANIC(0x0094),                          // 0x0094 (148)
    (uint32)&xboxkrnl::KeSetTimer,                  // 0x0095 (149)
    (uint32)PANIC(0x0096),                          // 0x0096 (150)
    (uint32)PANIC(0x0097),                          // 0x0097 (151)
    (uint32)PANIC(0x0098),                          // 0x0098 (152)
    (uint32)PANIC(0x0099),                          // 0x0099 (153)
    (uint32)PANIC(0x009A),                          // 0x009A (154)
    (uint32)PANIC(0x009B),                          // 0x009B (155)
    (uint32)&xboxkrnl::KeTickCount,                 // 0x009C (156)
    (uint32)PANIC(0x009D),                          // 0x009D (157)
    (uint32)PANIC(0x009E),                          // 0x009E (158)
    (uint32)PANIC(0x009F),                          // 0x009F (159)
    (uint32)PANIC(0x00A0),                          // 0x00A0 (160)
    (uint32)PANIC(0x00A1),                          // 0x00A1 (161)
    (uint32)PANIC(0x00A2),                          // 0x00A2 (162)
    (uint32)PANIC(0x00A3),                          // 0x00A3 (163)
    (uint32)&xboxkrnl::LaunchDataPage,              // 0x00A4 (164)
    (uint32)&xboxkrnl::MmAllocateContiguousMemory,  // 0x00A5 (165)
    (uint32)&xboxkrnl::MmAllocateContiguousMemoryEx,// 0x00A6 (166)
    (uint32)&xboxkrnl::MmAllocateSystemMemory,      // 0x00A7 (167)
    (uint32)PANIC(0x00A8),                          // 0x00A8 (168)
    (uint32)PANIC(0x00A9),                          // 0x00A9 (169)
    (uint32)PANIC(0x00AA),                          // 0x00AA (170)
    (uint32)&xboxkrnl::MmFreeContiguousMemory,      // 0x00AB (171)
    (uint32)&xboxkrnl::MmFreeSystemMemory,          // 0x00AC (172)
    (uint32)PANIC(0x00AD),                          // 0x00AD (173)
    (uint32)PANIC(0x00AE),                          // 0x00AE (174)
    (uint32)PANIC(0x00AF),                          // 0x00AF (175)
    (uint32)PANIC(0x00B0),                          // 0x00B0 (176)
    (uint32)PANIC(0x00B1),                          // 0x00B1 (177)
    (uint32)&xboxkrnl::MmPersistContiguousMemory,   // 0x00B2 (178)
    (uint32)PANIC(0x00B3),                          // 0x00B3 (179)
    (uint32)PANIC(0x00B4),                          // 0x00B4 (180)
    (uint32)&xboxkrnl::MmQueryStatistics,           // 0x00B5 (181)
    (uint32)&xboxkrnl::MmSetAddressProtect,         // 0x00B6 (182)
    (uint32)PANIC(0x00B7),                          // 0x00B7 (183)
    (uint32)&xboxkrnl::NtAllocateVirtualMemory,     // 0x00B8 (184)
    (uint32)PANIC(0x00B9),                          // 0x00B9 (185)
    (uint32)&xboxkrnl::NtClearEvent,                // 0x00BA (186)
    (uint32)&xboxkrnl::NtClose,                     // 0x00BB (187)
    (uint32)PANIC(0x00BC),                          // 0x00BC (188)
    (uint32)&xboxkrnl::NtCreateEvent,               // 0x00BD (189)
    (uint32)&xboxkrnl::NtCreateFile,                // 0x00BE (190)
    (uint32)PANIC(0x00BF),                          // 0x00BF (191)
    (uint32)&xboxkrnl::NtCreateMutant,              // 0x00C0 (192)
    (uint32)PANIC(0x00C1),                          // 0x00C1 (193)
    (uint32)PANIC(0x00C2),                          // 0x00C2 (194)
    (uint32)PANIC(0x00C3),                          // 0x00C3 (195)
    (uint32)PANIC(0x00C4),                          // 0x00C4 (196)
    (uint32)&xboxkrnl::NtDuplicateObject,           // 0x00C5 (197)
    (uint32)PANIC(0x00C6),                          // 0x00C6 (198)
    (uint32)&xboxkrnl::NtFreeVirtualMemory,         // 0x00C7 (199)
    (uint32)PANIC(0x00C8),                          // 0x00C8 (200)
    (uint32)PANIC(0x00C9),                          // 0x00C9 (201)
    (uint32)&xboxkrnl::NtOpenFile,                  // 0x00CA (202)
    (uint32)PANIC(0x00CB),                          // 0x00CB (203)
    (uint32)PANIC(0x00CC),                          // 0x00CC (204)
    (uint32)PANIC(0x00CD),                          // 0x00CD (205)
    (uint32)PANIC(0x00CE),                          // 0x00CE (206)
    (uint32)&xboxkrnl::NtQueryDirectoryFile,        // 0x00CF (207)
    (uint32)PANIC(0x00D0),                          // 0x00D0 (208)
    (uint32)PANIC(0x00D1),                          // 0x00D1 (209)
    (uint32)&xboxkrnl::NtQueryFullAttributesFile,   // 0x00D2 (210)
    (uint32)&xboxkrnl::NtQueryInformationFile,      // 0x00D3 (211)
    (uint32)PANIC(0x00D4),                          // 0x00D4 (212)
    (uint32)PANIC(0x00D5),                          // 0x00D5 (213)
    (uint32)PANIC(0x00D6),                          // 0x00D6 (214)
    (uint32)PANIC(0x00D7),                          // 0x00D7 (215)
    (uint32)PANIC(0x00D8),                          // 0x00D8 (216)
    (uint32)PANIC(0x00D9),                          // 0x00D9 (217)
    (uint32)&xboxkrnl::NtQueryVolumeInformationFile,// 0x00DA (218)
    (uint32)&xboxkrnl::NtReadFile,                  // 0x00DB (219)
    (uint32)PANIC(0x00DC),                          // 0x00DC (220)
    (uint32)&xboxkrnl::NtReleaseMutant,             // 0x00DD (221)
    (uint32)PANIC(0x00DE),                          // 0x00DE (222)
    (uint32)PANIC(0x00DF),                          // 0x00DF (223)
    (uint32)&xboxkrnl::NtResumeThread,              // 0x00E0 (224)
    (uint32)&xboxkrnl::NtSetEvent,                  // 0x00E1 (225)
    (uint32)&xboxkrnl::NtSetInformationFile,        // 0x00E2 (226)
    (uint32)PANIC(0x00E3),                          // 0x00E3 (227)
    (uint32)PANIC(0x00E4),                          // 0x00E4 (228)
    (uint32)PANIC(0x00E5),                          // 0x00E5 (229)
    (uint32)PANIC(0x00E6),                          // 0x00E6 (230)
    (uint32)PANIC(0x00E7),                          // 0x00E7 (231)
    (uint32)&xboxkrnl::NtUserIoApcDispatcher,       // 0x00E8 (232)
    (uint32)PANIC(0x00E9),                          // 0x00E9 (233)
    (uint32)&xboxkrnl::NtWaitForSingleObjectEx,     // 0x00EA (234)
    (uint32)&xboxkrnl::NtWaitForMultipleObjectsEx,  // 0x00EB (235)
    (uint32)&xboxkrnl::NtWriteFile,                 // 0x00EC (236)
    (uint32)PANIC(0x00ED),                          // 0x00ED (237)
    (uint32)&xboxkrnl::NtYieldExecution,            // 0x00EE (238)
    (uint32)PANIC(0x00EF),                          // 0x00EF (239)
    (uint32)PANIC(0x00F0),                          // 0x00F0 (240)
    (uint32)PANIC(0x00F1),                          // 0x00F1 (241)
    (uint32)PANIC(0x00F2),                          // 0x00F2 (242)
    (uint32)PANIC(0x00F3),                          // 0x00F3 (243)
    (uint32)PANIC(0x00F4),                          // 0x00F4 (244)
    (uint32)PANIC(0x00F5),                          // 0x00F5 (245)
    (uint32)PANIC(0x00F6),                          // 0x00F6 (246)
    (uint32)PANIC(0x00F7),                          // 0x00F7 (247)
    (uint32)PANIC(0x00F8),                          // 0x00F8 (248)
    (uint32)PANIC(0x00F9),                          // 0x00F9 (249)
    (uint32)PANIC(0x00FA),                          // 0x00FA (250)
    (uint32)PANIC(0x00FB),                          // 0x00FB (251)
    (uint32)PANIC(0x00FC),                          // 0x00FC (252)
    (uint32)PANIC(0x00FD),                          // 0x00FD (253)
    (uint32)PANIC(0x00FE),                          // 0x00FE (254)
    (uint32)&xboxkrnl::PsCreateSystemThreadEx,      // 0x00FF (255)
    (uint32)PANIC(0x0100),                          // 0x0100 (256)
    (uint32)PANIC(0x0101),                          // 0x0101 (257)
    (uint32)&xboxkrnl::PsTerminateSystemThread,     // 0x0102 (258)
    (uint32)PANIC(0x0103),                          // 0x0103 (259)
    (uint32)&xboxkrnl::RtlAnsiStringToUnicodeString,// 0x0104 (260)
    (uint32)PANIC(0x0105),                          // 0x0105 (261)
    (uint32)PANIC(0x0106),                          // 0x0106 (262)
    (uint32)PANIC(0x0107),                          // 0x0107 (263)
    (uint32)PANIC(0x0108),                          // 0x0108 (264)
    (uint32)PANIC(0x0109),                          // 0x0109 (265)
    (uint32)PANIC(0x010A),                          // 0x010A (266)
    (uint32)PANIC(0x010B),                          // 0x010B (267)
    (uint32)PANIC(0x010C),                          // 0x010C (268)
    (uint32)PANIC(0x010D),                          // 0x010D (269)
    (uint32)PANIC(0x010E),                          // 0x010E (270)
    (uint32)PANIC(0x010F),                          // 0x010F (271)
    (uint32)PANIC(0x0110),                          // 0x0110 (272)
    (uint32)PANIC(0x0111),                          // 0x0111 (273)
    (uint32)PANIC(0x0112),                          // 0x0112 (274)
    (uint32)PANIC(0x0113),                          // 0x0113 (275)
    (uint32)PANIC(0x0114),                          // 0x0114 (276)
    (uint32)&xboxkrnl::RtlEnterCriticalSection,     // 0x0115 (277)
    (uint32)PANIC(0x0116),                          // 0x0116 (278)
    (uint32)PANIC(0x0117),                          // 0x0117 (279)
    (uint32)PANIC(0x0118),                          // 0x0118 (280)
    (uint32)PANIC(0x0119),                          // 0x0119 (281)
    (uint32)PANIC(0x011A),                          // 0x011A (282)
    (uint32)PANIC(0x011B),                          // 0x011B (283)
    (uint32)PANIC(0x011C),                          // 0x011C (284)
    (uint32)PANIC(0x011D),                          // 0x011D (285)
    (uint32)PANIC(0x011E),                          // 0x011E (286)
    (uint32)PANIC(0x011F),                          // 0x011F (287)
    (uint32)PANIC(0x0120),                          // 0x0120 (288)
    (uint32)&xboxkrnl::RtlInitAnsiString,           // 0x0121 (289)
    (uint32)PANIC(0x0122),                          // 0x0122 (290)
    (uint32)&xboxkrnl::RtlInitializeCriticalSection,// 0x0123 (291)
    (uint32)PANIC(0x0124),                          // 0x0124 (292)
    (uint32)PANIC(0x0125),                          // 0x0125 (293)
    (uint32)&xboxkrnl::RtlLeaveCriticalSection,     // 0x0126 (294)
    (uint32)PANIC(0x0127),                          // 0x0127 (295)
    (uint32)PANIC(0x0128),                          // 0x0128 (296)
    (uint32)PANIC(0x0129),                          // 0x0129 (297)
    (uint32)PANIC(0x012A),                          // 0x012A (298)
    (uint32)PANIC(0x012B),                          // 0x012B (299)
    (uint32)PANIC(0x012C),                          // 0x012C (300)
    (uint32)&xboxkrnl::RtlNtStatusToDosError,       // 0x012D (301)
    (uint32)PANIC(0x012E),                          // 0x012E (302)
    (uint32)PANIC(0x012F),                          // 0x012F (303)
    (uint32)&xboxkrnl::RtlTimeFieldsToTime,         // 0x0130 (304)
    (uint32)&xboxkrnl::RtlTimeToTimeFields,         // 0x0131 (305)
    (uint32)PANIC(0x0132),                          // 0x0132 (306)
    (uint32)PANIC(0x0133),                          // 0x0133 (307)
    (uint32)&xboxkrnl::RtlUnicodeStringToAnsiString,// 0x0134 (308)
    (uint32)PANIC(0x0135),                          // 0x0135 (309)
    (uint32)PANIC(0x0136),                          // 0x0136 (310)
    (uint32)PANIC(0x0137),                          // 0x0137 (311)
    (uint32)PANIC(0x0138),                          // 0x0138 (312)
    (uint32)PANIC(0x0139),                          // 0x0139 (313)
    (uint32)PANIC(0x013A),                          // 0x013A (314)
    (uint32)PANIC(0x013B),                          // 0x013B (315)
    (uint32)PANIC(0x013C),                          // 0x013C (316)
    (uint32)PANIC(0x013D),                          // 0x013D (317)
    (uint32)PANIC(0x013E),                          // 0x013E (318)
    (uint32)PANIC(0x013F),                          // 0x013F (319)
    (uint32)PANIC(0x0140),                          // 0x0140 (320)
    (uint32)PANIC(0x0141),                          // 0x0141 (321)
    (uint32)&xboxkrnl::XboxHardwareInfo,            // 0x0142 (322)
    (uint32)PANIC(0x0143),                          // 0x0143 (323)
    (uint32)PANIC(0x0144),                          // 0x0144 (324)
    (uint32)&xboxkrnl::XboxSignatureKey,            // 0x0145 (325)
    (uint32)PANIC(0x0146),                          // 0x0146 (326)
    (uint32)PANIC(0x0147),                          // 0x0147 (327)
    (uint32)PANIC(0x0148),                          // 0x0148 (328)
    (uint32)PANIC(0x0149),                          // 0x0149 (329)
    (uint32)PANIC(0x014A),                          // 0x014A (330)
    (uint32)PANIC(0x014B),                          // 0x014B (331)
    (uint32)PANIC(0x014C),                          // 0x014C (332)
    (uint32)PANIC(0x014D),                          // 0x014D (333)
    (uint32)PANIC(0x014E),                          // 0x014E (334)
    (uint32)&xboxkrnl::XcSHAInit,                   // 0x014F (335)
    (uint32)&xboxkrnl::XcSHAUpdate,                 // 0x0150 (336)
    (uint32)&xboxkrnl::XcSHAFinal,                  // 0x0151 (337)
    (uint32)PANIC(0x0152),                          // 0x0152 (338)
    (uint32)PANIC(0x0153),                          // 0x0153 (339)
    (uint32)PANIC(0x0154),                          // 0x0154 (340)
    (uint32)PANIC(0x0155),                          // 0x0155 (341)
    (uint32)PANIC(0x0156),                          // 0x0156 (342)
    (uint32)PANIC(0x0157),                          // 0x0157 (343)
    (uint32)PANIC(0x0158),                          // 0x0158 (344)
    (uint32)PANIC(0x0159),                          // 0x0159 (345)
    (uint32)PANIC(0x015A),                          // 0x015A (346)
    (uint32)PANIC(0x015B),                          // 0x015B (347)
    (uint32)PANIC(0x015C),                          // 0x015C (348)
    (uint32)PANIC(0x015D),                          // 0x015D (349)
    (uint32)PANIC(0x015E),                          // 0x015E (350)
    (uint32)PANIC(0x015F),                          // 0x015F (351)
    (uint32)PANIC(0x0160),                          // 0x0160 (352)
    (uint32)PANIC(0x0161),                          // 0x0161 (353)
    (uint32)PANIC(0x0162),                          // 0x0162 (354)
    (uint32)PANIC(0x0163),                          // 0x0163 (355)
    (uint32)&xboxkrnl::HalBootSMCVideoMode,         // 0x0164 (356)
    (uint32)PANIC(0x0165),                          // 0x0165 (357)
    (uint32)PANIC(0x0166),                          // 0x0166 (358)
    (uint32)PANIC(0x0167),                          // 0x0167 (359)
    (uint32)PANIC(0x0168),                          // 0x0168 (360)
    (uint32)PANIC(0x0169),                          // 0x0169 (361)
    (uint32)PANIC(0x016A),                          // 0x016A (362)
    (uint32)PANIC(0x016B),                          // 0x016B (363)
    (uint32)PANIC(0x016C),                          // 0x016C (364)
    (uint32)PANIC(0x016D),                          // 0x016D (365)
    (uint32)PANIC(0x016E),                          // 0x016E (366)
};