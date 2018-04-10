#ifndef _ROUTINES_CPP
#define _ROUTINES_CPP
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

using namespace NSWFL::Windows;
using namespace NSWFL::Registry;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char **GetAddressList(struct hostent *hEntInfo, int *iOutIPs)
{
	char **sIPs = NULL;
	int iIPs = 0;

    struct in_addr addr;

    while( hEntInfo->h_addr_list[iIPs] )
    {
        memcpy(&addr.s_addr, hEntInfo->h_addr_list[iIPs], hEntInfo->h_length);
		char *sIP = inet_ntoa(addr);
		int iAlloc = strlen(sIP) + 1;

		sIPs = (char **) realloc(sIPs, sizeof(char *) * (iIPs + 1));
		sIPs[iIPs] = (char *) calloc(iAlloc, sizeof(char));
		strcpy_s(sIPs[iIPs], iAlloc, sIP);
        iIPs++;
    }

	*iOutIPs = iIPs;

	return sIPs;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FreeList(char **sList, int iListItems)
{
	if(sList)
	{
		for(int iItem = 0; iItem < iListItems; iItem++)
		{
			free(sList[iItem]);
		}
		free(sList);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char **GetAliasList(struct hostent *hEntInfo, int *iOutAliases)
{
	char **sAliases = NULL;
	int iAliases = 0;

    while( hEntInfo->h_aliases[iAliases] )
    {
		char *sAlias = hEntInfo->h_aliases[iAliases];
		int iAlloc = strlen(sAlias) + 1;

		sAliases = (char **) realloc(sAliases, sizeof(char *) * (iAliases + 1));
		sAliases[iAliases] = (char *) calloc(iAlloc, sizeof(char));
		strcpy_s(sAliases[iAliases], iAlloc, sAlias);
        iAliases++;
    }

	*iOutAliases = iAliases;

    return sAliases;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool GetHostName(char *sIP, char *sHostName, int iMaxSz)
{
	unsigned long lHostAddr = inet_addr(sIP);
    struct hostent *hEntInfo;

    if((hEntInfo = gethostbyaddr((char*) &lHostAddr, sizeof(unsigned long), AF_INET)) == NULL)
    {
		return false;
    }

	if(*hEntInfo->h_name)
	{
		strcpy_s(sHostName, iMaxSz, hEntInfo->h_name);
		return true;
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DWORD IPListProc(LISTERLOOKUP *lpLLU)
{
    char sTemp[1024];

    struct hostent *hEntInfo;
	memset(&hEntInfo, 0, sizeof(hEntInfo));

	if(lpLLU->bIsAddrIP)
    {
		unsigned long lHostAddr = inet_addr(lpLLU->sAddr);

		if((hEntInfo = gethostbyaddr((char*) &lHostAddr, sizeof(unsigned long), AF_INET)) == NULL)
		{
	        sprintf_s(sTemp, sizeof(sTemp), "Could not resolve address: %s\r\n\r\n", lpLLU->sAddr);
	        TextBoxWrite(lpLLU->hDetail, sTemp);

			strcpy_s(lpLLU->sHostName, sizeof(lpLLU->sHostName), lpLLU->sAddr);
			if((hEntInfo = gethostbyname(lpLLU->sHostName)) == NULL)
			{
				sprintf_s(sTemp, sizeof(sTemp), "Could not resolve host: %s\r\n", lpLLU->sHostName);
				TextBoxWrite(lpLLU->hDetail, sTemp);
				return false;
			}
		}
		else{
			if(*hEntInfo->h_name)
			{
				strcpy_s(lpLLU->sHostName, sizeof(lpLLU->sHostName), hEntInfo->h_name);
			}
			else{
				strcpy_s(lpLLU->sHostName, sizeof(lpLLU->sHostName), lpLLU->sAddr);
			}
		}
    }
	else{
		strcpy_s(lpLLU->sHostName, sizeof(lpLLU->sHostName), lpLLU->sAddr);

		if((hEntInfo = gethostbyname(lpLLU->sHostName)) == NULL)
		{
			sprintf_s(sTemp, sizeof(sTemp), "Could not resolve host: %s\r\n", lpLLU->sHostName);
			TextBoxWrite(lpLLU->hDetail, sTemp);
			return false;
		}
	}

	sprintf_s(sTemp, sizeof(sTemp), "%s host information\r\n\r\n", lpLLU->sHostName);
    TextBoxWrite(lpLLU->hDetail, sTemp);

	char **sIPs = NULL;
	int iIPs = 0;

	char **sAliases = NULL;
	int iAliases = 0;

    if(lpLLU->bResolveAddress)
    {
		sIPs = GetAddressList(hEntInfo, &iIPs);
    }

    if(lpLLU->bResolveAliases)
    {
		sAliases = GetAliasList(hEntInfo, &iAliases);
    }

    if(lpLLU->bResolveAddress)
    {
		TextBoxWrite(lpLLU->hDetail, "- Addresses\r\n");

		for(int iItem = 0; iItem < iIPs; iItem++)
		{
			TextBoxWrite(lpLLU->hDetail, "\t");
			TextBoxWrite(lpLLU->hDetail, sIPs[iItem]);

			if(iIPs <= 0)
			{
				TextBoxWrite(lpLLU->hDetail, "\t- none -\r\n");
			}
			else{
				if(lpLLU->bIsReverseLookup)
				{
					char sHost[1024];
					if(GetHostName(sIPs[iItem], sHost, sizeof(sHost)))
					{
						TextBoxWrite(lpLLU->hDetail, " (");
						TextBoxWrite(lpLLU->hDetail, sHost);
						TextBoxWrite(lpLLU->hDetail, ")");
					}
				}
			}

			TextBoxWrite(lpLLU->hDetail, "\r\n");
		}

		FreeList(sIPs, iIPs);
	}

    if(lpLLU->bResolveAliases)
    {
		TextBoxWrite(lpLLU->hDetail, "- Aliases\r\n");
		if(iAliases <= 0)
		{
			TextBoxWrite(lpLLU->hDetail, "\t- none -\r\n");
		}
		else{
			for(int iItem = 0; iItem < iAliases; iItem++)
			{
				TextBoxWrite(lpLLU->hDetail, "\t");
				TextBoxWrite(lpLLU->hDetail, sAliases[iItem]);

				TextBoxWrite(lpLLU->hDetail, "\r\n");
			}
		}

		FreeList(sAliases, iAliases);
	}

	SendMessage(lpLLU->hDetail, EM_SETSEL , 0, 0);
	SendMessage(lpLLU->hDetail, EM_SCROLLCARET, 0, 0);
	
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DWORD WINAPI IPListThreadProc(LPVOID lpData)
{
    LISTERLOOKUP *lpLLU = (LISTERLOOKUP *) lpData;

	SetEvent(lpLLU->hEvent);

	Set_Text(lpLLU->hDetail, "");
	
	IPListProc(lpLLU);

	Set_Text(lpLLU->hGOCmd, "Go");

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsIPAddress(const char *sString)
{
	int iStrSz = strlen(sString);
	int iDotCount = 0;

    if(iStrSz < 7 || iStrSz > 15 || inet_addr(sString) == INADDR_NONE)
	{
		return false;
	}
	else{
		for(int iRPos = 0; iRPos < iStrSz; iRPos++)
		{
			if(sString[iRPos] == '.')
			{
				iDotCount++;
			}
		}
	}

	return iDotCount == 3;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool StartThread(LISTERLOOKUP *lpLLU)
{
	lpLLU->hEvent = CreateEvent(NULL, TRUE, FALSE, "IP_Lister_Thread_Function");

    if((lpLLU->hThreadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)IPListThreadProc, (LPVOID) lpLLU, 0, (LPDWORD) &lpLLU->dwThreadID)) == NULL)
    {
		//Error!
        CloseHandle(lpLLU->hEvent);
        return false;
    }

    if(WaitForSingleObject(lpLLU->hEvent, 5000) == WAIT_TIMEOUT)
    {
		//Error!
        CloseHandle(lpLLU->hEvent);
        return false;
    }

	CloseHandle(lpLLU->hEvent);

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool WaitOnThreadToExit(LISTERLOOKUP *lpLLU)
{
    DWORD dwExitCode = 0;

    int iWaitCount = 0;

	if(lpLLU->hThreadHandle == NULL)
	{
		return true;
	}

    while(GetExitCodeThread(lpLLU->hThreadHandle, &dwExitCode))
    {
        if(dwExitCode != STILL_ACTIVE || iWaitCount == 10)
        {
            if(iWaitCount == 10)
            {
                //Possible thread dead-lock. Thread will be terminated.
                TerminateThread(lpLLU->hThreadHandle, 1);
            }

            //The thread was stopped.
			CloseHandle(lpLLU->hThreadHandle);
            lpLLU->dwThreadID = 0;

			Set_Text(lpLLU->hGOCmd, "Go");

			return true;
        }

        iWaitCount++;
        Sleep(1);
    }

	//The thread was stopped.
	Set_Text(lpLLU->hGOCmd, "Go");

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool GetValues(void)
{
	DWORD dwSize = sizeof(gsLastUserInput);
	memset(gsLastUserInput, 0, dwSize);

	if(Get_StringRegistryValue(HKEY_LOCAL_MACHINE, gsRegistryKey, "LastUserInput", gsLastUserInput, dwSize))
	{
		gbIsAddressList = Get_BOOLRegistryValue(HKEY_LOCAL_MACHINE, gsRegistryKey, "IsAddressList");
		gbIsAliases = Get_BOOLRegistryValue(HKEY_LOCAL_MACHINE, gsRegistryKey, "IsAliases");
		gbIsReverse = Get_BOOLRegistryValue(HKEY_LOCAL_MACHINE, gsRegistryKey, "IsReverse");
		gbIsAlwaysOnTop = Get_BOOLRegistryValue(HKEY_LOCAL_MACHINE, gsRegistryKey, "IsAlwaysOnTop");
	}
	else{
		gbIsAddressList = true;
		gbIsReverse = false;
		gbIsAliases = false;
		gbIsAlwaysOnTop = false;

		CreateRegistryKey(HKEY_LOCAL_MACHINE, gsRegistryKey);
		SetValues();
	}

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool SetValues(void)
{
    Set_StringRegistryValue(HKEY_LOCAL_MACHINE, gsRegistryKey, "LastUserInput", gsLastUserInput);

	Set_BOOLRegistryValue(HKEY_LOCAL_MACHINE, gsRegistryKey, "IsAddressList", gbIsAddressList);
	Set_BOOLRegistryValue(HKEY_LOCAL_MACHINE, gsRegistryKey, "IsAliases", gbIsAliases);
	Set_BOOLRegistryValue(HKEY_LOCAL_MACHINE, gsRegistryKey, "IsAlwaysOnTop", gbIsAlwaysOnTop);
	Set_BOOLRegistryValue(HKEY_LOCAL_MACHINE, gsRegistryKey, "IsReverse", gbIsReverse);

    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
