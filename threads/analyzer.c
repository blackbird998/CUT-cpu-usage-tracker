#include "analyzer.h"

void analyzerMain(struct argStruct* argStruct){

    __int16_t cpuStatsSize = getCoreNumberPlusOne(); // + 1 is for summary of all cpus
    struct Stats cpuStats[cpuStatsSize];
    __uint64_t PrevIdle[cpuStatsSize], Idle[cpuStatsSize], PrevNonIdle[cpuStatsSize], NonIdle[cpuStatsSize], PrevTotal[cpuStatsSize], Total[cpuStatsSize], totald[cpuStatsSize], idled[cpuStatsSize];
    struct CPU_Percentage CPU_Percentage[cpuStatsSize];
    //double percentageDouble;

    while(1){
        pthread_mutex_lock(&mutexStats);
            ring_buffer_dequeue_arr(argStruct->ring_buffer_ptr, cpuStats, cpuStatsSize); // TODO - check if empty / returned 0
        pthread_mutex_unlock(&mutexStats);

        for(__uint16_t n = 0; n < cpuStatsSize; ++n){
            PrevIdle[n] = cpuStats[n].idle + cpuStats[n].iowait;
            PrevNonIdle[n] = cpuStats[n].user + cpuStats[n].nice + cpuStats[n].system + cpuStats[n].irq + cpuStats[n].steal;
            PrevTotal[n] = PrevIdle[n] + PrevNonIdle[n];
        }

        usleep(500000);

        pthread_mutex_lock(&mutexStats);
            ring_buffer_dequeue_arr(argStruct->ring_buffer_ptr, cpuStats, cpuStatsSize);
        pthread_mutex_unlock(&mutexStats);

        for(__uint16_t n = 0; n < cpuStatsSize; ++n){
            Idle[n] = cpuStats[n].idle + cpuStats[n].iowait;
            NonIdle[n] = cpuStats[n].user + cpuStats[n].nice + cpuStats[n].system + cpuStats[n].irq + cpuStats[n].steal;
            Total[n] = Idle[n] + NonIdle[n];

            totald[n] = Total[n] - PrevTotal[n];
            idled[n] = Idle[n] - PrevIdle[n];

            if(0 != totald[n]){
                //percentageDouble = ((double)(totald[n] - idled[n])/(double)totald[n])*100;
                CPU_Percentage[n].percentage = round(((double)(totald[n] - idled[n])/(double)totald[n])*100);
                strcpy(CPU_Percentage[n].cpu_number, cpuStats[n].cpu_number);
            }
            
        }

        pthread_mutex_lock(&mutexCPU_Percentage);
            uint_ring_buffer_queue_arr(argStruct->uint_ring_buffer_ptr, CPU_Percentage, cpuStatsSize);
        pthread_mutex_unlock(&mutexCPU_Percentage);

    }
}