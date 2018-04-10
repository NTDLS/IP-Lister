#ifndef _NSWFL_H
#define _NSWFL_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NSWFL_DllImport extern "C" __declspec( dllimport )

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//_NETLOGO_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _AboutDialogInfo{
    char *BuildDate;
    char *BuildTime;
    char *CopyRight;
    char *FileVersion;
    char *TitleCaption;
    HICON DisplayIcon;
    HWND OwnerHandle;
} ABOUTDLGINFO, *LPABOUTDLGINFO;

NSWFL_DllImport bool IsNetLogoActive(void);
NSWFL_DllImport bool NetLogo(LPABOUTDLGINFO lpADI);
NSWFL_DllImport HWND NetLogoHandle(void);
NSWFL_DllImport void EndNetLogo(void);

//_DATETIME_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _TIME_T_DEFINED
NSWFL_DllImport bool TimetToLocalTime(time_t MyTime_T, LPSYSTEMTIME pLT);
NSWFL_DllImport bool TimetToSystemTime(time_t MyTime_T, LPSYSTEMTIME pST);
NSWFL_DllImport void TimetToFileTime(time_t t, LPFILETIME pft);
#endif

NSWFL_DllImport DWORD DateToLong(int iYear, int iMonth, int iDay);
NSWFL_DllImport DWORD TimeToLong(int iHour, int iMin, int iSec);
NSWFL_DllImport void LongToDate(DWORD dwDate, int *piYear, int *piMonth, int *piDay);
NSWFL_DllImport void LongToTime(DWORD dwTime, int *piHour, int *piMin, int *piSec);

//_KEYGENERATIION_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define GKNUMBERS        0x1
#define GKUPPER_AZ       0x2
#define GKLOWER_AZ       0x4
#define GKBROADKEY       0x8
#define GKNONREPETITION  0x16

NSWFL_DllImport bool GenerateKey(int iNewKeyLen, long lSeed, int iAttribs, char *sOutKey);
NSWFL_DllImport long GenerateSeed(void);

//_LISTBOX_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NSWFL_DllImport char *ListBoxItemText(HWND hWnd, int iItemPos);
NSWFL_DllImport int ClearListBox(HWND hWnd);
NSWFL_DllImport int CountListBoxItems(HWND hWnd);
NSWFL_DllImport int CurrentListBoxItem(HWND hWnd);
NSWFL_DllImport int DeleteListBoxItem(HWND hWnd, int iItemPos);
NSWFL_DllImport int HorizontalListBoxExtent(HWND hWnd, int iHorzExtent);
NSWFL_DllImport int InsertListBoxItem(HWND hWnd, const char *sInStr, int iInsertPos);
NSWFL_DllImport int InsertListBoxItemEx(HWND hWnd, const char *sInStr, int iMaxItems, int iInsertPos);
NSWFL_DllImport int ListBoxItemLength(HWND hWnd, int iItemPos);
NSWFL_DllImport int SelectListBoxItem(HWND hWnd, int iItemPos);
NSWFL_DllImport int SelectMultipleListBoxItem(HWND hWnd, int iItemPos, BOOL Select);
NSWFL_DllImport void ListBoxItemTextEx(HWND hWnd, int iItemPos, char *sOutVal);

//_MATH_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NSWFL_DllImport DWORD VersionToLong(int iBit1, int iBit2, int iBit3, int iBit4);
NSWFL_DllImport int HiByte (unsigned int iInput);
NSWFL_DllImport int IntLength(int iIn);
NSWFL_DllImport int LoByte (unsigned int iInput);
NSWFL_DllImport int LongLength(long lIn);
NSWFL_DllImport int ReverseInt(int iIn);
NSWFL_DllImport int ReverseLong(long lIn);
NSWFL_DllImport int SquareRoot (int iInput);
NSWFL_DllImport void LongToVersion(DWORD dwInVer, int *iBit1, int *iBit2, int *iBit3, int *iBit4);

//_MEMORY_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NSWFL_DllImport bool Free(void *vBuffer);
NSWFL_DllImport int MemCopyInt(char *sOutBuf, int iIn);
NSWFL_DllImport int MemCopyLong(char *sOutBuf, long lIn);
NSWFL_DllImport void *Allocate(int iBlockSz);
NSWFL_DllImport void *ClearMem(void *vBuffer, int iBufSz);
NSWFL_DllImport void *MemCopy(void *vTarget, void *vSource, int iLen);

//_Conversion_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NSWFL_DllImport char * DoubleChar (double dInput);
NSWFL_DllImport char * FloatChar (float fInput);
NSWFL_DllImport char * IntChar (int iInput);
NSWFL_DllImport char * LongChar (DWORD dwInput);
NSWFL_DllImport double CharDouble (const char *sInput);
NSWFL_DllImport DWORD CharLong (const char *sInput);
NSWFL_DllImport float CharFloat (const char *sInput);
NSWFL_DllImport int CharInt (const char *sInput);
NSWFL_DllImport void DoubleCharEx (double dInput, char *sOutVal);
NSWFL_DllImport void FloatCharEx (float fInput, char *sOutVal);
NSWFL_DllImport void IntCharEx (int iInput, char *sOutVal);
NSWFL_DllImport void LongCharEx (DWORD dwInput, char *sOutVal);

//_QUEUSYSTEM_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _QueuSystem{
    char **Data;
    int *DataSize;
    int MaxItems;
    int UsedItems;
} QUEUSYSTEM, *LPQUEUSYSTEM;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NSWFL_DllImport bool AddQueuItem(LPQUEUSYSTEM lpQS, void *vInBuf, int iInBufSz);
NSWFL_DllImport bool DeleteQueuItem(LPQUEUSYSTEM lpQS, int iItem);
NSWFL_DllImport bool FreeQueu(LPQUEUSYSTEM lpQS);
NSWFL_DllImport bool InitilizeQueu(LPQUEUSYSTEM lpQS, int iMaxItems);
NSWFL_DllImport int GetQueuItem(LPQUEUSYSTEM lpQS, int iItem, void *vOutBuf);
NSWFL_DllImport int ReadQueuItem(LPQUEUSYSTEM lpQS, int iItem, void *vOutBuf);

//_REGISTRY_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NSWFL_DllImport bool CreateRegistryKey(HKEY hKeyRoot, LPCTSTR pszSubKey);
NSWFL_DllImport bool DeleteRegistryKey(HKEY hKeyRoot, LPCTSTR pszSubKey);
NSWFL_DllImport bool DeleteRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue);
NSWFL_DllImport bool Get_BinaryRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, PVOID pBuffer, DWORD& rdwSize);
NSWFL_DllImport bool Get_BOOLRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue);
NSWFL_DllImport bool Get_DWORDRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, DWORD &rdwBuff);
NSWFL_DllImport bool Get_StringRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, LPTSTR pszBuffer, DWORD& rdwSize);
NSWFL_DllImport bool Set_BinaryRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, PVOID pData, DWORD dwSize);
NSWFL_DllImport bool Set_BOOLRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, bool bVal);
NSWFL_DllImport bool Set_DWORDRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, DWORD dwValue);
NSWFL_DllImport bool Set_StringRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, LPCTSTR pszString);

//WINSFL_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define OFD 1 //Open File Dialog (For OSFileDialog())
#define SFD 2 //Save File Dialog (For OSFileDialog())

NSWFL_DllImport bool BrowseDirectory(HWND hOwner, char *sInTitle, unsigned long ulFlags, char *sOutBuf);
NSWFL_DllImport char *Get_Text (HWND hWnd);
NSWFL_DllImport DWORD Get_Long(HWND hWnd);
NSWFL_DllImport HFONT MakeFont(char *sFontName, int iPointSize);
NSWFL_DllImport int Get_Int(HWND hWnd);
NSWFL_DllImport int Get_TextEx (HWND hWnd, char *sOutBuf, int iMaxSize);
NSWFL_DllImport int Get_TextLength(HWND hWnd);
NSWFL_DllImport int IsMouseOverHwnd(HWND hWnd);
NSWFL_DllImport int OSFileDialog (HWND hOwner, char *sInOutFileName, char *sInDfltExt, char *sInTitle, char *sInFilters, char *sInDfltDir, int iDlgType, DWORD dwFlags);
NSWFL_DllImport LRESULT CALLBACK Set_Color(int iFGColor, int iBKColor, int wParam);
NSWFL_DllImport void AlertMessage(HWND hWnd, char *sInBuf, char *sTitle);
NSWFL_DllImport void CenterWindow (HWND hWnd);
NSWFL_DllImport void ErrorMessage(HWND hWnd, char *sInBuf);
NSWFL_DllImport void MsgBox(char *sInBuf);
NSWFL_DllImport void Set_Int(HWND hWnd, int iInput);
NSWFL_DllImport void Set_Long(HWND hWnd, long lInput);
NSWFL_DllImport void Set_Text (HWND hWnd, char *sInBuf);
NSWFL_DllImport void SetFont(HWND hWnd, HFONT hFont);
NSWFL_DllImport void TextBoxWrite(HWND hWnd, char *sInBuf);

//SYSTEM_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define FAccess  6   // Check for read and write permission
#define FRead    4   // Check for read permission
#define FWrite   2   // Check for write permission
#define FExecute 1   // Execute (Ignored)
#define FExist   0   // Check for existence of file

NSWFL_DllImport bool BufferDataToFile(const char *sFile, const char *sBuf, const int iBufSz);
NSWFL_DllImport void CreateFolderStructure(const char *sFullPath);
NSWFL_DllImport bool FileAccess(const char *sFileName, short iMode);
NSWFL_DllImport BOOL Get_MachineNameEx (char *sOutVal);
NSWFL_DllImport BOOL Get_UserNameEx (char *sOutVal);
NSWFL_DllImport bool IsDirectory(const char *sPath);
NSWFL_DllImport bool IsWinNT(void);
NSWFL_DllImport BOOL ResetWindowsSys(UINT uFlags);
NSWFL_DllImport char * Get_CurrentDirectory (void);
NSWFL_DllImport char * Get_LongDate (void);
NSWFL_DllImport char * Get_MachineName (void);
NSWFL_DllImport char * Get_OsVersion (void);
NSWFL_DllImport char * Get_ShortDate (void);
NSWFL_DllImport char * Get_SystemDirectory (void);
NSWFL_DllImport char * Get_TempDirectory (void);
NSWFL_DllImport char * Get_Time (void);
NSWFL_DllImport char * Get_UserName (void);
NSWFL_DllImport char * Get_WindowsDirectory (void);
NSWFL_DllImport DWORD Get_CurrentDirectoryEx (char *sOutVal);
NSWFL_DllImport DWORD Get_FileSize(const char *sFileName);
NSWFL_DllImport DWORD Get_SystemDirectoryEx (char *sOutVal);
NSWFL_DllImport DWORD Get_TempDirectoryEx (char *sOutVal);
NSWFL_DllImport DWORD Get_WindowsDirectoryEx (char *sOutVal);
NSWFL_DllImport int Get_LongDateEx (char *sOutVal);
NSWFL_DllImport int Get_ShortDateEx (char *sOutVal);
NSWFL_DllImport int Get_TimeEx (char *sOutVal);
NSWFL_DllImport void Get_LocalDateTime(DWORD *dwDate, DWORD *dwTime);
NSWFL_DllImport void Get_OsVersionEx (char *sOutVal);
NSWFL_DllImport void Get_SystemDateTime(DWORD *dwDate, DWORD *dwTime);
NSWFL_DllImport void SetApplicationPriority(HANDLE hProcess, HANDLE hThread, int iPriorityClass, short iThreadPriority, bool bProcessBoost, bool bThreadBoost);

//_STRING_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NSWFL_DllImport bool CompareCSString(const char *sBuf1, const char *sBuf2);
NSWFL_DllImport bool CompareNCString(const char *sBuf1, const char *sBuf2);
NSWFL_DllImport bool IsLower(char cIn);
NSWFL_DllImport bool IsNumber(char cIn);
NSWFL_DllImport bool IsNumeric(char *sText);
NSWFL_DllImport bool IsUpper(char cIn);
NSWFL_DllImport bool IsWhiteSpace(char cChar);
NSWFL_DllImport bool ReverseString(char *sBuf, int iBufSz);
NSWFL_DllImport char * LCaseEx (char *sBuf, int iBufSz);
NSWFL_DllImport char * UCaseEx (char *sBuf, int iBufSz);
NSWFL_DllImport char **Split(char *sBuf, char *sSplitOn);
NSWFL_DllImport char **SplitEx(char *sBuf, int iBufSz, char **sArray, int *iOutItems, char *sSplitOn, int iSplitOnSz);
NSWFL_DllImport char *FormatFloatString(char *sOut, int iMaxSz, const char *sIn);
NSWFL_DllImport char *FormatInteger(char *sOut, const long lIn);
NSWFL_DllImport char *FormatiString(char *sOut, const char *sIn);
NSWFL_DllImport char *LCase (char *sBuf);
NSWFL_DllImport char *SimpleCipherString(char *sBuf, int iBufSz);
NSWFL_DllImport char *StringScan(const char *sInBuf, int iStartPos, int iLength);
NSWFL_DllImport char *UCase (char *sBuf);
NSWFL_DllImport char ToLower(char cIn);
NSWFL_DllImport char ToUpper(char cIn);
NSWFL_DllImport int AppendStrings(const char *sBuf1, const char *sBuf2, int iBuf1Sz, int iBuf2Sz, char *sOutBuf);
NSWFL_DllImport int Bin2Hex(const void *lpSrc, int iSz, int iBytes, void *lpTarget);
NSWFL_DllImport int CompareFlagedString(const char *sBuf, const char *sFlag);
NSWFL_DllImport int CopyString(char *sOutBuf, const char *sInBuf, int iInBufSz);
NSWFL_DllImport int GetFirstCharPos(char *sInBuf, int iInBufSz);
NSWFL_DllImport int GetFlagedValue(const char *sBuf, int iSkpLen, int iBufSz, char *sOutBuf);
NSWFL_DllImport int GetLastCharPos(char *sInBuf, int iInBufSz);
NSWFL_DllImport int InStr(const char *sSearchFor, const char *sInBuf);
NSWFL_DllImport int InStrEx(const char *sSearchFor, const char *sInBuf, const int iBufSz, const int iStartPos);
NSWFL_DllImport int InStrExx(const char *sSearchFor, int sSearchForSz, const char *sInBuf, const int iBufSz, const int iStartPos);
NSWFL_DllImport int Left(const char *sInBuf, char *sOutBuf, int iInLen, int iLeft);
NSWFL_DllImport int MidEx(const char *sInBuf, int iInBufSz, int iStartPos, int iRChars, char *sOutBuf);
NSWFL_DllImport int ReplaceCharacter(const char *sInBuf, char *sOutBuf, const char cReplace, const char cWith);
NSWFL_DllImport int ReplaceStrings (const char *sInBuf, const char *sReplace, const char *sWith, char *sOutBuf);
NSWFL_DllImport int Right(const char *sInBuf, char *sOutBuf, int iInLen, int iRight);
NSWFL_DllImport int StrCatEx(char *sOutBuf, const char *sInBuf, int iInBufSz, int iOutBufSz);
NSWFL_DllImport int StringScanEx(const char *sInBuf, int iStartPos, int iLength, char *sOutVal);
NSWFL_DllImport int UBound(char **sArray);
NSWFL_DllImport void FreeArray(char **sArray);
NSWFL_DllImport void FreeArrayEx(char **sArray, int iItems);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
