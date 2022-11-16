# CUT-cpu-usage-tracker

## How it works

Program has 5 threads:

1. Reader - reads /proc/stat file and sends read data to Analyzer
2. Analyzer - calculates percentage usage of every CPU thread
3. Printer - prints usage in form of horizontal bars and percentage numbers
4. Watchdog - checks if every thread still works. If any freezes, then it attempts to gracefully close all threads and if it's not possible it forces to termination
5. Logger - saves various logs into *.txt file. In worst case scenario there will be two log files, 10MiB each

Program can catch SIGTERM and SIGINT. 

#
Tested on Manjaro and Ubuntu
