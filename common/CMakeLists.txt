add_library(
    shared SHARED
    shared.h
    shared.c
)
add_library(
    ringbuffer SHARED
    ringbuffer.h
    ringbuffer.c
)
add_library(
    uint_ringbuffer SHARED
    uint_ringbuffer.h
    uint_ringbuffer.c
)

target_include_directories(shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ringbuffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(uint_ringbuffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})