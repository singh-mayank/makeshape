echo off
set arg1=%1
shift
msbuild makeshape.sln /p:Configuration=Debug /nologo /verbosity:quiet /target:%arg1%
