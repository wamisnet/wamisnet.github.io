@echo off
echo "Nefry用設定ファイル"
echo "書き込みを開始します。"
  
echo, 
echo 注意：Arduino IDEを閉じてから実行してください!
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
echo "書き込みを完了しました。"
pause
