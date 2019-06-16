echo off
REM msbuild makeshape.sln /p:Configuration=Debug /nologo /verbosity:minimal 
msbuild makeshape.sln /p:Configuration=Release /nologo /verbosity:quiet
