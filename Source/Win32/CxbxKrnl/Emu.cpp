// ******************************************************************
// *
// *    .,-:::::    .,::      .::::::::.    .,::      .:
// *  ,;;;'````'    `;;;,  .,;;  ;;;'';;'   `;;;,  .,;; 
// *  [[[             '[[,,[['   [[[__[[\.    '[[,,[['  
// *  $$$              Y$$$P     $$""""Y$$     Y$$$P    
// *  `88bo,__,o,    oP"``"Yo,  _88o,,od8P   oP"``"Yo,  
// *    "YUMMMMMP",m"       "Mm,""YUMMMP" ,m"       "Mm,
// *
// *   Cxbx->Win32->CxbxKrnl->Emu.cpp
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

#include "Emu.h"
#include "EmuFS.h"
#include "EmuD3D8.h"
#include "EmuKrnl.h"
#include "EmuShared.h"
#include "HLEDataBase.h"

// ******************************************************************
// * global / static
// ******************************************************************
extern DWORD g_dwTlsAdjust = 0;

// ******************************************************************
// * static
// ******************************************************************
static void EmuInstallWrappers(OOVPATable *OovpaTable, uint32 OovpaTableSize, void (*Entry)(), Xbe::Header *XbeHeader);
static int ExitException(LPEXCEPTION_POINTERS e);

// ******************************************************************
// * func: DllMain
// ******************************************************************
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if(fdwReason == DLL_PROCESS_ATTACH)
        EmuShared::Init();
    
    if(fdwReason == DLL_PROCESS_DETACH)
        EmuShared::Cleanup();

    return TRUE;
}

// ******************************************************************
// * func: EmuNoFunc
// ******************************************************************
extern "C" CXBXKRNL_API void NTAPI EmuNoFunc()
{
    EmuSwapFS();   // Win2k/XP FS

    printf("Emu (0x%.08X): EmuNoFunc()\n", GetCurrentThreadId());

    EmuSwapFS();   // XBox FS
}

// ******************************************************************
// * func: EmuCleanThread
// ******************************************************************
static void EmuCleanThread()
{
    if(EmuIsXboxFS())
        EmuSwapFS();    // Win2k/XP FS

    EmuCleanupFS();

    ExitThread(0);
}

// ******************************************************************
// * func: EmuInit
// ******************************************************************
extern "C" CXBXKRNL_API void NTAPI EmuInit(uint32 TlsAdjust, Xbe::LibraryVersion *LibraryVersion, DebugMode DbgMode, char *szDebugFilename, Xbe::Header *XbeHeader, uint32 XbeHeaderSize, void (*Entry)())
{
    g_dwTlsAdjust = TlsAdjust;

    // ******************************************************************
    // * Store this thread handle
    // ******************************************************************
    {
        HANDLE hThread = NULL;
        DWORD  hThreadId = GetCurrentThreadId();

        DuplicateHandle(GetCurrentProcess(), GetCurrentThread(), GetCurrentProcess(), &hThread, 0, FALSE, DUPLICATE_SAME_ACCESS);

        ThreadList::Insert(hThread, hThreadId);
    }

    // ******************************************************************
    // * debug console allocation (if configured)
    // ******************************************************************
    if(DbgMode == DM_CONSOLE)
    {
        if(AllocConsole())
        {
            freopen("CONOUT$", "wt", stdout);

            SetConsoleTitle("Cxbx : Kernel Debug Console");

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
            
            printf("CxbxKrnl (0x%.08X): Debug console allocated (DM_CONSOLE).\n", GetCurrentThreadId());
        }
    }
    else if(DbgMode == DM_FILE)
    {
        FreeConsole();

        freopen(szDebugFilename, "wt", stdout);

        printf("Emu (0x%.08X): Debug console allocated (DM_FILE).\n", GetCurrentThreadId());
    }
    else
    {
        FreeConsole();

        freopen("NUL", "wt", stdout);
    }

    // ******************************************************************
    // * debug trace
    // ******************************************************************
    {
        #ifdef _DEBUG_TRACE
        printf("CxbxKrnl (0x%.08X): _DEBUG_TRACE enabled.\n", GetCurrentThreadId());

        printf("Emu: EmuInit\n"
               "(\n"
               "   TlsAdjust           : 0x%.08X\n"
               "   LibraryVersion      : 0x%.08X\n"
               "   DebugConsole        : 0x%.08X\n"
               "   DebugFilename       : \"%s\"\n"
               "   XBEHeader           : 0x%.08X\n"
               "   XBEHeaderSize       : 0x%.08X\n"
               "   Entry               : 0x%.08X\n"
               ");\n",
               TlsAdjust, LibraryVersion, DbgMode, szDebugFilename, XbeHeader, XbeHeaderSize, Entry);

        #else
        printf("CxbxKrnl (0x%.08X): _DEBUG_TRACE disabled.\n", GetCurrentThreadId());
        #endif
    }

    // ******************************************************************
    // * Load the necessary pieces of XBEHeader
    // ******************************************************************
    {
        Xbe::Header *MemXbeHeader = (Xbe::Header*)0x00010000;

        uint32 old_protection = 0;

        VirtualProtect(MemXbeHeader, 0x1000, PAGE_READWRITE, &old_protection);

        // we sure hope we aren't corrupting anything necessary for an .exe to survive :]
        MemXbeHeader->dwSizeofHeaders   = XbeHeader->dwSizeofHeaders;
        MemXbeHeader->dwCertificateAddr = XbeHeader->dwCertificateAddr;
        MemXbeHeader->dwPeHeapReserve   = XbeHeader->dwPeHeapReserve;
        MemXbeHeader->dwPeHeapCommit    = XbeHeader->dwPeHeapCommit;

        memcpy(&MemXbeHeader->dwInitFlags, &XbeHeader->dwInitFlags, sizeof(XbeHeader->dwInitFlags));

        memcpy((void*)XbeHeader->dwCertificateAddr, &((uint08*)XbeHeader)[XbeHeader->dwCertificateAddr - 0x00010000], sizeof(Xbe::Certificate));
    }

    // ******************************************************************
    // * Initialize all components
    // ******************************************************************
    {
        EmuInitFS();

        EmuGenerateFS(TlsAdjust);
    }

    // ******************************************************************
    // * Initialize OpenXDK emulation
    // ******************************************************************
    if(LibraryVersion == 0)
        printf("Emu: Detected OpenXDK application...\n");

    // ******************************************************************
    // * Initialize Microsoft XDK emulation
    // ******************************************************************
    if(LibraryVersion != 0)
    {
        printf("Emu: Detected Microsoft XDK application...\n");

        uint32 dwLibraryVersions = XbeHeader->dwLibraryVersions;
        uint32 dwHLEEntries      = HLEDataBaseSize/sizeof(HLEData);

        for(uint32 v=0;v<dwLibraryVersions;v++)
        {
            uint16 MajorVersion = LibraryVersion[v].wMajorVersion;
            uint16 MinorVersion = LibraryVersion[v].wMinorVersion;
            uint16 BuildVersion = LibraryVersion[v].wBuildVersion;

            char szLibraryName[9] = {0};

            for(uint32 c=0;c<8;c++)
                szLibraryName[c] = LibraryVersion[v].szName[c];

            printf("Emu: Locating HLE Information for %s %d.%d.%d...", szLibraryName, MajorVersion, MinorVersion, BuildVersion);

            bool found=false;

            for(uint32 d=0;d<dwHLEEntries;d++)
            {
                if(BuildVersion != HLEDataBase[d].BuildVersion || MinorVersion != HLEDataBase[d].MinorVersion || MajorVersion != HLEDataBase[d].MajorVersion || strcmp(szLibraryName, HLEDataBase[d].Library) != 0)
                    continue;

                found = true;

                printf("Found\n");

                EmuInstallWrappers(HLEDataBase[d].OovpaTable, HLEDataBase[d].OovpaTableSize, Entry, XbeHeader);
            }

            if(!found)
                printf("Skipped\n");
        }

        EmuD3DInit(XbeHeader, XbeHeaderSize);
    }

    printf("Emu (0x%.08X): Initial thread starting.\n", GetCurrentThreadId());

    // ******************************************************************
    // * Entry Point
    // ******************************************************************
    __try
    {
        EmuSwapFS();   // XBox FS

        Entry();

        EmuSwapFS();   // Win2k/XP FS
    }
    __except(EmuException(GetExceptionInformation()))
    {
        printf("Emu: WARNING!! Problem with ExceptionFilter\n");
    }

    printf("Emu (0x%.08X): Initial thread ended.\n", GetCurrentThreadId());

    fflush(stdout);

    EmuCleanThread();

    return;
}

// ******************************************************************
// * func: EmuCleanup
// ******************************************************************
extern "C" CXBXKRNL_API void NTAPI EmuCleanup(const char *szErrorMessage)
{
    // ******************************************************************
    // * Print out ErrorMessage (if exists)
    // ******************************************************************
    if(szErrorMessage != NULL)
    {
        char buffer[255];

        sprintf(buffer, "CxbxKrnl: Recieved Fatal Message \"%s\"\n", szErrorMessage);

        printf("%s", buffer);

        MessageBox(NULL, buffer, "CxbxKrnl", MB_OK | MB_ICONEXCLAMATION);
    }

    // ******************************************************************
    // * Suspend and Redirect all Threads
    // ******************************************************************
    {
        ThreadList *tl = 0;

        for(tl = ThreadList::pFirst;tl != NULL;tl = tl->pNext)
        {
            // ignore current thread
            DWORD cur = GetCurrentThreadId();
            DWORD cmp = tl->dwThreadId;

            if(cmp == 0)
                break;

            if(cmp == cur)
                continue;

            SuspendThread(tl->hThread);

            CONTEXT Context;

            Context.ContextFlags = CONTEXT_CONTROL;

            GetThreadContext(tl->hThread, &Context);
            
            Context.Eip = (DWORD)EmuCleanThread;

            Context.ContextFlags = CONTEXT_CONTROL;

            SetThreadContext(tl->hThread, &Context);
        }
    }

    // ******************************************************************
    // * Resume all Threads
    // ******************************************************************
    {
        ThreadList *tl = ThreadList::pFirst;

        while(tl != NULL)
        {
            // ignore current thread
            DWORD cur = GetCurrentThreadId();
            DWORD cmp = tl->dwThreadId;

            if(cmp == 0)
                break;

            if(cmp != cur)
            {
                ResumeThread(tl->hThread);

                DWORD dwTerm = 0;
                GetExitCodeThread(tl->hThread, &dwTerm);

                while(dwTerm == STILL_ACTIVE)
                {
                    Sleep(50);
                    GetExitCodeThread(tl->hThread, &dwTerm);
                }

                printf("Cxbx: Thread 0x%.08X Terminated\n", tl->hThread);
            }

            ThreadList *pTmpDel = tl;

            tl = tl->pNext;

            delete pTmpDel;
        }
    }

    printf("CxbxKrnl: Terminating Process\n");
    fflush(stdout);

    EmuD3DCleanup();

    EmuCleanupFS();

    __try
    {
        ExitProcess(0);
    }
    __except(ExitException(GetExceptionInformation()))
    {
        printf("Emu: WARNING!! Problem with ExitExceptionFilter\n");
    }

    return;
}

// ******************************************************************
// * func: EmuPanic
// ******************************************************************
extern "C" CXBXKRNL_API void NTAPI EmuPanic()
{
    if(EmuIsXboxFS())
        EmuSwapFS();   // Win2k/XP FS

    printf("Emu (0x%.08X): EmuPanic()\n", GetCurrentThreadId());

#ifdef _DEBUG_TRACE
    MessageBox(NULL, "Kernel Panic! Process will now terminate.\n\n"
                     "Check debug traces for hints on the cause of this crash.", "CxbxKrnl", MB_OK | MB_ICONEXCLAMATION);
#else
    MessageBox(NULL, "Kernel Panic! Process will now terminate.", "CxbxKrnl", MB_OK | MB_ICONEXCLAMATION);
#endif

    EmuCleanup("Kernel Panic!");

    EmuSwapFS();   // XBox FS
}

// ******************************************************************
// * func: EmuInstallWrapper
// ******************************************************************
inline void EmuInstallWrapper(void *FunctionAddr, void *WrapperAddr)
{
    uint08 *FuncBytes = (uint08*)FunctionAddr;

    *(uint08*)&FuncBytes[0] = 0xE9;
    *(uint32*)&FuncBytes[1] = (uint32)WrapperAddr - (uint32)FunctionAddr - 5;
}

// ******************************************************************
// * func: EmuInstallWrappers
// ******************************************************************
void EmuInstallWrappers(OOVPATable *OovpaTable, uint32 OovpaTableSize, void (*Entry)(), Xbe::Header *XbeHeader)
{
    // ******************************************************************
    // * traverse the full OOVPA table
    // ******************************************************************
    for(uint32 a=0;a<OovpaTableSize/sizeof(OOVPATable);a++)
    {
        #ifdef _DEBUG_TRACE
        printf("Emu: Searching for %s...", OovpaTable[a].szFuncName);
        #endif

        OOVPA *Oovpa = OovpaTable[a].Oovpa;

        uint32 count = Oovpa->Count;
        uint32 lower = XbeHeader->dwBaseAddr;
        uint32 upper = XbeHeader->dwBaseAddr + XbeHeader->dwSizeofImage;

        // ******************************************************************
        // * Large
        // ******************************************************************
        if(Oovpa->Large == 1)
        {
            LOOVPA<1> *Loovpa = (LOOVPA<1>*)Oovpa;

            upper -= Loovpa->Lovp[count-1].Offset;

            bool found = false;

            // ******************************************************************
            // * Search all of the image memory
            // ******************************************************************
            for(uint32 cur=lower;cur<upper;cur++)
            {
                uint32  v=0;

                // ******************************************************************
                // * check all pairs, moving on if any do not match
                // ******************************************************************
                for(v=0;v<count;v++)
                {
                    uint32 Offset = Loovpa->Lovp[v].Offset;
                    uint32 Value  = Loovpa->Lovp[v].Value;

                    uint08 RealValue = *(uint08*)(cur + Offset);

                    if(RealValue != Value)
                        break;
                }

                // ******************************************************************
                // * success if we found all pairs
                // ******************************************************************
                if(v == count)
                {
                    #ifdef _DEBUG_TRACE
                    printf("Found! (0x%.08X)\n", cur);
                    #endif

                    EmuInstallWrapper((void*)cur, OovpaTable[a].lpRedirect);

                    found = true;

                    break;
                }
            }

            // ******************************************************************
            // * not found
            // ******************************************************************
            if(!found)
            {
                #ifdef _DEBUG_TRACE
                printf("None (OK)\n");
                #endif
            }
        }
        // ******************************************************************
        // * Small
        // ******************************************************************
        else
        {
            SOOVPA<1> *Soovpa = (SOOVPA<1>*)Oovpa;

            upper -= Soovpa->Sovp[count-1].Offset;

            bool found = false;

            // ******************************************************************
            // * Search all of the image memory
            // ******************************************************************
            for(uint32 cur=lower;cur<upper;cur++)
            {
                uint32  v=0;

                // ******************************************************************
                // * check all pairs, moving on if any do not match
                // ******************************************************************
                for(v=0;v<count;v++)
                {
                    uint32 Offset = Soovpa->Sovp[v].Offset;
                    uint32 Value  = Soovpa->Sovp[v].Value;

                    uint08 RealValue = *(uint08*)(cur + Offset);

                    if(RealValue != Value)
                        break;
                }

                // ******************************************************************
                // * success if we found all pairs
                // ******************************************************************
                if(v == count)
                {
                    #ifdef _DEBUG_TRACE
                    printf("Found! (0x%.08X)\n", cur);
                    #endif

                    EmuInstallWrapper((void*)cur, OovpaTable[a].lpRedirect);

                    found = true;

                    break;
                }
            }

            // ******************************************************************
            // * not found
            // ******************************************************************
            if(!found)
            {
                #ifdef _DEBUG_TRACE
                printf("None (OK)\n");
                #endif
            }
        }
    }
}

// ******************************************************************
// * func: EmuException
// ******************************************************************
int EmuException(LPEXCEPTION_POINTERS e)
{
	// ******************************************************************
	// * Debugging Information
	// ******************************************************************
	{
		printf("\n");
		printf("Recieved Exception : 0x%.08X\n", e->ExceptionRecord->ExceptionCode);
		printf("\n");
	}

	// ******************************************************************
	// * Notify User
	// ******************************************************************
	{
		char buffer[256];

		sprintf(buffer, "Recieved Exception [0x%.08X]\n\nPress 'OK' to terminate emulation.\nPress 'Cancel' to debug.", e->ExceptionRecord->ExceptionCode);

		if(MessageBox(NULL, buffer, "Cxbx", MB_ICONSTOP | MB_OKCANCEL) == IDOK)
			ExitProcess(1);
	}

    return EXCEPTION_CONTINUE_SEARCH;
}


// ******************************************************************
// * func: ExitException
// ******************************************************************
int ExitException(LPEXCEPTION_POINTERS e)
{
    static int count = 0;

    // ******************************************************************
	// * Debugging Information
	// ******************************************************************
	{
		printf("\n");
		printf("Recieved Exit Exception : 0x%.08X\n", e->ExceptionRecord->ExceptionCode);
		printf("\n");
	}

    count++;

    if(count > 1)
    {
        MessageBox(NULL, "Warning: Could not safely terminate process!", "Cxbx", MB_OK);
        return EXCEPTION_CONTINUE_SEARCH;
    }

    ExitProcess(1);

    return EXCEPTION_CONTINUE_SEARCH;
}
