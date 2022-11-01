#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#include "shared.h"
#include "watchdog.h"
#include "reader.h"
#include "analyzer.h"
#include "printer.h"
#include "logger.h"
#include "ringbuffer.h"
#include "uint_ringbuffer.h"

int terminate(void){
    atomic_store(&terminateWatchdog, true);
    return 0;
}

int main(void){

    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = (void*)terminate;
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGINT, &action, NULL);


    atomic_init(&terminateReader, false);
    atomic_init(&terminateAnalyzer, false);
    atomic_init(&terminatePrinter, false);
    atomic_init(&terminateLogger, false);
    atomic_init(&terminateWatchdog, false);

    ring_buffer_t ring_buffer;
    uint_ring_buffer_t uint_ring_buffer;
    struct argStruct argStruct;
    argStruct.ring_buffer_ptr = &ring_buffer;
    argStruct.uint_ring_buffer_ptr = &uint_ring_buffer;


    pthread_create(&ThreadID.thread_reader_id, NULL, (void*)readerMain, &ring_buffer);
    usleep(50000);

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