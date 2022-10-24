#include "reader.h"

#define PATH "/proc/stat"

/**
 * @brief Documentation: https://www.kernel.org/doc/Documentation/filesystems/proc.txt
 * 
 */
struct Stats {
    char cpu_number[5];     // cpu number
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

int readFile(struct Stats *stat){
    FILE *filePointer;

    if(NULL == (filePointer = fopen(PATH, "r"))){
        printf("ERROR: File does not exist or it can't be opened!");
        exit(1);
    }

    //struct Stats stat;

    //while(0 != 
    //fscanf(filePointer, "%s, %lu, %lu, %lu, %d, %d, %d, %d, %d, %d", stat.cpu_number, &(stat.user), &(stat.nice), &(stat.system), &(stat.idle), &(stat.iowait), &(stat.irq), &(stat.softirq), &(stat.steal), &(stat.guest), &(stat.guest_nice));//)

    fscanf(filePointer, "%s %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu", stat->cpu_number, &(stat->user), &(stat->nice), &(stat->system), &(stat->idle), &(stat->iowait), &(stat->irq), &(stat->softirq), &(stat->steal), &(stat->guest), &(stat->guest_nice));
    system("cat /proc/stat");

    //printf("%s, %lu, %lu, %lu, %d, %d, %d, %d, %d, %d", stat.cpu_number, stat.user, stat.nice, stat.system, stat.idle, stat.iowait, stat.irq, stat.softirq, stat.steal, stat.guest, stat.guest_nice);

    printf("%lu, %lu, %lu, ", /*stat->cpu_number,*/ stat->user, stat->nice, stat->system);
    fclose(filePointer);

    return 0;
}

