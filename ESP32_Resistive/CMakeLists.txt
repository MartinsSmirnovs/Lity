set(TARGET_NAME lity_esp32_resistive)

add_custom_target( ${TARGET_NAME}_x86_test
                   platformio test --environment Testing_x86
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})