@echo off
echo "Nefry用設定ファイル"
echo "書き込みを開始します。"
  
for /D %%a in (%appdata%\Arduino15\packages\Nefry\hardware\esp8266\*) do (
cd "%%a"
for /f "delims=" %%i in (platform.txt) do (
set "line=%%i"
call :replace
)
)
goto :end

:replace
set "line=%line:>=^>%"
set "line=%line:<=^<%"
set "line=%line:&=^&%"
set "line=%line:|=^|%"
set "line=%line:{build.path}/arduino.bin={nefry.path}/arduino.bin%"
echo %line% >>dump.txt
exit /B

:end

del platform.txt
ren dump.txt platform.txt
echo, 
echo --------------------------------------------------
echo Nefryで使うファイルの保存場所を決めます。
echo Nefryフォルダを作成し、そこにファイルを保存します。
echo,
echo 入力できるもの
echo  0 :Documentsフォルダ（推奨） 1 :Desktop (どちらも半角数字)
echo 他のフォルダが良い場合:（例） C:\Users\Public\Documents 
echo --------------------------------------------------
set /P FOLDER="保存先を入力してください。: "
echo,  
if %FOLDER% == 0 (
	call :Documents
) else if %FOLDER% == 1 (
	call :Desktop
) else (
	call :Other
)
goto :setting
:Documents
cd %USERPROFILE%\Documents
set USR_INPUT=%USERPROFILE%\Documents
mkdir Nefry
echo Documentsフォルダに保存します。
exit /B

:Desktop
cd %USERPROFILE%\Desktop
set  USR_INPUT=%USERPROFILE%\Desktop
mkdir Nefry
echo Desktopに保存します。
exit /B

:Other
cd %FOLDER%
set  USR_INPUT=%FOLDER%
mkdir Nefry
echo %FOLDER%に保存します。
exit /B

:setting


cd "%appdata%\Arduino15"
FIND /V "nefry.path" preferences.txt >TEMP.TXT
COPY /Y TEMP.TXT preferences.txt >NUL
DEL TEMP.TXT
echo nefry.path= %USR_INPUT%\Nefry>>preferences.txt
echo "書き込みを完了しました。"
pause