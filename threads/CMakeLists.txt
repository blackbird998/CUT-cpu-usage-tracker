target_link_libraries(${PROJECT_NAME} PRIVATE shared ringbuffer)
#target_include_directories(${PROJECT_NAME} PRIVATE ../common)
include_directories(BEFORE ../common)

add_library(
    reader SHARED
    reader.h
    reader.c
)
add_library(
    analyzer SHARED
    analyzer.h
    analyzer.c
)
add_library(
    printer SHARED
    printer.h
    printer.c
)
add_library(
    watchdog SHARED
    watchdog.h
    watchdog.c
)
add_library(
    logger SHARED
    logger.h
    logger.c
)

target_include_directories(reader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(analyzer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(printer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(watchdog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
