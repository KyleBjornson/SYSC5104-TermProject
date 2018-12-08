#include "platform.h"

typedef unsigned long long RTIME;

void clockInit();
void inc(void);
RTIME rt_timer_read(void);
void hw_sleep(void);
void hw_check(void);
int sleepFor(RTIME);
int sleepUntil(RTIME);
int isInterrupted(void);
void setInterrupted(void);
//void clearInterrupted(void);
/*
#ifdef __cplusplus
    extern "C" {
#endif
*/
void stopTimer(void);
void resumeTimer(void);
/*
#ifdef __cplusplus
     }
#endif
*/


