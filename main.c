#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "reader.h"
#include "shared.h"
#include "ringbuffer.h"



int main(void){
    printf("Hi\n");
    ring_buffer_t ring_buffer;

    pthread_t thread_reader_id;
    //pthread_t thread_analyzer_id;
    //pthread_t thread_printer_id;
    //pthread_t thread_watchdog_id;
    //pthread_t thread_logger_id;

    //readFile();
    pthread_create(&thread_reader_id, NULL, (void*)readerMain, &ring_buffer);
    pause();
    return 0;
}