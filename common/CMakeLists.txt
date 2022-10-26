add_library(
    shared SHARED
    shared.h
    shared.c
)

target_include_directories(shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
