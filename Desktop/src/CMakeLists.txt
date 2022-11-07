set(TARGET_NAME lity_desktop_src)


FILE(GLOB HEADER_FILES lity/logic/*.h)
FILE(GLOB SOURCE_FILES lity/logic/*.cpp)

include(ExternLibs)

add_library(${TARGET_NAME}
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

ADDQT5CORE(${TARGET_NAME})
ADDQT5WIDGETS(${TARGET_NAME})
