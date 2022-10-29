#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "reader.h"
#include "shared.h"
#include "analyzer.h"
#include "ringbuffer.h"
#include "uint_ringbuffer.h"




int main(void){
    printf("Hi\n");
    ring_buffer_t ring_buffer;
    uint_ring_buffer_t uint_ring_buffer;
    struct argStruct argStruct;
    argStruct.ring_buffer_ptr = &ring_buffer;
    argStruct.uint_ring_buffer_ptr = &uint_ring_buffer;

    pthread_t thread_reader_id;
    pthread_t thread_analyzer_id;
    //pthread_t thread_printer_id;
    //pthread_t thread_watchdog_id;
    //pthread_t thread_logger_id;

    //readFile();
    pthread_create(&thread_reader_id, NULL, (void*)readerMain, &ring_buffer);
    usleep(50000);
    pthread_create(&thread_analyzer_id, NULL, (void*)analyzerMain, &argStruct);
    pause();
    return 0;
}