echo off
set arg1=%1
shift
REM msbuild makeshape.sln /p:Configuration=Debug /nologo /verbosity:quiet /target:%arg1%
"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\msbuild.exe" makeshape.sln /p:Configuration=Debug /nologo /verbosity:quiet /target:%arg1%
