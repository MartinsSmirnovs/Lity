function(ADDQT5CORE TARGET_NAME)
        find_package(Qt5 COMPONENTS Core REQUIRED)
        target_link_libraries(${TARGET_NAME} PRIVATE Qt5::Core)
endfunction()

function(ADDQT5WIDGETS TARGET_NAME)
        find_package(Qt5 COMPONENTS Widgets REQUIRED)
        target_link_libraries(${TARGET_NAME} PRIVATE Qt5::Widgets)
endfunction()
