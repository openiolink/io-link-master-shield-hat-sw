
add_library(openiolink  OpenIOLink.hpp
                        board/IOLMasterPortMax14819.hpp
                        board/IOLMasterPortMax14819.cpp
                        board/Max14819.hpp
                        board/Max14819.cpp
                        protocol/IOLMasterPort_old.cpp
                        protocol/IOLMasterPort_old.hpp
                        protocol/IOLMasterPort.cpp
                        protocol/IOLMasterPort.hpp
                        protocol/HardwareBase.hpp
                        protocol/IOLink.hpp
                        protocol/HardwareBase.cpp
                        protocol/IOLGenericDevice.cpp
                        protocol/IOLGenericDevice.hpp
                        sensors/BalluffBus0023.cpp
                        sensors/BalluffBni0088.cpp
                        sensors/BalluffBus0023.hpp
                        sensors/BalluffBni0088.hpp)

# Check hardwarespecific Files
if(${CMAKE_SYSTEM_NAME} STREQUAL "Arduino")
    add_library(arduionohw  board/HardwareArduino.hpp
                            board/HardwareArduino.cpp)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "arm")
        add_library(raspberrypihw  board/HardwareRaspberry.hpp
                                board/HardwareRaspberry.cpp)
        target_link_libraries(openiolink raspberrypihw)
        target_link_libraries(raspberrypihw openiolink)
        find_library(WIRINGPI_LIB wiringPi REQUIRED) # TODO clean-up
        target_link_libraries(openiolink ${WIRINGPI_LIB})
        target_link_libraries(openiolink pthread rt) # TODO clean-up
    else()
    endif()
                            
endif()

set_target_properties(openiolink PROPERTIES CXX_STANDARD_REQUIRED 11 CXX_STANDARD 14)
target_include_directories(openiolink PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})