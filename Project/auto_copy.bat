@echo off

:: hex 转 bin

set SRC_PATH=.\Objects\
set HEX_FILE=PMCU_DEMO_V01.hex
set BIN_FILE=PMCU_DEMO_V01.bin
::.\tool\hex2bin.exe -b %SRC_PATH%\%HEX_FILE%  %SRC_PATH%\%BIN_FILE%
.\tool\hex2bin.exe  %SRC_PATH%\%HEX_FILE%  %SRC_PATH%\%BIN_FILE%

::查找烧录器

for /f "tokens=2 delims==" %%a  in ('wmic LogicalDisk where "DriveType='2'" get DeviceID /value') do (
      set DriveU=%%a
    )
echo.%DriveU%
::删除旧文件
::del /s /Q %DriveU%	
del %DriveU%\*.bin



set RENAME_TOOL_PATH= .\tool
set RENAME_TOOL_EXE=pmcu_bin_crc.exe
set CFG_FILE=configure.ini
set RENAME_OUTPUT_PAHT= .\rename
::删除老文件
del %RENAME_OUTPUT_PAHT%\*.bin
::重命名bin
%RENAME_TOOL_PATH%\%RENAME_TOOL_EXE%  %RENAME_TOOL_PATH%\%CFG_FILE%  %SRC_PATH%\%BIN_FILE%  %RENAME_OUTPUT_PAHT%


::复制新文件
@echo on

copy %RENAME_OUTPUT_PAHT%\*.bin  %DriveU%\
::pause
