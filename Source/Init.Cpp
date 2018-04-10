#ifndef _INIT_CPP
#define _INIT_CPP
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <WinSock2.H>
#include <Windows.H>
#include <WindowsX.H>
#include <ShellAPI.H>
#include <Stdio.H>
#include <Stdlib.H>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../Resources/Resource.H"

#include "Init.H"
#include "Entry.H"
#include "Routines.H"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InitializeApp(void)
{
	LoadString(ghAppInstance, IDS_APPCOPYRIGHT, gsAppCopyRight, sizeof(gsAppCopyRight));
    LoadString(ghAppInstance, IDS_FILEVERSION, gsFileVersion, sizeof(gsFileVersion));
    LoadString(ghAppInstance, IDS_TITLECAPTION, gsTitleCaption, sizeof(gsTitleCaption));
    LoadString(ghAppInstance, IDS_REGISTRYKEY, gsRegistryKey, sizeof(gsRegistryKey));

    WORD wsaVerReq = 0x0101;
    WSADATA wsaData;

    if(WSAStartup(wsaVerReq, &wsaData) == SOCKET_ERROR)
    {
        MessageBox(GetActiveWindow(), "WSAStartup() Failed.", gsTitleCaption, MB_ICONSTOP | MB_TASKMODAL);
        return false;
    }
	
	if(!GetValues())
	{
		MessageBox(GetActiveWindow(), "Failed to obtain registry values.", gsTitleCaption, MB_ICONSTOP | MB_TASKMODAL);
		return false;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool UninitializeApp(void)
{
	bool bResult = true;

	if(WSACleanup() == SOCKET_ERROR)
    {
        MessageBox(GetActiveWindow(), "WSACleanup() Failed.", gsTitleCaption, MB_ICONSTOP | MB_TASKMODAL);
		bResult = false;
    }

	if(!SetValues())
	{
		MessageBox(GetActiveWindow(), "Failed to save registry values.", gsTitleCaption, MB_ICONSTOP | MB_TASKMODAL);
		bResult = false;
	}

	return bResult;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

