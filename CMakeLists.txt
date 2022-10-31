cmake_minimum_required(VERSION 3.20)

project(CUT-cpu-usage-tracker)

SET(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -g -O0")
SET(GCC_COVERAGE_LINK_FLAGS    "-lpthread -lm")

SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_executable(${PROJECT_NAME} main.c)

add_subdirectory(threads)
add_subdirectory(common)

target_link_libraries(${PROJECT_NAME} PRIVATE shared reader ringbuffer uint_ringbuffer analyzer printer watchdog logger)


