add_library(
    reader SHARED
    reader.h
    reader.c
)

target_include_directories(reader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})