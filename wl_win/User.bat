@echo off 
echo [HANDLER]: Launching Server.
set hh=%time:~0,2%&set mm=%time:~3,2%&set ss=%time:~6,5%
if "%time:~3,1%"=="0" set /a mm="%time:~4,1%"
if "%time:~0,1%"=="0" set /a mm="%time:~1,1%"
md %cd%\log
copy %cd%\server_log.txt %cd%\log\tmplog.txt
ren %cd%\log\tmplog.txt %date:~0,4%%date:~5,2%%date:~8,2%%hh%%mm%%ss%.log
echo [backup]server_log.txt backup in %cd%\log\%date:~0,4%%date:~5,2%%date:~8,2%%hh%%mm%%ss%.log
del %cd%\server_log.txt
:restart
samp-server.exe
echo [HANDLER]: Server Crashed.
pause
echo [HANDLER]: Server Restarting.
set hh=%time:~0,2%&set mm=%time:~3,2%&set ss=%time:~6,5%
if "%time:~3,1%"=="0" set /a mm="%time:~4,1%"
if "%time:~0,1%"=="0" set /a mm="%time:~1,1%"
md %cd%\log
copy %cd%\server_log.txt %cd%\log\tmplog.txt
ren %cd%\log\tmplog.txt %date:~0,4%%date:~5,2%%date:~8,2%%hh%%mm%%ss%.log
echo [backup]server_log.txt backup in %cd%\log\%date:~0,4%%date:~5,2%%date:~8,2%%hh%%mm%%ss%.log
del %cd%\server_log.txt

goto restart

