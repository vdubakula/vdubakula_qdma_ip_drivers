@ECHO off

SET mode=%1
SET dir=%2
SET num_q=%3
SET runtime=%4
SET pkt_sz=%5


IF [%mode%] neq [st] IF [%mode%] neq [mm] GOTO ERROR_EXIT
IF [%dir%] neq [h2c] IF [%dir%] neq [c2h] GOTO ERROR_EXIT

IF [%num_q%] == [0] GOTO ERROR_EXIT
IF [%num_q%] == [] GOTO ERROR_EXIT

IF [%runtime%] == [0] GOTO ERROR_EXIT
IF [%runtime%] == [] GOTO ERROR_EXIT

IF [%pkt_sz%] == [0] GOTO ERROR_EXIT
IF [%pkt_sz%] == [] GOTO ERROR_EXIT


SET /a "q_end=%num_q%-1"

REM COMMENT : Prepare the configuration file
ECHO mode=%mode% >  perf_config
ECHO dir=%dir% >>  perf_config
ECHO pf_range=0:0 >>  perf_config
ECHO q_range=0:%q_end% >>  perf_config
ECHO flags= >>  perf_config
ECHO rngidx=9 >>  perf_config
ECHO cmpl_status_acc=5 >>  perf_config
ECHO runtime=%runtime% #msecs >>  perf_config
ECHO dump_en=0 >>  perf_config
ECHO num_threads=3 >>  perf_config
ECHO num_pkt=64 >>  perf_config
ECHO pkt_sz=%pkt_sz% >>  perf_config
ECHO pci_bus=17>>  perf_config
ECHO pci_device=00>>  perf_config


REM : SET EXE_DIR=..\..\..\..\..\sw_host\mdma\windows\build\x64\Debug\bin
SET EXE_DIR=..\..\..\..\..\sw_host\mdma\windows\build\x64\Release\bin
REM COMMENT : Queue 0 in ST Mode

SET qid=0
:QUEUE_ADD_START
REM COMMENT : Queue 0 Add and Start
IF [%mode%] == [st] (
%EXE_DIR%\qdma_ctl.exe pf 0 queue add mode %mode% idx_h2c_ringsz 9 idx_c2h_ringsz 9 trigmode every qid %qid% >> cmd_log.txt
) else (
%EXE_DIR%\qdma_ctl.exe pf 0 queue add mode %mode% idx_h2c_ringsz 9 idx_c2h_ringsz 9 qid %qid% >> cmd_log.txt
)
%EXE_DIR%\qdma_ctl.exe pf 0 queue start qid %qid% >> cmd_log.txt
SET /a "qid=%qid%+1"
IF /I %qid% GEQ %num_q% GOTO QUEUE_ADD_END
GOTO QUEUE_ADD_START

:QUEUE_ADD_END
REM COMMENT : %EXE_DIR%\qdma_arw.exe -c %EXE_DIR%\h2c_st_1_1_cmptsz0_4096
%EXE_DIR%\qdma_perf.exe -c perf_config >> perf_results.txt

SET qid=0
:QUEUE_STOP_START
REM COMMENT : Queue 0 Stop and Delete
%EXE_DIR%\qdma_ctl.exe pf 0 queue stop qid %qid% >> cmd_log.txt
%EXE_DIR%\qdma_ctl.exe pf 0 queue delete qid %qid% >> cmd_log.txt
SET /a "qid=%qid%+1"
IF /I %qid% GEQ %num_q% GOTO QUEUE_STOP_END
GOTO QUEUE_STOP_START

:QUEUE_STOP_END
:EXIT
	ECHO Performance Executed Successfully  >> cmd_log.txt
	GOTO END

:ERROR_EXIT
	ECHO Incorrect Parameters Passed..Please check and run again
	GOTO END

:END