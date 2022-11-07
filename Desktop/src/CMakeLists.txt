set(TARGET_NAME lity_desktop_src)

FILE(GLOB HEADER_FILES lity/logic/*.h lity/widgets/*.h)
FILE(GLOB SOURCE_FILES lity/logic/*.cpp lity/widgets/*.cpp)
FILE(GLOB FORMS lity/widgets/*.ui)

include(ExternLibs)

add_library(${TARGET_NAME}
    ${HEADER_FILES}
    ${SOURCE_FILES}
    ${FORMS}
)

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lity)

ADDQT5CORE(${TARGET_NAME})
ADDQT5WIDGETS(${TARGET_NAME})
