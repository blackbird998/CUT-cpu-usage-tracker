#ifndef PRINTER_H
#define PRINTER_H

#include <stdio.h>
#include "shared.h"
#include "uint_ringbuffer.h"

#define PRINT_DIVIDER 1

extern bool printerClosed;
extern atomic_bool terminatePrinter;
extern atomic_long printerTime;

struct PrinterMessages{
    char message[200];
    atomic_bool newMessageFlag;
};

extern struct PrinterMessages PrinterMessages;

void printerMain(uint_ring_buffer_t* uint_ring_buffer);

#endif
