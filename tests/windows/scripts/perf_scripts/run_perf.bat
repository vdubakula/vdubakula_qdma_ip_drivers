@ECHO off

SET mode=st
SET dir=h2c
SET runtime=1000
SET num_q=1
SET pkt_sz=64

ECHO  > cmd_log.txt
ECHO  > perf_results.txt

ECHO Running performance application: mode: %mode% dir : %dir% num_q : %num_q% runtime : %runtime%
ECHO Running performance application: mode: %mode% dir : %dir% num_q : %num_q% runtime : %runtime% >> perf_results.txt

:PKTSZ_UPDATE
ECHO PACKET SIZE : %pkt_sz%
CALL perf_analysis.bat %mode% %dir% %num_q% %runtime% %pkt_sz%
SET /a "pkt_sz=%pkt_sz%*2"
IF /I %pkt_sz% GEQ 32768 GOTO ST_C2H
TIMEOUT 1 >> cmd_log.txt
GOTO PKTSZ_UPDATE


:ST_C2H
REM COMMENT : ST C2H is not supported right now
GOTO MM_H2C
REM SET pkt_sz=64
REM SET dir=c2h
REM ECHO Running performance application: mode: %mode% dir : %dir% num_q : %num_q% runtime : %runtime%
REM ECHO Running performance application: mode: %mode% dir : %dir% num_q : %num_q% runtime : %runtime% >> perf_results.txt
REM GOTO PKTSZ_UPDATE2

REM 
REM :PKTSZ_UPDATE2
REM ECHO PACKET SIZE : %pkt_sz%
REM CALL perf_analysis.bat %mode% %dir% %num_q% %runtime% %pkt_sz%
REM SET /a "pkt_sz=%pkt_sz%*2"
REM IF /I %pkt_sz% GEQ 32768 GOTO MM_H2C
REM TIMEOUT 1 >> cmd_log.txt
REM GOTO PKTSZ_UPDATE2


:MM_H2C
SET pkt_sz=64
SET mode=mm
SET dir=h2c
ECHO Running performance application: mode: %mode% dir : %dir% num_q : %num_q% runtime : %runtime%
ECHO Running performance application: mode: %mode% dir : %dir% num_q : %num_q% runtime : %runtime% >> perf_results.txt
GOTO PKTSZ_UPDATE3

:PKTSZ_UPDATE3
ECHO PACKET SIZE : %pkt_sz%
CALL perf_analysis.bat %mode% %dir% %num_q% %runtime% %pkt_sz%
SET /a "pkt_sz=%pkt_sz%*2"
IF /I %pkt_sz% GEQ 32768 GOTO MM_C2H
TIMEOUT 1 >> cmd_log.txt
GOTO PKTSZ_UPDATE3


:MM_C2H
ECHO "MM C2H"
SET pkt_sz=64
SET mode=mm
SET dir=c2h
ECHO Running performance application: mode: %mode% dir : %dir% num_q : %num_q% runtime : %runtime%
ECHO Running performance application: mode: %mode% dir : %dir% num_q : %num_q% runtime : %runtime% >> perf_results.txt
GOTO PKTSZ_UPDATE4

:PKTSZ_UPDATE4
ECHO PACKET SIZE : %pkt_sz%
CALL perf_analysis.bat %mode% %dir% %num_q% %runtime% %pkt_sz%
SET /a "pkt_sz=%pkt_sz%*2"
IF /I %pkt_sz% GEQ 32768 GOTO EXIT
TIMEOUT 1 >> cmd_log.txt
GOTO PKTSZ_UPDATE4


:EXIT
	ECHO DONE
