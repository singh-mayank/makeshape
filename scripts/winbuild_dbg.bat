echo off
REM msbuild makeshape.sln /p:Configuration=Debug /nologo /verbosity:minimal 
REM msbuild makeshape.sln /p:Configuration=Debug /nologo /verbosity:quiet
"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\msbuild.exe" makeshape.sln /p:Configuration=Debug /nologo /verbosity:quiet
