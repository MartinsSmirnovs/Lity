set(TARGET_NAME lity_desktop_app)

include(ExternLibs)

add_executable(${TARGET_NAME}
    WIN32
    main.cpp
)

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Desktop/src ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(${TARGET_NAME} PRIVATE lity_desktop_src)

ADDQT5CORE(${TARGET_NAME})
ADDQT5WIDGETS(${TARGET_NAME})
