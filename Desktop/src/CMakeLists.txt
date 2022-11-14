set(TARGET_NAME lity_desktop_src)

FILE(GLOB HEADER_FILES ${CMAKE_SOURCE_DIR}/lib/lity/*.h lity/widgets/*.h lity/*.h)
FILE(GLOB SOURCE_FILES ${CMAKE_SOURCE_DIR}/lib/lity/*.cpp lity/widgets/*.cpp lity/*.cpp)
FILE(GLOB FORMS lity/widgets/*.ui)

include(ExternLibs)

add_library(
    ${TARGET_NAME}
    ${HEADER_FILES}
    ${SOURCE_FILES}
    ${FORMS}
)

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lity ${CMAKE_SOURCE_DIR}/lib)

ADDQT5CORE(${TARGET_NAME})
ADDQT5WIDGETS(${TARGET_NAME})
