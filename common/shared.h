#ifndef SHARED_H
#define SHARED_H

#define CPU_NAME_SIZE 10

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <time.h>

#include <assert.h>

struct Stats{
    char cpu_number[CPU_NAME_SIZE];     // cpu number
    __uint64_t user;         // normal processes executing in user mode
    __uint64_t nice;         // niced processes executing in user mode
    __uint64_t system;       // processes executing in kernel mode
    __uint64_t idle;         // twiddling thumbs
    __uint64_t iowait;       // waiting for I/O to complete, NOT reliable
    __uint64_t irq;          // servicing interrupts
    __uint64_t softirq;      // servicing softirqs
    __uint64_t steal;        // involuntary wait
    __uint64_t guest;        // running a normal guest
    __uint64_t guest_nice;   // running a niced guest
};

struct CPU_Percentage{
    __uint16_t percentage;
    char cpu_number[CPU_NAME_SIZE];
};

extern pthread_mutex_t mutexStats;
extern pthread_mutex_t mutexCPU_Percentage;

__int16_t getCoreNumberPlusOne(void);

#endif
