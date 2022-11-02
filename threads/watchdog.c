#include "watchdog.h"

struct ThreadID ThreadID;
struct WatchdogMessages WatchdogMessages;
atomic_bool terminateWatchdog;

void watchdogMain(void){
    time_t watchdogTime;
    time_t readerTimeTmp;
    time_t analyzerTimeTmp;
    time_t printerTimeTmp;
    time_t loggerTimeTmp;
    char threadName[10];


    //atomic_init(WatchdogMessages.message, "\n");
    atomic_init(&WatchdogMessages.newMessageFlag, false);

    while(atomic_load(&terminateWatchdog) == false){

        usleep(500000);
        watchdogTime = time(NULL);
        readerTimeTmp = atomic_load(&readerTime);
        analyzerTimeTmp = atomic_load(&analyzerTime);
        printerTimeTmp = atomic_load(&printerTime);
        loggerTimeTmp = atomic_load(&loggerTime);

        if((abs( (int)(watchdogTime - readerTimeTmp) ) > TIME_FOR_THREAD_RESPONSE)){
            strcpy(threadName, "Reader");
            sendWatchdogMessage("Reader thread didn't responded in time. Threads are being terminated and program will close soon.\n");
            break;
        }else if((abs( (int)(watchdogTime - analyzerTimeTmp) ) > TIME_FOR_THREAD_RESPONSE)){
            strcpy(threadName, "Analyzer");
            sendWatchdogMessage("Analyzer thread didn't responded in time. Threads are being terminated and program will close soon.\n");
            break;
        }else if((abs( (int)(watchdogTime - printerTimeTmp) ) > TIME_FOR_THREAD_RESPONSE)){
            strcpy(threadName, "Printer");
            sendWatchdogMessage("Printer thread didn't responded in time. Threads are being terminated and program will close soon.\n");
            break;
        }else if((abs((int)(watchdogTime - loggerTimeTmp) ) > TIME_FOR_THREAD_RESPONSE)){
            strcpy(threadName, "Logger");
            printf("LOGGER ERROR: Some logs might be missing!\n");
            break;
        }
    }
    
    if(atomic_load(&terminateWatchdog) == false){
        printf("%s thread didn't responded in time. Threads are being terminated and program will close soon.\n", threadName);
    }else{
        printf("\nReceived SIGTERM/SIGINT. Canceling threads now...\n");
        sendWatchdogMessage("\tReceived SIGTERM/SIGINT. Canceling threads now...\n");
    }

// Attempt to send signal to threads to exit by themselves
    atomic_store(&terminatePrinter, true);
    atomic_store(&terminateAnalyzer, true);
    atomic_store(&terminateReader, true);
    usleep(1500000); //50ms


// Checking if threads closed gracefully. If not force cancel.
    if(printerClosed != true){
        printf("Failed to gracefully close Printer Thread. Will force cancel.\n");
        sendWatchdogMessage("Failed to gracefully close Printer Thread. Will force cancel.\n");
        assert(pthread_cancel(ThreadID.thread_printer_id) == 0);
    }else{
        printf("Printer Thread closed gracefully.\n");
        sendWatchdogMessage("Printer Thread closed gracefully.\n");
    }

    if(analyzerClosed != true){
        printf("Failed to gracefully close Analyzer Thread. Will force cancel.\n");
        sendWatchdogMessage("Failed to gracefully close Analyzer Thread. Will force cancel.\n");
        assert(pthread_cancel(ThreadID.thread_analyzer_id) == 0);
    }else{
        printf("Analyzer Thread closed gracefully.\n");
        sendWatchdogMessage("Analyzer Thread closed gracefully.\n");
    }

    if(readerClosed != true){
        printf("Failed to gracefully close Reader Thread. Will force cancel.\n");
        sendWatchdogMessage("Failed to gracefully close Reader Thread. Will force cancel.\n");
        assert(pthread_cancel(ThreadID.thread_reader_id) == 0);
    }else{
        printf("Reader Thread closed gracefully.\n");
        sendWatchdogMessage("Reader Thread closed gracefully.\n");

    }

    // Give time to logger to save logs
    usleep(1000000); // 500ms

    // Terminate logger
    atomic_store(&terminateLogger, true);
    usleep(500000); //50ms
    
    if(loggerClosed != true){
        printf("LOGGER ERROR: Failed to gracefully close Logger Thread. Will force cancel. Some logs might be missing!\n");
        assert(pthread_cancel(ThreadID.thread_reader_id) == 0);
    }else{
        printf("Logger Thread closed gracefully. This log will be missing in log file.\n");
    }
    
    pthread_exit(0);
}

bool sendWatchdogMessage(char* message){
    for(__int16_t i = 0; i < 5; ++i){
            if( atomic_load(&WatchdogMessages.newMessageFlag) == false ){
                strcpy(WatchdogMessages.message, message);
                usleep(10000);
                atomic_store(&WatchdogMessages.newMessageFlag, true);
                return true;
            }
            usleep(10000);
    }
    return false;
}
