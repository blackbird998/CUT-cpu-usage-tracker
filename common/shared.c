#include "shared.h"

__int16_t getCoreNumberPlusOne(void){
    return (__int16_t)(sysconf(_SC_NPROCESSORS_ONLN) + 1); // Get number of cpus to monitor
}

pthread_mutex_t mutexStats = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexCPU_Percentage = PTHREAD_MUTEX_INITIALIZER;
