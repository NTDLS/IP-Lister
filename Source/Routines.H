#ifndef _ROUTINES_H
#define _ROUTINES_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct _TAG_LISTERLOOKUP{

	int iSize;

	char sIPAddress[16];
	char sHostName[1024];
	
	char sAddr[1024];
	bool bIsAddrIP;
	bool bResolveAliases;
	bool bResolveAddress;
	bool bIsReverseLookup;

	HANDLE hThreadHandle;
	HANDLE hEvent;
	HWND hGOCmd;
	HWND hDetail;
	DWORD dwThreadID;

} LISTERLOOKUP, *LPLISTERLOOKUP;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsIPAddress(const char *sString);
bool StartThread(LISTERLOOKUP *lpLLU);
bool WaitOnThreadToExit(LISTERLOOKUP *lpLLU);
bool GetValues(void);
bool SetValues(void);
DWORD IPListProc(LISTERLOOKUP *lpLLU);
bool GetHostName(char *sIP, char *sHostName, int iMaxSz);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

