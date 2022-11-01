/**
 * @brief Documentation of Linux /proc file system: https://www.kernel.org/doc/Documentation/filesystems/proc.txt
 * 
 */

#ifndef READER_H
#define READER_H

#include "shared.h"
#include "ringbuffer.h"

#include <stdio.h> // Used for handling file operations
#include <stdlib.h>
#include <unistd.h> // Used for _SC_NPROCESSORS_ONLN macro needed to determine number of online cores
#include <string.h>

#define PATH "/proc/stat"

bool readerClosed = false;
atomic_bool terminateReader;
atomic_long readerTime;

FILE *filePointer;

struct ReaderMessages{
    char message[200];
    atomic_bool newMessageFlag;
};

struct ReaderMessages ReaderMessages;

void readerMain(ring_buffer_t *ring_buffer);
void readFile(struct Stats* cpuStats);

#endif