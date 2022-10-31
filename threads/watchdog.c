#include "watchdog.h"

void watchdogMain(void){
    time_t watchdogTime;
    time_t readerTimeTmp;
    time_t analyzerTimeTmp;
    time_t printerTimeTmp;
    time_t loggerTimeTmp;
    char threadName[10];

    while(atomic_load(&terminateWatchdog) == false){

        usleep(500000);
        watchdogTime = time(NULL);
        readerTimeTmp = atomic_load(&readerTime);
        analyzerTimeTmp = atomic_load(&analyzerTime);
        printerTimeTmp = atomic_load(&printerTime);
        loggerTimeTmp = atomic_load(&loggerTime);

        if((abs( (int)(watchdogTime - readerTimeTmp) ) > TIME_FOR_THREAD_RESPONSE)){
            strcpy(threadName, "Reader");
            break;
        }else if((abs( (int)(watchdogTime - analyzerTimeTmp) ) > TIME_FOR_THREAD_RESPONSE)){
            strcpy(threadName, "Analyzer");
            break;
        }else if((abs( (int)(watchdogTime - printerTimeTmp) ) > TIME_FOR_THREAD_RESPONSE)){
            strcpy(threadName, "Printer");
            break;
        }//else if((abs((int)(watchdogTime - atomic_load(&loggerTime))) > TIME_FOR_THREAD_RESPONSE)){
         //   strcpy(threadName, "Logger");
         //   break;
        //}

    }
    
    if(atomic_load(&terminateWatchdog) == false){
        printf("%s thread didn't responded in time. Threads are being terminated and program will close soon.\n", threadName);
    }else{
        printf("\nReceived SIGTERM/SIGINT. Canceling threads now...\n");
    }

    assert(pthread_cancel(ThreadID.thread_printer_id) == 0);
    assert(pthread_cancel(ThreadID.thread_analyzer_id) == 0);
    assert(pthread_cancel(ThreadID.thread_reader_id) == 0);
    //assert(pthread_cancel(ThreadID.thread_logger_id) == 0);
    
    pthread_exit(0);

    return;
}