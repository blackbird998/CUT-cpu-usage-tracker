cmake_minimum_required(VERSION 3.20)

project(CUT-cpu-usage-tracker)

add_executable(${PROJECT_NAME} main.c)
add_subdirectory(theads)