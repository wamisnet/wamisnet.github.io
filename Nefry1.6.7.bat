@echo off
echo "Nefry�p�ݒ�t�@�C��"
echo "�������݂��J�n���܂��B"
  
echo, 
echo ���ӁFArduino IDE����Ă�����s���Ă�������!
echo --------------------------------------------------
echo Nefry�Ŏg���t�@�C���̕ۑ��ꏊ�����߂܂��B
echo Nefry�t�H���_���쐬���A�����Ƀt�@�C����ۑ����܂��B
echo,
echo ���͂ł������
echo  0 :Documents�t�H���_�i�����j 1 :Desktop (�ǂ�������p����)
echo ���̃t�H���_���ǂ��ꍇ:�i��j C:\Users\Public\Documents 
echo --------------------------------------------------
set /P FOLDER="�ۑ������͂��Ă��������B: "
echo,  
if %FOLDER% == 0 (
	call :Documents
) else if %FOLDER% == 1 (
	call :Desktop
) else (
	call :Other
)
for /D %%a in (%USERPROFILE%\AppData\Local\Arduino15\packages\Nefry\hardware\esp8266\*) do (
cd "%%a"
for /f "delims=" %%i in (platform.txt) do (
set "line=%%i"
call :replace
)
del platform.txt
ren dump.txt platform.txt
call :nefry
)
goto :end

:Documents
cd %USERPROFILE%\Documents
set USR_INPUT=%USERPROFILE%\Documents
mkdir Nefry
echo Documents�t�H���_�ɕۑ����܂��B
exit /B

:Desktop
cd %USERPROFILE%\Desktop
set  USR_INPUT=%USERPROFILE%\Desktop
mkdir Nefry
echo Desktop�ɕۑ����܂��B
exit /B

:Other
cd %FOLDER%
set  USR_INPUT=%FOLDER%
mkdir Nefry
echo %FOLDER%�ɕۑ����܂��B
exit /B

:replace
set "line=%line:>=^>%"
set "line=%line:<=^<%"
set "line=%line:&=^&%"
set "line=%line:|=^|%"
set "line=%line:{build.path}/arduino.bin={nefry.path}/arduino.bin%"
echo %line% >>dump.txt
exit /B


:nefry
find /v "nefry.path=" < platform.txt >dump.txt
del platform.txt
ren dump.txt platform.txt
echo nefry.path= %USR_INPUT%\Nefry>>platform.txt
exit /B

:end
echo "�������݂��������܂����B"
pause
