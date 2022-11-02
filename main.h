#ifndef MAIN_H
#define MAIN_H

#define _XOPEN_SOURCE 700 // Fixes Clang error with signal handling

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

int terminate(void);
void catchSignal(void);

#endif
