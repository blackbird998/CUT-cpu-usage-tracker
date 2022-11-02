#include "logger.h"

bool loggerClosed = false;
atomic_long loggerTime;
atomic_bool terminateLogger;

FILE* logPointer;

int openLog(void){
    struct stat buf;
    stat(LOG_PATH_1, &buf);
    off_t log1Size = buf.st_size; // File size in bytes
    stat(LOG_PATH_2, &buf);
    off_t log2Size = buf.st_size; // File size in bytes
    
    __int16_t oldLogFlag = 1;

    // Store logs in the non full log file (there are two in total). Log file is full when size exceeds 10MiB
    if( (log1Size < (10*1024*1024)) && (log2Size < (10*1024*1024)) ){
        // Both files not full
        //a-
        assert( ((logPointer = fopen(LOG_PATH_1, "a")) != NULL) );
    }else if( (log1Size >= (10*1024*1024)) && (log2Size < (10*1024*1024)) ){
        // First file full, second not full
        oldLogFlag = 1;
        //-a
        assert( ((logPointer = fopen(LOG_PATH_2, "a")) != NULL) );
    }else if( (log1Size >= (10*1024*1024)) && (log2Size >= (10*1024*1024)) ){
        //Both files full
        if(1 == oldLogFlag){
            //First file is older
            //w-
            assert( ((logPointer = fopen(LOG_PATH_1, "w")) != NULL) );
        }else{
            //Second file is older
            //-w
            assert( ((logPointer = fopen(LOG_PATH_2, "w")) != NULL) );
        }
    }else if( (log1Size < (10*1024*1024)) && (log2Size >= (10*1024*1024)) ){
        // First file not full, second file full
        oldLogFlag = 2;
        //a-
        assert( ((logPointer = fopen(LOG_PATH_1, "a")) != NULL) );
    }else{
        printf("LOGGER ERROR");
        return 1;
    }
    return 0;
}

void loggerMain(void){
    
    char buffer[200];

    if(openLog() == 0){
        time_t timeL;
        time(&timeL);
        char newLine[1] = "\n";
        fputs(newLine, logPointer);
        fputs(ctime(&timeL), logPointer);
        fclose(logPointer);
    }

    while(atomic_load(&terminateLogger) == false){
        atomic_store(&loggerTime, time(NULL));
        usleep(50000); // 50ms

        if(atomic_load(&ReaderMessages.newMessageFlag) == true){
            strcpy(buffer, ReaderMessages.message);
            atomic_store(&ReaderMessages.newMessageFlag, false);
            if(openLog() == 0){
                fputs(buffer, logPointer);
                fclose(logPointer);
            }else{
                printf("LOGGER ERROR: Failed to open log file.\n");
            }
        }

        if(atomic_load(&AnalyzerMessages.newMessageFlag) == true){
            strcpy(buffer, AnalyzerMessages.message);
            atomic_store(&AnalyzerMessages.newMessageFlag, false);
            if(openLog() == 0){
                fputs(buffer, logPointer);
                fclose(logPointer);
            }else{
                printf("LOGGER ERROR: Failed to open log file.\n");
            }
        }
        
        if(atomic_load(&PrinterMessages.newMessageFlag) == true){
            strcpy(buffer, PrinterMessages.message);
            atomic_store(&PrinterMessages.newMessageFlag, false);
            if(openLog() == 0){
                fputs(buffer, logPointer);
                fclose(logPointer);
            }else{
                printf("LOGGER ERROR: Failed to open log file.\n");
            }
        }

        if(atomic_load(&WatchdogMessages.newMessageFlag) == true){
            strcpy(buffer, WatchdogMessages.message);
            atomic_store(&WatchdogMessages.newMessageFlag, false);
            if(openLog() == 0){
                fputs(buffer, logPointer);
                if(NULL != logPointer){
                    fclose(logPointer);
                }
            }else{
                printf("LOGGER ERROR: Failed to open log file.\n");
            }
        }
    }

    loggerClosed = true;
    pthread_exit(0);
}
