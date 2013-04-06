echo Run this from the visual c++ commandline

set buildFolder=build

mkdir %buildFolder%

set libraryName=libLinkAPI
set srcFile=LinkAPI

set vcDirectory=D:\Program Files (x86)\Microsoft Visual Studio 10.0\VC
set sdkDirectory=D:\Program Files\Microsoft SDKs\Windows\v7.1


cd %buildFolder%

   REM # 32-Bit version: #
REM ### set the path:   ###
set LIB=%vcDirectory%\LIB;%sdkDirectory%\Lib;
REM ### compile: 		###
cl.exe /EHcs /Fe"%libraryName%.dll" "..\..\..\src\%srcFile%.cpp" /I "%sdkDirectory%\Include" /I "%vcDirectory%\include" /link /DLL


  REM # 64-Bit version: #
REM ### set the path:   ###
set LIB=%vcDirectory%\lib\amd64;%sdkDirectory%\Lib\x64
REM ### compile: 		###
"%vcDirectory%\bin\x86_amd64\cl.exe" /EHcs /Fe"%libraryName%64.dll" "..\..\..\src\%srcFile%.cpp" /I "%sdkDirectory%\Include" /I "%vcDirectory%\include" /link /DLL

  REM # cleaning up #
del *.obj
del *.exp

cd ..

   REM # Check the dependencies (if new LIBs need to be included, except KERNEL32.dll that one is always there): #
REM ### 32-Bit version: ###
"%vcDirectory%\bin\x86_amd64\dumpbin.exe" /IMPORTS "%buildFolder%\%libraryName%.dll"
REM ### 64-Bit version: ###
"%vcDirectory%\bin\x86_amd64\dumpbin.exe" /IMPORTS "%buildFolder%\%libraryName%64.dll"

  REM # Check the if the exports are there as expected: #
REM ### 32-Bit version: ###
"%vcDirectory%\bin\x86_amd64\dumpbin.exe" /EXPORTS "%buildFolder%\%libraryName%.dll"
REM ### 64-Bit version: ###
"%vcDirectory%\bin\x86_amd64\dumpbin.exe" /EXPORTS "%buildFolder%\%libraryName%64.dll"


































