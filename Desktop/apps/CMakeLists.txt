set(TARGET_NAME lity_desktop_app)

include(ExternLibs)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/settings.ini.in settings.ini)

add_executable(${TARGET_NAME}
    WIN32
    main.cpp
)

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Desktop/src ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(${TARGET_NAME} PRIVATE lity_desktop_src)

ADDQT5CORE(${TARGET_NAME})
ADDQT5WIDGETS(${TARGET_NAME})

add_custom_target(${TARGET_NAME}_deploy ALL C:/Qt/5.15.2/msvc2019_64/bin/windeployqt.exe ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}.exe)

add_dependencies(${TARGET_NAME}_deploy ${TARGET_NAME})
