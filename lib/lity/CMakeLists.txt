set(TARGET_NAME lib_lity)

file(GLOB HEADER_FILES *.h)
file(GLOB SOURCE_FILES *.cpp)

add_library(${TARGET_NAME}
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
