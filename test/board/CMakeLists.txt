# Check hardwarespecific Files
if(${CMAKE_SYSTEM_NAME} STREQUAL "Arduino")
    add_executable(test_board    test_board_arduino.cpp)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "arm")
        add_executable(test_board    test_board_raspi.cpp)
    else()
        add_executable(test_board    test_board_dummy.cpp)
    endif()
                            
endif()

target_link_libraries(test_board Catch openiolink)


add_custom_command(TARGET test_board POST_BUILD COMMAND cp -v test_board ~/rpi/)