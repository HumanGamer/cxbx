// ******************************************************************
// *
// *    .,-:::::    .,::      .::::::::.    .,::      .:
// *  ,;;;'````'    `;;;,  .,;;  ;;;'';;'   `;;;,  .,;; 
// *  [[[             '[[,,[['   [[[__[[\.    '[[,,[['  
// *  $$$              Y$$$P     $$""""Y$$     Y$$$P    
// *  `88bo,__,o,    oP"``"Yo,  _88o,,od8P   oP"``"Yo,  
// *    "YUMMMMMP",m"       "Mm,""YUMMMP" ,m"       "Mm,
// *
// *   Cxbx->Win32->Cxbx->WinMain.cpp
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
#include "EmuExe.h"
#include "WndMain.h"

#undef FIELD_OFFSET     // prevent macro redefinition warnings
#include <windows.h>

// ******************************************************************
// * func : WinMain
// ******************************************************************
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WndMain *caustik = new WndMain(hInstance);

    if(__argc > 1)
    {
        while(!caustik->isCreated() && caustik->ProcessMessages())
            Sleep(10);

        if(caustik->GetError() == 0)
        {
            caustik->OpenXbe(__argv[1]);

            caustik->StartEmulation(true);
        }
    }

    while(caustik->GetError() == 0 && caustik->ProcessMessages())
        Sleep(10);

    if(caustik->GetError() != 0)
        MessageBox(NULL, caustik->GetError(), "Cxbx", MB_OK);

    delete caustik;

    return 0;
}