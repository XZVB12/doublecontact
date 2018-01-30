; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "DoubleContact"
#define MyAppVersion "0.1.3"
#define MyAppPublisher "DarkHobbit"
#define MyAppURL "https://github.com/DarkHobbit/doublecontact/"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{7F7DFA90-E881-4C7E-80AB-A0342789AB25}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
;AppPublisherURL={#MyAppURL}
;AppSupportURL={#MyAppURL}
;AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\DarkHobbit\{#MyAppName}
DefaultGroupName=\DarkHobbit\{#MyAppName}
;AllowNoIcons=yes
OutputBaseFilename=doublecontact_{#MyAppVersion}_win32_setup
;Compression=lzma
;SolidCompression=yes
LicenseFile=.\doc\COPYING

[Files]
Source: ".\doublecontact.exe"; DestDir: "{app}"; Flags: ignoreversion; Components: DoubleContact
Source: ".\contconv.exe"; DestDir: "{app}"; Flags: ignoreversion; Components: ContConv

Source: ".\iso639-1.utf8"; DestDir: "{app}"; Flags: ignoreversion; Components: Translations
Source: ".\doublecontact_en_GB.qm"; DestDir: "{app}"; Flags: ignoreversion; Components: Translations
Source: ".\doublecontact_nb_NO.qm"; DestDir: "{app}"; Flags: ignoreversion; Components: Translations
Source: ".\doublecontact_nl.qm"; DestDir: "{app}"; Flags: ignoreversion; Components: Translations
Source: ".\doublecontact_ru_RU.qm"; DestDir: "{app}"; Flags: ignoreversion; Components: Translations
Source: ".\doublecontact_uk_UA.qm"; DestDir: "{app}"; Flags: ignoreversion; Components: Translations
Source: ".\qt_ru.qm"; DestDir: "{app}"; Flags: ignoreversion; Components: Translations
Source: ".\qt_uk.qm"; DestDir: "{app}"; Flags: ignoreversion; Components: Translations
; Currently, no official qt_*.qm for nl and nb_NO

Source: ".\libgcc_s_dw2-1.dll"; DestDir: "{app}"; Flags: ignoreversion; Components: Libraries

Source: ".\doc\changelog"; DestDir: "{app}\doc"; Flags: ignoreversion; Components: Docs
Source: ".\doc\COPYING"; DestDir: "{app}\doc"; Flags: ignoreversion; Components: Docs
Source: ".\doc\manual.en.md"; DestDir: "{app}\doc"; Flags: ignoreversion; Components: Docs
Source: ".\doc\manual.rus.md"; DestDir: "{app}\doc"; Flags: ignoreversion; Components: Docs
Source: ".\doc\README.md"; DestDir: "{app}\doc"; Flags: ignoreversion; Components: Docs

[Icons]
Name: "{group}\DoubleContact"; Filename: "{app}\doublecontact.exe"; WorkingDir: "{app}"; IconFilename: "{app}\doublecontact.exe"; IconIndex: 0; Components: DoubleContact
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"

[Components]
Name: "DoubleContact"; Description: {cm:dcname}; Types: full custom doublecontact
Name: "ContConv"; Description: {cm:ccname}; Types: full custom contconv
Name: "Docs"; Description: {cm:docname}; Types: custom full doublecontact contconv; Flags: fixed
Name: "Translations"; Description: {cm:trname}; Types: custom full doublecontact; Flags: fixed
Name: "Libraries"; Description: {cm:libname}; Types: custom full doublecontact contconv; Flags: fixed

[Types]
Name: "full"; Description: {cm:stfull}
Name: "custom"; Description: {cm:stcustom}; Flags: iscustom
Name: "doublecontact"; Description: {cm:stdconly}
Name: "contconv"; Description: {cm:stcconly}

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"
Name: "ukrainian"; MessagesFile: "compiler:Languages\Ukrainian.isl"

[CustomMessages]
english.dcname=DoubleContact GUI application
english.ccname=Console format convertor
english.docname=Documentation
english.trname=Translation files
english.libname=Common libraries
english.stfull=Full
english.stcustom=Custom
english.stdconly=DoubleContact only
english.stcconly=ContConv only

russian.dcname=��������� DoubleContact
russian.ccname=���������� ��������� ��������
russian.docname=������������
russian.trname=��������
russian.libname=����� ����������
russian.stfull=������
russian.stcustom=����������
russian.stdconly=������ DoubleContact
russian.stcconly=������ ���������� ���������

ukrainian.dcname=�������� DoubleContact
ukrainian.ccname=���������� ��������� �������
ukrainian.docname=������������
ukrainian.trname=���������
ukrainian.libname=�������� ��������
ukrainian.stfull=�����
ukrainian.stcustom=��������
ukrainian.stdconly=���� DoubleContact
ukrainian.stcconly=���� ���������� ���������

[Dirs]
Name: "{app}"

