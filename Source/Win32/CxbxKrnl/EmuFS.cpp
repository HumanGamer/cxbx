// ******************************************************************
// *
// *    .,-:::::    .,::      .::::::::.    .,::      .:
// *  ,;;;'````'    `;;;,  .,;;  ;;;'';;'   `;;;,  .,;; 
// *  [[[             '[[,,[['   [[[__[[\.    '[[,,[['  
// *  $$$              Y$$$P     $$""""Y$$     Y$$$P    
// *  `88bo,__,o,    oP"``"Yo,  _88o,,od8P   oP"``"Yo,  
// *    "YUMMMMMP",m"       "Mm,""YUMMMP" ,m"       "Mm,
// *
// *   Cxbx->Win32->CxbxKrnl->EmuFS.cpp
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

// ******************************************************************
// * prevent name collisions
// ******************************************************************
namespace xboxkrnl
{
    #include <xboxkrnl/xboxkrnl.h>
};

#include "EmuFS.h"
#include "EmuLDT.h"

#undef FIELD_OFFSET     // prevent macro redefinition warnings
#include <windows.h>

// ******************************************************************
// * func: EmuInitFS
// ******************************************************************
void EmuInitFS()
{
    EmuInitLDT();
}

// ******************************************************************
// * func: EmuGenerateFS
// ******************************************************************
void EmuGenerateFS(int TlsAdjust)
{
    NT_TIB         *OrgNtTib;
    xboxkrnl::KPCR *NewPcr;

	uint16 NewFS = -1, OrgFS = -1;

    void *TLSPtr = 0;

    // ******************************************************************
    // * Allocate LDT entry
    // ******************************************************************
    {
        uint32 dwSize = sizeof(xboxkrnl::KPCR);

        NewPcr = (xboxkrnl::KPCR*)new char[dwSize];

        memset(NewPcr, 0, sizeof(*NewPcr));

        NewFS = EmuAllocateLDT((uint32)NewPcr, (uint32)NewPcr + dwSize);
    }

    // ******************************************************************
    // * Obtain "OrgFS"
    // ******************************************************************
    __asm
    {
        // Obtain "OrgFS"
        mov ax, fs
        mov OrgFS, ax

        // Obtain "OrgNtTib"
        mov eax, fs:[0x18]
        mov OrgNtTib, eax

        // Save "NewFS" inside OrgFS.ArbitraryUserPointer.SwapFS
        mov ax, NewFS
        mov fs:[0x14], ax

		// Save "True" inside OrgFS.ArbitraryUserPointer.isOrgFS
		mov ah, 1
		mov fs:[0x16], ah
    }

    // ******************************************************************
    // * Generate TIB
    // ******************************************************************
    {
        xboxkrnl::KTHREAD *KThread = new xboxkrnl::KTHREAD();

        memcpy(&NewPcr->NtTib, OrgNtTib, sizeof(NT_TIB));

        NewPcr->NtTib.Self = &NewPcr->NtTib;

        NewPcr->PrcbData.CurrentThread = KThread;

        NewPcr->Prcb = &NewPcr->PrcbData;

        // Retrieve Win2k/XP TEB.ThreadLocalStoragePointer
        __asm
        {
            mov eax, fs:[0x2C]
            mov TLSPtr, eax
        }

        // HACK: This converts from XBE stack form to Windows form (I guess?!)
        TLSPtr = (void*)((uint32)TLSPtr + TlsAdjust);

        // TlsAdjust == -1 implies that there is no TLS
        if(TlsAdjust == -1)
        {
            TLSPtr = new uint32;
            *(uint32*)TLSPtr = 0;
        }

        NewPcr->PrcbData.CurrentThread->TlsData = TLSPtr;
    }

    // ******************************************************************
    // * Swap into the "NewFS"
    // ******************************************************************
    EmuSwapFS();

    // ******************************************************************
    // * Save "OrgFS" inside NewFS.ArbitraryUserPointer
    // ******************************************************************
    __asm
    {
        mov ax, OrgFS
        mov fs:[0x14], ax   // NewFS.ArbitraryUserPointer

		mov ah, 0
		mov fs:[0x16], ah	// NewFS.ArbitraryUserPointer.isOrgFS
    }

    // ******************************************************************
    // * Save "TLSPtr" inside NewFS.StackBase
    // ******************************************************************
    __asm
    {
        mov eax, TLSPtr
        mov fs:[0x04], eax
    }

    // ******************************************************************
    // * Swap back into the "OrgFS"
    // ******************************************************************
    EmuSwapFS();
}

// ******************************************************************
// * func: EmuCleanupFS
// ******************************************************************
void EmuCleanupFS()
{
    WORD wSelector;

    __asm
    {
        mov ax, fs
        mov wSelector, ax
    }

    EmuDeallocateLDT(wSelector);
}