[Setup]
;-- Main Setup Information
 AppName                = IP-Lister
 AppVerName             = IP-Lister 1.0.0.4
 AppCopyright           = Copyright © 1995-2009 NetworkDLS.
 DefaultDirName         = {pf}\NetworkDLS\IP-Lister
 DefaultGroupName       = NetWorkDLS\IP-Lister
 UninstallDisplayIcon   = {app}\IPLister.Exe
 WizardImageFile        = \..\..\@Resources\Setup\LgSetup.bmp
 WizardSmallImageFile   = \..\..\@Resources\Setup\SmSetup.bmp
 PrivilegesRequired     = PowerUser
 Uninstallable          = Yes
 AppMutex               = IP-Lister
 LicenseFile            = \..\..\@Resources\Setup\EULA.txt
 compression            = ZIP/9
 OutputBaseFilename     = Setup
 MinVersion             = 0.0,5.0

;-- Windows 2000 & XP (Support Dialog)
 AppPublisher    = NetworkDLS
 AppPublisherURL = http://www.NetworkDLS.com/
 AppUpdatesURL   = http://www.NetworkDLS.com/
 AppVersion      = 1.0.0.4

[Tasks]
 Name: desktopicon;         Description: "Create a &desktop icon";    GroupDescription: "Additional icons:"; Flags: unchecked;
 Name: desktopicon\common;  Description: "For all users";             GroupDescription: "Additional icons:"; Flags: exclusive;
 Name: desktopicon\user;    Description: "For the current user only"; GroupDescription: "Additional icons:"; Flags: exclusive unchecked;

[Files]
 Source: "..\..\@AutoUpdate\Win32\AutoUpdate.Exe"; DestDir: "{app}"; Flags: RestartReplace;
 Source: "AutoUpdate.xml";                        DestDir: "{app}"; Flags: IgnoreVersion;
 Source: "..\Release\IPLister.Exe";               DestDir: "{app}"; Flags: IgnoreVersion;

[Icons]
 Name: "{group}\IP-Lister";          Filename: "{app}\IPLister.Exe";
 Name: "{group}\AutoUpdate";         Filename: "{app}\AutoUpdate.Exe";
 Name: "{group}\Uninstall";          Filename: "{uninstallexe}";
 Name: "{commondesktop}\IP-Lister";  Filename: "{app}\IPLister.Exe"; Tasks: desktopicon\common;
 Name: "{userdesktop}\IP-Lister";    Filename: "{app}\IPLister.Exe"; Tasks: desktopicon\user;

[Run]
 Filename: "{app}\IPLister.Exe"; Description: "Launch application"; Flags: postinstall nowait skipifsilent unchecked

[Registry]
 Root: HKLM; Subkey: "Software\NetWorkDLS\IPLister"; Flags: uninsdeletekey noerror;
 Root: HKLM; Subkey: "Software\NetWorkDLS\IPLister"; ValueType: dword;  ValueName: "IsAddressList"; ValueData:1;  Flags: createvalueifdoesntexist
 Root: HKLM; Subkey: "Software\NetWorkDLS\IPLister"; ValueType: dword;  ValueName: "IsReverse";     ValueData:0;  Flags: createvalueifdoesntexist
 Root: HKLM; Subkey: "Software\NetWorkDLS\IPLister"; ValueType: dword;  ValueName: "IsAliases";     ValueData:0;  Flags: createvalueifdoesntexist
 Root: HKLM; Subkey: "Software\NetWorkDLS\IPLister"; ValueType: dword;  ValueName: "IsAlwaysOnTop"; ValueData:0;  Flags: createvalueifdoesntexist
 Root: HKLM; Subkey: "Software\NetWorkDLS\IPLister"; ValueType: string; ValueName: "LastUserInput"; ValueData:"LocalHost"; Flags: createvalueifdoesntexist
 
