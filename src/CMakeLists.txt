
add_library(openiolink  OpenIOLink.hpp
                        protocol/IOLinkConfig.hpp
                        protocol/IOLMessage.hpp
                        protocol/IOLMessage.cpp
                        protocol/IOLMasterPort.hpp
                        protocol/IOLMasterPort.cpp
                        protocol/IOLGenericDevice.hpp
                        protocol/IOLGenericDevice.cpp
                        protocol/HardwareBase.hpp
                        protocol/IOLink.hpp
                        protocol/HardwareBase.cpp)

# Check hardwarespecific Files
if(${CMAKE_SYSTEM_NAME} STREQUAL "Arduino")
    add_library(arduionohw  
                            board/Max14819.hpp
                            board/Max14819.cpp
                            board/HardwareArduino.hpp
                            board/HardwareArduino.cpp)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "arm")
        add_library(raspberrypihw
                                board/Max14819.hpp
                                board/Max14819.cpp
                                board/HardwareRaspberry.hpp
                                board/HardwareRaspberry.cpp)
        target_link_libraries(openiolink raspberrypihw)
        target_link_libraries(raspberrypihw openiolink)
        find_library(WIRINGPI_LIB wiringPi REQUIRED) # TODO clean-up
        target_link_libraries(openiolink ${WIRINGPI_LIB})
        target_link_libraries(openiolink pthread rt) # TODO clean-up
    else()
        add_library(dummyhw board/HardwareDummy.hpp
                            board/HardwareDummy.cpp
                            board/HardwareDummyChip.hpp
                            board/HardwareDummyChip.cpp)
        target_link_libraries(openiolink dummyhw)
        target_link_libraries(dummyhw openiolink)
    endif()
                            
endif()

set_target_properties(openiolink PROPERTIES CXX_STANDARD_REQUIRED 11 CXX_STANDARD 14)
target_include_directories(openiolink PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})