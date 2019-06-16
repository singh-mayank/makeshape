echo off
REM msbuild makeshape.sln /p:Configuration=Debug /nologo /verbosity:minimal 
msbuild makeshape.sln /p:Configuration=Debug /nologo /verbosity:quiet
