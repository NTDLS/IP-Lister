#ifndef _MAINDLG_CPP
#define _MAINDLG_CPP
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Windows.H>
#include <Stdio.H>
#include <Stdlib.H>

#include "../Resources/Resource.H"

#include "../Source/Entry.H"
#include "../Source/Routines.H"

#include "../Dialogs/MainDlg.H"
#include "../Dialogs/NetLogoDlg.H"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//---------------------(Variable Declarations)
HWND hMainDialog = NULL;

LISTERLOOKUP gLLU;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace NSWFL::Windows;
using namespace NSWFL::String;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CALLBACK MainDialog(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    //--------------------------------------------------------------------------

    static HWND hIPHost = NULL;
    static HWND hDetail = NULL;
    static HWND hGOCmd = NULL;

    //--------------------------------------------------------------------------

    if(uMsg == WM_INITDIALOG) // Received A Initilize Dialog Message
    {
		hMainDialog = hWnd;

		memset(&gLLU, 0, sizeof(gLLU));
		gLLU.iSize = sizeof(gLLU);

        HMENU SystemMenu_hMenu = GetSystemMenu(hWnd, FALSE);
        AppendMenu(SystemMenu_hMenu, MF_SEPARATOR, 0, 0);
        AppendMenu(SystemMenu_hMenu, MF_STRING, MAINDIALOG_MENU_ABOUT, "About");

        SendMessage(hWnd, (UINT)WM_SETTEXT, (WPARAM)0, (LPARAM)gsTitleCaption);
        SendMessage(hWnd, WM_SETICON, TRUE, (LPARAM) LoadIcon(ghAppInstance, MAKEINTRESOURCE(IDI_MAIN)));

        hIPHost = GetDlgItem(hWnd, IDC_IPHOST);
        hDetail = GetDlgItem(hWnd, IDC_DETAIL);
		hGOCmd  = GetDlgItem(hWnd, IDC_GO);

		Set_Text(hIPHost, gsLastUserInput);
        Set_Text(hDetail, "");

		if(gbIsAlwaysOnTop)
		{
			CheckDlgButton(hWnd, IDC_CHK_AOT, BST_CHECKED);
			SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

        if(gbIsReverse)
		{
			CheckDlgButton(hWnd, IDC_CHK_REVERSE, BST_CHECKED);
		}

		if(gbIsAliases)
		{
			CheckDlgButton(hWnd, IDC_CHK_ALIASES, BST_CHECKED);
		}

		if(gbIsAddressList)
		{
			CheckDlgButton(hWnd, IDC_CHK_ADDRESS, BST_CHECKED);
		}

		SetFocus(hIPHost);
		SendMessage(hIPHost, EM_SETSEL, 0, -1);
		EnableWindow(GetDlgItem(hWnd, IDC_CHK_REVERSE), gbIsAddressList);

		CenterWindow(hWnd);

        return TRUE; // Return TRUE to set the keyboard focus, Otherwise return FALSE.
    }

    //--------------------------------------------------------------------------

    if(uMsg == WM_COMMAND)
    {
		if(wParam == IDC_CHK_ADDRESS)
		{
			gbIsAddressList = (IsDlgButtonChecked(hWnd, IDC_CHK_ADDRESS) == BST_CHECKED);
			if(!gbIsAddressList)
			{
				CheckDlgButton(hWnd, IDC_CHK_REVERSE, BST_UNCHECKED);
			}
			EnableWindow(GetDlgItem(hWnd, IDC_CHK_REVERSE), gbIsAddressList);
			return TRUE;
		}

		if(wParam == IDC_CHK_ALIASES)
		{
			gbIsAliases = (IsDlgButtonChecked(hWnd, IDC_CHK_ALIASES) == BST_CHECKED);
			return TRUE;
		}

		if(wParam == IDC_CHK_REVERSE)
		{
			gbIsReverse = (IsDlgButtonChecked(hWnd, IDC_CHK_REVERSE) == BST_CHECKED);
			return TRUE;
		}

		if(wParam == IDC_CHK_AOT)
		{
			gbIsAlwaysOnTop = (IsDlgButtonChecked(hWnd, IDC_CHK_AOT) == BST_CHECKED);

			if(gbIsAlwaysOnTop)
			{
				SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			}
			else{
				SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			}
		}

		if(wParam == IDC_ABOUT)
        {
            _AboutDialogInfo ADI;
    
            ADI.DisplayIcon  = LoadIcon(ghAppInstance, MAKEINTRESOURCE(IDI_MAIN));
            ADI.TitleCaption = gsTitleCaption;
            ADI.FileVersion  = gsFileVersion;
            ADI.BuildDate    = __DATE__;
            ADI.BuildTime    = __TIME__;
            ADI.CopyRight    = gsAppCopyRight;
            ADI.OwnerHandle  = hWnd;

            NetLogo(&ADI);
            return TRUE;
        }

		if(wParam == IDC_GO)
        {
			SetFocus(hIPHost);
			SendMessage(hIPHost, EM_SETSEL, 0, -1);

			char sButonText[100];
			bool bCancel = false;

			Get_Text(gLLU.hGOCmd, sButonText, sizeof(sButonText));

			if(_strcmpi(sButonText, "Cancel") == 0)
			{
				if(MessageBox(hWnd, "Cancel pending process?", gsTitleCaption, MB_ICONQUESTION | MB_YESNO) == IDYES)
				{
					bCancel = true;
				}
				else{
					return TRUE;
				}
			}

			WaitOnThreadToExit(&gLLU);

			if(bCancel)
			{
				TextBoxWrite(hDetail, "\r\nCancelled.");
				return TRUE;
			}

			memset(&gLLU, 0, sizeof(gLLU));
			gLLU.iSize = sizeof(gLLU);

			gLLU.hGOCmd = hGOCmd;
			gLLU.hDetail = hDetail;

			Set_Text(gLLU.hGOCmd, "Cancel");

			if(Get_Text(hIPHost, gLLU.sAddr, sizeof(gLLU.sAddr)) <= sizeof(gLLU.sAddr))
			{
				int iSize = strlen(gLLU.sAddr);

				iSize = CleanWhiteSpaces(gLLU.sAddr, iSize);

				if(iSize > 0)
				{
					strcpy_s(gsLastUserInput, sizeof(gsLastUserInput), gLLU.sAddr);

					Set_Text(hIPHost, gsLastUserInput);
					SendMessage(hIPHost, EM_SETSEL, 0, -1);

					gLLU.bIsAddrIP = IsIPAddress(gLLU.sAddr);
					gLLU.bResolveAddress = gbIsAddressList;
					gLLU.bResolveAliases = gbIsAliases;
					gLLU.bIsReverseLookup = gbIsReverse;
					
					if(StartThread(&gLLU))
					{
						return TRUE;
					}
				}
			}

			Set_Text(gLLU.hGOCmd, "Go");

            return TRUE;
        }

        if(wParam == IDC_EXIT)
        {
            EndDialog(hWnd, 0);
            DestroyWindow(hWnd);

			hMainDialog = NULL;

            return TRUE;
        }

        return FALSE;
    }

    //--------------------------------------------------------------------------

	if(uMsg == WM_PAINT)
    {
        HDC ThisHDC;
        PAINTSTRUCT ThisPS;

        ThisHDC = BeginPaint(hWnd, &ThisPS);

        //- Any painting should be done here.

        EndPaint(hWnd, &ThisPS);
        return TRUE;
    }

    //--------------------------------------------------------------------------

    if(uMsg == WM_SYSCOMMAND) //- Received a system menu message.
    {
        if(LOWORD(wParam) == MAINDIALOG_MENU_ABOUT) //- About.
        {
            _AboutDialogInfo ADI;
    
            ADI.DisplayIcon  = LoadIcon(ghAppInstance, MAKEINTRESOURCE(IDI_MAIN));
            ADI.TitleCaption = gsTitleCaption;
            ADI.FileVersion  = gsFileVersion;
            ADI.BuildDate    = __DATE__;
            ADI.BuildTime    = __TIME__;
            ADI.CopyRight    = gsAppCopyRight;
            ADI.OwnerHandle  = hWnd;

            NetLogo(&ADI);
            return TRUE;
        }

        return FALSE;
    }

    //--------------------------------------------------------------------------

    if(uMsg == WM_CLOSE) //- Received close message.
    {
        EndDialog(hWnd,0);
        DestroyWindow(hWnd);

		hMainDialog = NULL;

        return TRUE;
    }

    //--------------------------------------------------------------------------

    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

