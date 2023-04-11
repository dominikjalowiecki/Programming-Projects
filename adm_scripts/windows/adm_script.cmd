@ECHO OFF

ECHO.
ECHO @Dominik Jalowiecki
ECHO Aktualny czas: %date% %time:~0,5% & ECHO.
ECHO ----------------------------------
ECHO 1 - Wlacz konto administratora
ECHO 2 - Wylacz konto administratora
ECHO 3 - Wlacz funkcje hibernacji
ECHO 4 - Wylacz funkcje hibernacji
ECHO 5 - Wyjdz ze skryptu & ECHO.

:: Glowna petla skryptu
:MAIN
	SET /P CHOICE="> Wybierz odpowiednia funkcje: " & ECHO.

	IF %CHOICE% EQU 1 (
		CALL :ADMIN_EN
	) ELSE IF %CHOICE% EQU 2 (
		CALL :ADMIN_DIS
	) ELSE IF %CHOICE% EQU 3 (
		CALL :HIBERNATION_EN
	) ELSE IF %CHOICE% EQU 4 (
		CALL :HIBERNATION_DIS
	) ELSE IF %CHOICE% EQU 5 (
		GOTO :EXIT
	) ELSE (
		ECHO -	PODANA AKCJA NIE ISTNIEJE! & ECHO.
	)
	
	GOTO :MAIN

:ADMIN_EN
	
	NET USER Administrator /active:yes
	IF %errorlevel% EQU 0 ECHO +	Konto administratora zostalo wlaczone! & ECHO.
	GOTO :EOF

:ADMIN_DIS

	NET USER Administrator /active:no
	IF %errorlevel% EQU 0 ECHO +	Konto administratora zostalo wylaczone! & ECHO.
	GOTO :EOF

:HIBERNATION_EN

	POWERCFG.EXE /HIBERNATE ON
	IF %errorlevel% EQU 0 ECHO +	Funkcja hibernacji zostala wlaczona! & ECHO.
	GOTO :EOF

:HIBERNATION_DIS

	POWERCFG.EXE /HIBERNATE OFF
	IF %errorlevel% EQU 0 ECHO +	Funkcja hibernacji zostala wylaczona! & ECHO.
	GOTO :EOF

:EXIT

	ECHO Wychodzenie ze skryptu... & ECHO.
	PAUSE
	EXIT /B