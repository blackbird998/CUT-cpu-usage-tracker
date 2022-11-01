#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "shared.h"
#include "reader.h"
#include "analyzer.h"
#include "printer.h"
#include "watchdog.h"

bool loggerClosed;
atomic_long loggerTime;
atomic_bool terminateLogger;

FILE* logPointer = NULL;

#define LOG_PATH_1 "CUT_log1.txt"
#define LOG_PATH_2 "CUT_log2.txt"

int openLog();
void loggerMain(void);

#endif