#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <pthread.h>
#include <string.h>
#include <assert.h>

#include "shared.h"
#include "reader.h"
#include "analyzer.h"
#include "printer.h"
#include "logger.h"

#define TIME_FOR_THREAD_RESPONSE 2

struct ThreadID{
    pthread_t thread_reader_id;
    pthread_t thread_analyzer_id;
    pthread_t thread_printer_id;
    pthread_t thread_watchdog_id;
    pthread_t thread_logger_id;
};

struct ThreadID ThreadID;
atomic_bool terminateWatchdog;

void watchdogMain(void);

#endif