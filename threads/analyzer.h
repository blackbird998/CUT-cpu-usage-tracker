#ifndef ANALYZER_H
#define ANALYZER_H

#include "shared.h"
#include "ringbuffer.h"
#include "uint_ringbuffer.h"

#include <math.h>
#include <string.h>

bool analyzerClosed = false;
atomic_bool terminateAnalyzer;
atomic_long analyzerTime;

struct argStruct {
    ring_buffer_t* ring_buffer_ptr;
    uint_ring_buffer_t* uint_ring_buffer_ptr;
};

struct AnalyzerMessages{
    char message[200];
    atomic_bool newMessageFlag;
};

struct AnalyzerMessages AnalyzerMessages;

void analyzerMain(struct argStruct* argStruct);

#endif