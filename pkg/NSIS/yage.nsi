; YaGE NSIS Installer Script
; The script is designed to run on AppVeyor, refer to pkg\AppVeyor directory for more information.

CRCCheck On

; Test faster
;SetCompress off

; Real scenario
SetCompressor /SOLID lzma

!include MUI2.nsh
!include XML.nsh

!include utils.nsh

Name "YaGE"
OutFile "yageinst.exe"
ShowInstDetails "show"
ShowUninstDetails "show"
RequestExecutionLevel admin

InstallDir "$PROGRAMFILES\YaGE"

!define MUI_WELCOMEPAGE
!define MUI_LICENSEPAGE
!define MUI_DIRECTORYPAGE
!define MUI_ABORTWARNING
!define MUI_UNINSTALLER
!define MUI_UNCONFIRMPAGE
!define MUI_FINISHPAGE

; Installer
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "../../LICENSE"
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

; Uninstaller
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

!insertmacro MUI_LANGUAGE "English" ;first language is the default language
!insertmacro MUI_LANGUAGE "French"
!insertmacro MUI_LANGUAGE "German"
!insertmacro MUI_LANGUAGE "SimpChinese"
!insertmacro MUI_LANGUAGE "TradChinese"
!insertmacro MUI_LANGUAGE "Japanese"
!insertmacro MUI_LANGUAGE "Korean"

; Version Info
VIProductVersion "0.1.0.0"
VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "Yet another Graphics Engine"
VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "Copyright (C) YaGE developers"
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" "YaGE is under LGPLv3 license"
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "YaGE is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.\n\nYaGE is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.\n\nYou should have received a copy of the GNU Lesser General Public License along with YaGE.  If not, see <http://www.gnu.org/licenses/>."
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "YaGE installer"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "0.1.0.0"
VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductVersion" "0.1.0.0"

Section "install" ;Installation info
    SetOutPath "$INSTDIR"
    File /r ..\..\include
    File /oname=license.txt ..\..\LICENSE
    File /r ..\..\build-bin\doc
    CreateShortcut "$DESKTOP\YaGE English documentation.lnk" "$INSTDIR\doc\english\modules.html"
    CreateShortcut "$DESKTOP\YaGE Chinese documentation.lnk" "$INSTDIR\doc\chinese\modules.html"

    SetOutPath "$INSTDIR\lib"
    File ..\..\build-bin\build-vc9\lib\Release\yagevc9.lib
    File ..\..\build-bin\build-vc9\lib\Debug\yagevc9d.lib
    File ..\..\build-bin\build-vc10\lib\Release\yagevc10.lib
    File ..\..\build-bin\build-vc10\lib\Debug\yagevc10d.lib
    File ..\..\build-bin\build-vc11\lib\Release\yagevc11.lib
    File ..\..\build-bin\build-vc11\lib\Debug\yagevc11d.lib
    File ..\..\build-bin\build-vc12\lib\Release\yagevc12.lib
    File ..\..\build-bin\build-vc12\lib\Debug\yagevc12d.lib

    SetOutPath "$INSTDIR\gtk3\bin"
    File C:\GTK\bin\*.dll
    File C:\GTK\bin\gdk-pixbuf-query-loaders.exe

    SetOutPath "$INSTDIR\gtk3"
    File /r C:\GTK\etc

    SetOutPath "$INSTDIR\gtk3\lib"
    File C:\GTK\lib\*.def
    File C:\GTK\lib\*.lib
    File /r C:\GTK\lib\gdk-pixbuf-2.0
    File /r C:\GTK\lib\gtk-3.0

    SetOutPath "$INSTDIR\gtk3\share\glib-2.0"
    File /r C:\GTK\share\glib-2.0\schemas

    SetOutPath "$INSTDIR\gtk3\share"
    File /r C:\GTK\share\locale

    SetOutPath "$INSTDIR\gtk3\share\icons"
    File /r ..\..\src\res\yage-extent-icon-pack\YaGE

    Push $4
    ; Write MSBuild config file at $4 register, and using $5, $6 register preserved

    StrCpy $4 $LOCALAPPDATA\Microsoft\MSBuild\v4.0\Microsoft.Cpp.Win32.user.props
    IfFileExists "$4" 0 finishwriteconfig
    Push $6
    Push $5
    ${xml::LoadFile} "$4" $5
    IntCmp $5 0 0 finishwritexml finishwritexml

    ; check all paths are available, if not, create it!
    ${xml::GotoPath} /Project $5
    IntCmp $5 0 0 finishwritexml finishwritexml

    ${xml::GotoPath} /Project/ItemDefinitionGroup $5
    IntCmp $5 0 writeitems 0 0
    ${xml::CreateNode} "<ItemDefinitionGroup><ClCompile><AdditionalIncludeDirectories>%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories></ClCompile><Link><AdditionalLibraryDirectories>%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories></Link><Lib><AdditionalLibraryDirectories>%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories></Lib></ItemDefinitionGroup>" $6
    ${xml::InsertEndChild} $6 $5
    goto writecontents

writeitems:
    ${xml::GotoPath} /Project/ItemDefinitionGroup/ClCompile/ $5
    IntCmp $5 0 +4 0 0
    ${xml::CreateNode} "<ClCompile><AdditionalIncludeDirectories>%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories></ClCompile>" $6
    ${xml::InsertEndChild} $6 $5
    goto +5
    ${xml::GotoPath} /Project/ItemDefinitionGroup/ClCompile/AdditionalIncludeDirectories $5
    IntCmp $5 0 +3 0 0
    ${xml::CreateNode} "<AdditionalIncludeDirectories>%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>" $6
    ${xml::InsertEndChild} $6 $5

    ${xml::GotoPath} /Project/ItemDefinitionGroup $5
    ${xml::GotoPath} /Project/ItemDefinitionGroup/Link/ $5
    IntCmp $5 0 +4 0 0
    ${xml::CreateNode} "<Link><AdditionalLibraryDirectories>%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories></Link>" $6
    ${xml::InsertEndChild} $6 $5
    goto +5
    ${xml::GotoPath} /Project/ItemDefinitionGroup/Link/AdditionalLibraryDirectories $5
    IntCmp $5 0 +3 0 0
    ${xml::CreateNode} "<AdditionalLibraryDirectories>%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>" $6
    ${xml::InsertEndChild} $6 $5

    ${xml::GotoPath} /Project/ItemDefinitionGroup $5
    ${xml::GotoPath} /Project/ItemDefinitionGroup/Lib/ $5
    IntCmp $5 0 +4 0 0
    ${xml::CreateNode} "<Lib><AdditionalLibraryDirectories>%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories></Lib>" $6
    ${xml::InsertEndChild} $6 $5
    goto writecontents
    ${xml::GotoPath} /Project/ItemDefinitionGroup/Lib/AdditionalLibraryDirectories $5
    IntCmp $5 0 +3 0 0
    ${xml::CreateNode} "<AdditionalLibraryDirectories>%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>" $6
    ${xml::InsertEndChild} $6 $5

writecontents:
    path::AnsiToUtf8 "$INSTDIR" ; UTF-8 string is saved into $8
    ; header
    ${xml::GotoPath} /Project/ItemDefinitionGroup/ClCompile/AdditionalIncludeDirectories $5
    ${xml::GetText} $6 $5
    ${StrContains} $5 "$8\include;" $6
    StrCmp $5 "" 0 +2
    ${xml::SetText} "$8\include;$6" $5
    ; dynamic library TODO
    ${xml::GotoPath} /Project/ItemDefinitionGroup/Link/AdditionalLibraryDirectories $5
    ${xml::GetText} $6 $5
    ${StrContains} $5 "$8\lib;" $6
    StrCmp $5 "" 0 +2
    ${xml::SetText} "$8\lib;$6" $5
    ; static library
    ${xml::GotoPath} /Project/ItemDefinitionGroup/Lib/AdditionalLibraryDirectories $5
    ${xml::GetText} $6 $5
    ${StrContains} $5 "$8\lib;" $6
    StrCmp $5 "" 0 +2
    ${xml::SetText} "$8\lib;$6" $5
    ${xml::SaveFile} "" $5
finishwritexml:
    ${xml::Unload}
    Pop $5
    Pop $6
finishwriteconfig:
    Pop $4
    path::AddToPath "$INSTDIR\gtk3\bin"
    ExecDos::exec "$INSTDIR\gtk3\bin\gdk-pixbuf-query-loaders.exe" "" "$INSTDIR\gtk3\lib\gdk-pixbuf-2.0\2.10.0\loaders.cache"
    WriteUninstaller "$INSTDIR\uninst.exe"
SectionEnd

Section "Uninstall" ;Uninstaller
    RMDir /r "$INSTDIR\*.*"
    Delete "$DESKTOP\YaGE English documentation.lnk"
    Delete "$DESKTOP\YaGE Chinese documentation.lnk"
    !insertmacro un.RemoveFromPath "$INSTDIR\gtk3\bin"
SectionEnd

Function .onInit
    !insertmacro MUI_LANGDLL_DISPLAY
FunctionEnd
