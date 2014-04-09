@ECHO OFF
REM Copy all needed DLLs to be with the exe
SET solnDir=%1%
SET outDir=%2%
SET DLL_Folder=%solnDir%third_party\third_party_DLLs\

xcopy /s/y %DLL_Folder%* %outDir%