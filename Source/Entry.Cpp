#ifndef _ENTRY_CPP
#define _ENTRY_CPP
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Windows.H>
#include <Stdio.H>
#include <Stdlib.H>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../Resources/Resource.H"

#include "Entry.H"
#include "Init.H"

#include "../Dialogs/MainDlg.H"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HINSTANCE ghAppInstance = NULL;

char gsAppCopyRight[64];
char gsFileVersion[32];
char gsTitleCaption[64];
char gsRegistryKey[255];

char gsLastUserInput[1024];
bool gbIsAddressList = false;
bool gbIsAliases = false;
bool gbIsReverse = false;
bool gbIsAlwaysOnTop = false;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
int main(int argc, char *argv[])
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevious, LPSTR CmdLine, int CmdShow)
#endif
{
    #ifdef _DEBUG
	ghAppInstance = GetModuleHandle(NULL);
    #else
	ghAppInstance = hInstance;
    #endif

    int iResult = 0;

	if(!InitializeApp())
    {
		MessageBox(GetActiveWindow(), "Failed to initialize the application.", gsTitleCaption, MB_ICONSTOP | MB_TASKMODAL);
        return 1;
    }

	DialogBox(ghAppInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, MainDialog);

    if(!UninitializeApp())
    {
        return 1;
    }

	return iResult;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

