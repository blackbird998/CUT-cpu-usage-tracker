#ifndef PRINTER_H
#define PRINTER_H

#include <stdio.h>
#include "shared.h"
#include "uint_ringbuffer.h"

#define PRINT_DIVIDER 1

void printerMain(uint_ring_buffer_t* uint_ring_buffer);

#endif