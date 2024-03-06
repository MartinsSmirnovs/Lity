set(TARGET_NAME lib_unity)

add_library(${TARGET_NAME} STATIC unity.c)
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
