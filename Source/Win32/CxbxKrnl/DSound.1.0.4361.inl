// ******************************************************************
// *
// *    .,-:::::    .,::      .::::::::.    .,::      .:
// *  ,;;;'````'    `;;;,  .,;;  ;;;'';;'   `;;;,  .,;; 
// *  [[[             '[[,,[['   [[[__[[\.    '[[,,[['  
// *  $$$              Y$$$P     $$""""Y$$     Y$$$P    
// *  `88bo,__,o,    oP"``"Yo,  _88o,,od8P   oP"``"Yo,  
// *    "YUMMMMMP",m"       "Mm,""YUMMMP" ,m"       "Mm,
// *
// *   Cxbx->Win32->CxbxKrnl->DSound.1.0.4627.cpp
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

// ******************************************************************
// * DirectSoundCreate
// ******************************************************************
SOOVPA<9> DirectSoundCreate_1_0_4361 =
{
    0,  // Large == 0
    9,  // Count == 9

    {
        // DirectSoundCreate+0x0B : movzx esi, al
        { 0x0B, 0x0F }, // (Offset,Value)-Pair #1
        { 0x0C, 0xB6 }, // (Offset,Value)-Pair #2
        { 0x0D, 0xF0 }, // (Offset,Value)-Pair #3

        // DirectSoundCreate+0x12 : call [addr]
        { 0x12, 0xE8 }, // (Offset,Value)-Pair #4

        // DirectSoundCreate+0x1B : jl +0x13
        { 0x1B, 0x7C }, // (Offset,Value)-Pair #5
        { 0x1C, 0x13 }, // (Offset,Value)-Pair #6

        // DirectSoundCreate+0x27 : sbb ecx, ecx
        { 0x27, 0x1B }, // (Offset,Value)-Pair #7
        { 0x28, 0xC9 }, // (Offset,Value)-Pair #8

        // DirectSoundCreate+0x43 : leave
        { 0x43, 0xC9 }, // (Offset,Value)-Pair #9
    }
};

// ******************************************************************
// * IDirectSound8_CreateSoundBuffer
// ******************************************************************
SOOVPA<9> IDirectSound8_CreateSoundBuffer_1_0_4361 =
{
    0,  // Large == 0
    9,  // Count == 9

    {
        // IDirectSound8_CreateSoundBuffer+0x2A : push 0x24
        { 0x2A, 0x6A }, // (Offset,Value)-Pair #1
        { 0x2B, 0x24 }, // (Offset,Value)-Pair #2

        // IDirectSound8_CreateSoundBuffer+0x3C : call [addr]
        { 0x3C, 0xE8 }, // (Offset,Value)-Pair #3

        // IDirectSound8_CreateSoundBuffer+0x4A : and esi, 0x7FF8FFF2
        { 0x4A, 0x81 }, // (Offset,Value)-Pair #4
        { 0x4B, 0xE6 }, // (Offset,Value)-Pair #5
        { 0x4C, 0xF2 }, // (Offset,Value)-Pair #6
        { 0x4D, 0xFF }, // (Offset,Value)-Pair #7
        { 0x4E, 0xF8 }, // (Offset,Value)-Pair #8
        { 0x4F, 0x7F }, // (Offset,Value)-Pair #9
    }
};

// ******************************************************************
// * IDirectSoundBuffer8_SetBufferData
// ******************************************************************
SOOVPA<10> IDirectSoundBuffer8_SetBufferData_1_0_4361 =
{
    0,  // Large == 0
    10, // Count == 10

    // NOTE: This is actually intercepting CDirectSoundBuffer::SetBufferData(void*, ULONG)

    {
        // IDirectSoundBuffer8_SetBufferData+0x48 : cmp ebx, [eax+0x00B8]
        { 0x4E, 0x3B }, // (Offset,Value)-Pair #1
        { 0x4F, 0x98 }, // (Offset,Value)-Pair #2
        { 0x50, 0xB8 }, // (Offset,Value)-Pair #3

        // IDirectSoundBuffer8_SetBufferData+0x8A : mov ecx, [esi+0x20]
        { 0x8A, 0x8B }, // (Offset,Value)-Pair #4
        { 0x8B, 0x4E }, // (Offset,Value)-Pair #5
        { 0x8C, 0x20 }, // (Offset,Value)-Pair #6

        // IDirectSoundBuffer8_SetBufferData+0x99 : jz +0x0B
        { 0x99, 0x74 }, // (Offset,Value)-Pair #7
        { 0x9A, 0x0B }, // (Offset,Value)-Pair #8

        // IDirectSoundBuffer8_SetBufferData+0xAB : retn 0x0C
        { 0xAB, 0xC2 }, // (Offset,Value)-Pair #9
        { 0xAC, 0x0C }, // (Offset,Value)-Pair #10
    }
};

// ******************************************************************
// * DirectSoundCreate_1_0_4361
// ******************************************************************
OOVPATable DSound_1_0_4361[] =
{
    // DirectSoundCreate
    {
        (OOVPA*)&DirectSoundCreate_1_0_4361,

        xdirectx::EmuDirectSoundCreate,

        #ifdef _DEBUG_TRACE
        "EmuDirectSoundCreate" 
        #endif
    },
    // IDirectSound8::CreateSoundBuffer
    {
        (OOVPA*)&IDirectSound8_CreateSoundBuffer_1_0_4361,

        xdirectx::EmuIDirectSound8_CreateSoundBuffer,

        #ifdef _DEBUG_TRACE
        "EmuIDirectSound8_CreateSoundBuffer" 
        #endif
    },
    // IDirectSoundBuffer8::SetBufferData
    {
        (OOVPA*)&IDirectSoundBuffer8_SetBufferData_1_0_4361,

        xdirectx::EmuIDirectSoundBuffer8_SetBufferData,

        #ifdef _DEBUG_TRACE
        "EmuIDirectSoundBuffer8_SetBufferData" 
        #endif
    },
};

// ******************************************************************
// * DSound_1_0_4361_SIZE
// ******************************************************************
uint32 DSound_1_0_4361_SIZE = sizeof(DSound_1_0_4361);
