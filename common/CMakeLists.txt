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

target_include_directories(shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ringbuffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
