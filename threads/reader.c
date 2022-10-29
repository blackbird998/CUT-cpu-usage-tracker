#include "reader.h"

void readFile(struct Stats* cpuStats){
    FILE *filePointer;
    char temporary_cpu_number[CPU_NAME_SIZE];
    __uint16_t n = 0;


    if(NULL == (filePointer = fopen(PATH, "r"))){
        printf("ERROR: File does not exist or it can't be opened!");
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

    //ring_buffer_queue_arr(&ring_buffer, cpuStats, cpuStatsSize);


    if(NULL != filePointer){
        fclose(filePointer);
    }
    

    return;
}

void readerMain(ring_buffer_t *ring_buffer){

    __int16_t cpuStatsSize = getCoreNumberPlusOne(); // + 1 is for summary of all cpus
    struct Stats cpuStats[cpuStatsSize]; 

    ring_buffer_init(ring_buffer);
    
    while(1){
        readFile(cpuStats);
        ring_buffer_queue_arr(ring_buffer, cpuStats, cpuStatsSize);
        usleep(500000);
    }

}

