# Example only works on Arduino and RaspberryPi
if((${CMAKE_SYSTEM_NAME} STREQUAL "Arduino") OR ((${CMAKE_SYSTEM_NAME} STREQUAL "Linux") AND (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "arm")))
    add_subdirectory(watertank)
endif()