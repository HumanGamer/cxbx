rem Pack Release Build with UPX

echo Packing with UPX ...

cd ..\build\bin\Release

echo Packing Cxbx.exe ...
upx -9 Cxbx.exe
echo Packing Cxbx.dll ...
upx -9 Cxbx.dll

copy Cxbx.exe ..\Export\Release\
copy Cxbx.dll ..\Export\Release\

cd ..\scripts

echo Done
