#ifndef ANALYZER_H
#define ANALYZER_H

#include "shared.h"
#include "ringbuffer.h"
#include "uint_ringbuffer.h"

#include <math.h>
#include <string.h>

struct argStruct {
    ring_buffer_t* ring_buffer_ptr;
    uint_ring_buffer_t* uint_ring_buffer_ptr;
};



void analyzerMain(struct argStruct* argStruct);

#endif