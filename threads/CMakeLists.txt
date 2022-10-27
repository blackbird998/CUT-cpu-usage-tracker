target_link_libraries(${PROJECT_NAME} PRIVATE shared ringbuffer)
#target_include_directories(${PROJECT_NAME} PRIVATE ../common)
include_directories(BEFORE ../common)

add_library(
    reader SHARED
    reader.h
    reader.c
)

target_include_directories(reader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#add_subdirectory(../common ../build/common)

