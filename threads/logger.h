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

extern bool loggerClosed;
extern atomic_long loggerTime;
extern atomic_bool terminateLogger;

extern FILE* logPointer;

#define LOG_PATH_1 "CUT_log1.txt"
#define LOG_PATH_2 "CUT_log2.txt"

int openLog(void);
void loggerMain(void);

#endif
