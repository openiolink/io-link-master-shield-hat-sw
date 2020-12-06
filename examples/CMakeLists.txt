# Example only works on Arduino and RaspberryPi
if(${CMAKE_SYSTEM_NAME} STREQUAL "Arduino")
    add_subdirectory(watertank)
endif()
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    if((${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm"))
        add_subdirectory(watertank)
    endif()
endif()