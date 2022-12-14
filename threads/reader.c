#include "reader.h"

bool readerClosed = false;
atomic_bool terminateReader;
atomic_long readerTime;
struct ReaderMessages ReaderMessages;

FILE *filePointer;

void readFile(struct Stats* cpuStats){
    char temporary_cpu_number[CPU_NAME_SIZE];
    __uint16_t n = 0;

    if( (filePointer = fopen(PATH, "r")) == NULL ){
        printf("ERROR: File does not exist or it can't be opened!\n");
        exit(1);
    }

    n = 0;
    pthread_mutex_lock(&mutexStats);
    while(1){
        fscanf(filePointer, "%s", temporary_cpu_number);
        if('c' != temporary_cpu_number[0]){
            break;
        }

        strcpy(cpuStats[n].cpu_number, temporary_cpu_number);

        fscanf(filePointer, "%lu %lu %lu %lu %lu %lu %lu %lu %lu %lu", 
               &(cpuStats[n].user), 
               &(cpuStats[n].nice), 
               &(cpuStats[n].system), 
               &(cpuStats[n].idle), 
               &(cpuStats[n].iowait), 
               &(cpuStats[n].irq), 
               &(cpuStats[n].softirq), 
               &(cpuStats[n].steal), 
               &(cpuStats[n].guest), 
               &(cpuStats[n].guest_nice));

        ++n;
    }
    pthread_mutex_unlock(&mutexStats);
    //system("cat /proc/stat"); // For debugging

    if(NULL != filePointer){
        fclose(filePointer);
    }
    cpuStats[0].cpu_number[3] = 'A'; // A for All to compensate for lack of number

    return;
}

void readerMain(ring_buffer_t *ring_buffer){

    __int16_t cpuStatsSize = getCoreNumberPlusOne(); // + 1 is for summary of all cpus
    struct Stats cpuStats[cpuStatsSize]; 

    ring_buffer_init(ring_buffer);
    
    while(atomic_load(&terminateReader) == false){
        atomic_store(&readerTime, time(NULL));
        readFile(cpuStats);
        ring_buffer_queue_arr(ring_buffer, cpuStats, cpuStatsSize);
        usleep(900000);
    }
    readerClosed = true;
    pthread_exit(0);
}
