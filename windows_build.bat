:: =============================================
:: this script builds with MinGW
::
:: for this script to work on your machine,
:: you have to set the paths for BUILD TOOLS,
:: where these are installed on your machine.
:: =============================================

@echo off

:: ================== BUILD TOOLS ===========================
:: set your paths to qmake and make here.
:: for qmake using msvc, you need Visual Studio 2015 or 2017
:: valid compilers are in Qt folder C:\Qt\Qt5.14.2\5.14.2
:: -> mingw73_32, mingw73_64, msvc2015_64, msvc2017, msvc2017_64
set COMPILER=mingw73_32
set QTDIR=C:\Qt\Qt5.14.2\5.14.2\%COMPILER%
set MINGWDIR=C:\MinGW\bin
set QMAKE=%QTDIR%\bin\qmake.exe
set MAKE=%MINGWDIR%\mingw32-make.exe
:: !! there is a compatibility issue between
:: your compiler you want to use and with which compiler
:: your build tools have been compiled. So, you want
:: e.g. to compile your application with mingw, then
:: you need a qmake and make that has also been compiled
:: with mingw. Also be aware of the x86 or x64 versions
:: of your build tools.
:: ==========================================================

:: ================== PATHS =================================
:: add Qt and MinGW to path.
:: when using a Microsoft compiler add e.g. "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.12.25827\bin\Hostx64\x64" to your path, so you can call cl. that example shows how to add the compiler msvc2017_64 (Visual Studio 2017)
set path=%path%;%QTDIR%\bin;%MINGWDIR%;
:: ==========================================================

::set QMakeSpec=win32-msvc
set QMakeSpec=%QTDIR%\mkspecs\win32-g++

:: ==================== Start Building ======================
echo QTDIR=%QTDIR%
echo QMAKE=%QMAKE%
echo MAKE=%MAKE%
echo using compiler %COMPILER%
echo running qmake

%QMAKE% -config release -o Makefile anwalic.pro
:: stop here, if qmake ran into an error
if %errorlevel% neq 0 PAUSE exit /b

echo running make
%MAKE%
:: ==========================================================

PAUSE
