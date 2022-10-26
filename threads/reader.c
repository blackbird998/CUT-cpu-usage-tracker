#include "reader.h"

#include <unistd.h> //TEMP
#include <string.h>

#define PATH "/proc/stat"
#define CPU_NAME_SIZE 10

/**
 * @brief Documentation: https://www.kernel.org/doc/Documentation/filesystems/proc.txt
 * 
 */

struct Stats {
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

void readFile(){
    FILE *filePointer;

    if(NULL == (filePointer = fopen(PATH, "r"))){
        printf("ERROR: File does not exist or it can't be opened!");
        exit(1);
    }

    __int16_t numberOfProcessors = sysconf(_SC_NPROCESSORS_ONLN); // Get number of cpus to monitor
    struct Stats cpuStats[numberOfProcessors + 1]; // + 1 is for summary of all cpus
    char temporary_cpu_number[CPU_NAME_SIZE];
    
    __uint16_t n = 0;
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

    //system("cat /proc/stat"); // For debugging

    if(NULL != filePointer){
        fclose(filePointer);
    }

    return;
}



void readerMain(){

}

