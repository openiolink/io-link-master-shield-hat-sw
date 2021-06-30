set(CATCH_INCLUDE_DIR ./Catch2/single_include/catch2/)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

# Check hardwarespecific Files
if(${CMAKE_SYSTEM_NAME} STREQUAL "Arduino")
#test on Arduino
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
    add_compile_definitions(RASPBERRY) #test on Raspberry Pi
    else()
        add_subdirectory(protocol) #test on Linux PC only
    endif()
                            
endif()

add_subdirectory(board)