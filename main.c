#include "main.h"

int terminate(void){
    atomic_store(&terminateWatchdog, true);
    return 0;
}

void catchSignal(void){
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = (void*)terminate;
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGINT, &action, NULL);
}

int main(void){

    ring_buffer_t ring_buffer;
    uint_ring_buffer_t uint_ring_buffer;
    struct argStruct argStruct;

    catchSignal();

    argStruct.ring_buffer_ptr = &ring_buffer;
    argStruct.uint_ring_buffer_ptr = &uint_ring_buffer;

    atomic_init(&terminateReader, false);
    atomic_init(&terminateAnalyzer, false);
    atomic_init(&terminatePrinter, false);
    atomic_init(&terminateLogger, false);
    atomic_init(&terminateWatchdog, false);

    pthread_create(&ThreadID.thread_reader_id, NULL, (void*)readerMain, &ring_buffer);
    usleep(50000); // Warning caused by _XOPEN_SOURCE 700 in main.h

    pthread_create(&ThreadID.thread_analyzer_id, NULL, (void*)analyzerMain, &argStruct);
    usleep(50000);

    pthread_create(&ThreadID.thread_printer_id, NULL, (void*)printerMain, &uint_ring_buffer);
    usleep(50000);

    pthread_create(&ThreadID.thread_logger_id, NULL, (void*)loggerMain, NULL);
    usleep(50000);

    pthread_create(&ThreadID.thread_watchdog_id, NULL, (void*)watchdogMain, NULL);

    assert(pthread_join(ThreadID.thread_watchdog_id, NULL) == 0);
    //pthread_join(ThreadID.thread_watchdog_id, NULL);

    printf("Main thread closing...\n");

    return 0;
}
