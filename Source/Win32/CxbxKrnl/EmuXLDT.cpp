// ******************************************************************
// *
// *    .,-:::::    .,::      .::::::::.    .,::      .:
// *  ,;;;'````'    `;;;,  .,;;  ;;;'';;'   `;;;,  .,;; 
// *  [[[             '[[,,[['   [[[__[[\.    '[[,,[['  
// *  $$$              Y$$$P     $$""""Y$$     Y$$$P    
// *  `88bo,__,o,    oP"``"Yo,  _88o,,od8P   oP"``"Yo,  
// *    "YUMMMMMP",m"       "Mm,""YUMMMP" ,m"       "Mm,
// *
// *   Cxbx->Win32->CxbxKrnl->CxbxKrnl.cpp
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
#include "Cxbx.h"
#include "EmuX.h"

// ******************************************************************
// * ntdll wrapped in namespace to avoid collisions
// ******************************************************************
namespace xntdll
{
    #include "xntdll.h"
};

#undef FIELD_OFFSET     // prevent macro redefinition warnings
#include <windows.h>

// ******************************************************************
// * Maximum number of threads this LDT system will handle
// ******************************************************************
#define MAXIMUM_XBOX_THREADS 32

// ******************************************************************
// * Table of free LDT entries
// ******************************************************************
static uint16 FreeLDTEntries[MAXIMUM_XBOX_THREADS];

// ******************************************************************
// * Critical section lock
// ******************************************************************
static CRITICAL_SECTION EmuXLDTLock;

// ******************************************************************
// * func: EmuXInitLDT
// ******************************************************************
void EmuXInitLDT()
{
    InitializeCriticalSection(&EmuXLDTLock);

    for(uint32 v=0;v<MAXIMUM_XBOX_THREADS;v++)
        FreeLDTEntries[v] = (uint16)((v*8) + 7 + 8);
}

// ******************************************************************
// * func: EmuXAllocateLDT
// ******************************************************************
uint16 EmuXAllocateLDT(uint32 dwBaseAddr, uint32 dwLimit)
{
    xntdll::LDT_ENTRY LDTEntry;

    int x=0;

    EnterCriticalSection(&EmuXLDTLock);

    // ******************************************************************
    // * Locate a free LDT entry
    // ******************************************************************
    {
        for(x=0;x<MAXIMUM_XBOX_THREADS;x++)
            if(FreeLDTEntries[x])
                break;

        if(x == MAXIMUM_XBOX_THREADS)
        {
            LeaveCriticalSection(&EmuXLDTLock);

            // TODO: cleaner error handling
            MessageBox(NULL, "Very strange error: Could not locate free LDT entry!", "CxbxKrnl", MB_OK | MB_ICONEXCLAMATION);

            return 0;
        }
    }

    // ******************************************************************
    // * Set up selector information
    // ******************************************************************
    {
        LDTEntry.BaseLow                    = (WORD)(dwBaseAddr & 0xFFFF);
        LDTEntry.HighWord.Bits.BaseMid      = (dwBaseAddr >> 16) & 0xFF;
        LDTEntry.HighWord.Bits.BaseHi       = (dwBaseAddr >> 24) & 0xFF;
	    LDTEntry.HighWord.Bits.Type         = 0x13; // RW data segment
	    LDTEntry.HighWord.Bits.Dpl          = 3;    // user segment
	    LDTEntry.HighWord.Bits.Pres         = 1;    // present
	    LDTEntry.HighWord.Bits.Sys          = 0;
	    LDTEntry.HighWord.Bits.Reserved_0   = 0;
	    LDTEntry.HighWord.Bits.Default_Big  = 1;    // 386 segment
	    LDTEntry.HighWord.Bits.Granularity  = (dwLimit >= 0x00100000) ? 1 : 0;

        if(LDTEntry.HighWord.Bits.Granularity)
            dwLimit >>= 12;

        LDTEntry.LimitLow                   = (WORD)(dwLimit & 0xFFFF);
	    LDTEntry.HighWord.Bits.LimitHi      = (dwLimit >> 16) & 0xF;
    }

    // ******************************************************************
    // * Allocate selector
    // ******************************************************************
    {
        using namespace xntdll;

        if(!NT_SUCCESS(NtSetLdtEntries((x*8)+7+8, LDTEntry, 0, LDTEntry)))
        {
            LeaveCriticalSection(&EmuXLDTLock);

            // TODO: cleaner error handling
            MessageBox(NULL, "Very strange error: Could not set LDT entry!", "CxbxKrnl", MB_OK | MB_ICONEXCLAMATION);

            return 0;
        }
    }

    LeaveCriticalSection(&EmuXLDTLock);

    FreeLDTEntries[x] = 0;

    return (x*8)+7+8;
}

// ******************************************************************
// * func: EmuXDeallocateLDT
// ******************************************************************
void EmuXDeallocateLDT(uint16 wSelector)
{
    xntdll::LDT_ENTRY LDTEntry;

    EnterCriticalSection(&EmuXLDTLock);

    ZeroMemory(&LDTEntry, sizeof(LDTEntry));

    xntdll::NtSetLdtEntries(wSelector, LDTEntry, 0, LDTEntry);

    FreeLDTEntries[(wSelector >> 3)-1] = wSelector;

    LeaveCriticalSection(&EmuXLDTLock);

    return;
}