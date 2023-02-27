set(TARGET_NAME lity_esp32_resistive)

add_test(NAME ${TARGET_NAME}_x86_test
         COMMAND platformio test --environment Testing_x86
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Empty target that allows to not to build anything and
# perform testing right away in vscode
add_custom_target(testing)
