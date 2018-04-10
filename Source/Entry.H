#ifndef _ENTRY_H
#define _ENTRY_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../../@Libraries/Debug/Debug.H"
//#include "../../@Libraries/CMemPool/CMemPool.H"
//#include "../../@Libraries/CCmdLine/CCmdLine.H"
#include "../../@Libraries/NSWFL/NSWFL.H"

#include "../Resources/Resource.H"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern HINSTANCE ghAppInstance;

extern char gsAppCopyRight[64];
extern char gsFileVersion[32];
extern char gsTitleCaption[64];
extern char gsRegistryKey[255];

extern char gsLastUserInput[1024];
extern bool gbIsAddressList;
extern bool gbIsAliases;
extern bool gbIsReverse;
extern bool gbIsAlwaysOnTop;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

