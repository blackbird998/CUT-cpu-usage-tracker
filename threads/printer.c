#include "printer.h"

void printerMain(uint_ring_buffer_t* uint_ring_buffer){

    __int16_t cpuStatsSize = getCoreNumberPlusOne(); // + 1 is for summary of all cpus
    struct CPU_Percentage CPU_Percentage[cpuStatsSize];
    printf("\n===printer===\n");

    while(atomic_load(&terminatePrinter) == false){
        atomic_store(&printerTime, time(NULL));
        usleep(1000000);
//        usleep(3000000); // For watchdog DEBUG
        system("clear");
        pthread_mutex_lock(&mutexCPU_Percentage);
            uint_ring_buffer_dequeue_arr(uint_ring_buffer, CPU_Percentage, cpuStatsSize);
        pthread_mutex_unlock(&mutexCPU_Percentage);

        __uint16_t i, j;
        for(__uint16_t n = 0; n < cpuStatsSize; ++n){
            //printf("%d\n", n);
            printf("%s [", CPU_Percentage[n].cpu_number);

            i = 0;
            for(i = 0; i < (CPU_Percentage[n].percentage/PRINT_DIVIDER); i++){
                printf("%c", '|');
                //printf("%d\n", i);
            }
            for(j = i; j < (100/PRINT_DIVIDER); j++){
                printf("%c", ' ');
                //printf("%d\n", i);
            }
            printf("] %d%%\n", CPU_Percentage[n].percentage);
        }
    }
    pthread_exit(0);

// TODO terminate

}