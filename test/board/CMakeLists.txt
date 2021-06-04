# Check hardwarespecific Files


if(${CMAKE_SYSTEM_NAME} STREQUAL "Arduino")
    add_executable(test_board    test_board_arduino.cpp)
    target_link_arduino_libraries(test_board PRIVATE SPI core)
    target_link_libraries(test_board PRIVATE openiolink)
    target_enable_arduino_upload(test_board)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
        add_executable(test_board    test_board_raspi.cpp)
        target_link_libraries(test_board Catch openiolink)
    else()
#        add_executable(test_board    test_board_dummy.cpp)
#        target_link_libraries(test_board Catch openiolink)
        add_executable(test_board   test_MapperIOLPort.cpp)
        target_link_libraries(test_board  openiolink)
    endif()
                            
endif()


