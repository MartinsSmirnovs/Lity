set(TARGET_NAME lity_tests)

set(HEADER_FILES
    Tests.h
)

set(SOURCE_FILES
    AnimationTest.cpp
    ConverterTest.cpp
    CrossTest.cpp
    DifferTest.cpp
    FieldTest.cpp
    PointTest.cpp
    SquareTest.cpp
)

add_executable(${TARGET_NAME}
    ${HEADER_FILES}
    ${SOURCE_FILES}
    main.cpp
)

target_link_libraries(${TARGET_NAME} lib_unity lib_lity)

target_include_directories(${TARGET_NAME} PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ${CMAKE_SOURCE_DIR}/lib/lity
                           ${CMAKE_SOURCE_DIR}/lib/unity)

include(CTest)

add_test(NAME ${TARGET_NAME} COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}.exe)
