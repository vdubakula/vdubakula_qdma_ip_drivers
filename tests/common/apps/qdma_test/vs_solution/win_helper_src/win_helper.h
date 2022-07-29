#ifndef _WIN_HELPER_H
#define _WIN_HELPER_H

#include <Windows.h>
#include <errno.h>

static void sleep(DWORD dwMilliseconds)
{
    Sleep(dwMilliseconds);
}

static void usleep(__int64 usec)
{
    HANDLE timer;
    LARGE_INTEGER ft;

    ft.QuadPart = -(10 * usec); // Convert to 100 nanosecond interval, negative value indicates relative time

    timer = CreateWaitableTimer(NULL, TRUE, NULL);
    SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);

}


enum xnl_st_c2h_cmpt_desc_size {
	XNL_ST_C2H_CMPT_DESC_SIZE_8B,
	XNL_ST_C2H_CMPT_DESC_SIZE_16B,
	XNL_ST_C2H_CMPT_DESC_SIZE_32B,
	XNL_ST_C2H_CMPT_DESC_SIZE_64B
};

#endif