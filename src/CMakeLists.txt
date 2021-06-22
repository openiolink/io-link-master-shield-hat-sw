
add_library(openiolink  OpenIOLink.hpp
                        protocol/IOLinkConfig.hpp
                        protocol/IOLMessage.hpp
                        protocol/IOLMessage.cpp
                        protocol/IOLMasterPort.hpp
                        protocol/IOLMasterPort.cpp
                        protocol/IOLGenericDevice.hpp
                        protocol/IOLGenericDevice.cpp
                        board/MapperIOLPort.hpp)
                        #FIXME: Which files exactly have to be added here?

# Check hardwarespecific Files
if(${CMAKE_SYSTEM_NAME} STREQUAL "Arduino")
    add_library(arduionohw  #FIXME typo!
                            board/Max14819.hpp
                            board/Max14819.cpp
                            board/arduino/HardwareArduino.hpp
                            board/arduino/HardwareArduino.cpp
                            #TODO complete or change
                            #board/arduino/MapperChip_Arduino.hpp
                            #board/arduino/MapperIOLPort_Arduino.hpp
                            #board/arduino/Pin_Arduino.hpp
                            #board/arduino/Pin_Arduino.cpp
                            #board/PrintAndWait.hpp
                            #board/arduino/PrintAndWait.cpp
                            #board/arduino/SpiArduino.hpp
                            #board/arduino/SpiArduino.cpp
                            )
    target_link_arduino_libraries(arduionohw PRIVATE SPI core)
    target_link_libraries(arduionohw PRIVATE openiolink)
    target_link_libraries(openiolink arduionohw)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
        add_library(raspberrypihw
                                board/Max14819.hpp
                                board/Max14819.cpp
                                board/raspberry/HardwareRaspberry.hpp
                                board/raspberry/HardwareRaspberry.cpp
                                board/raspberry/MapperChip_Raspberry.hpp
                                board/raspberry/MapperIOLPort_Raspberry.hpp
                                board/raspberry/Pin_Raspberry.hpp
                                board/raspberry/Pin_Raspberry.cpp
                                board/PrintAndWait.hpp
                                board/raspberry/PrintAndWait.cpp
                                board/raspberry/SpiRaspberry.hpp
                                board/raspberry/SpiRaspberry.cpp
                                )
        target_link_libraries(openiolink raspberrypihw)
        target_link_libraries(raspberrypihw openiolink)
        find_library(WIRINGPI_LIB wiringPi REQUIRED) # TODO clean-up
        target_link_libraries(openiolink ${WIRINGPI_LIB})
        target_link_libraries(openiolink pthread rt) # TODO clean-up
    else()
        add_library(dummyhw board/dummy/HardwareDummy.hpp
                            board/dummy/HardwareDummy.cpp
                            board/dummy/HardwareDummyChip.hpp
                            board/dummy/HardwareDummyChip.cpp)
        target_link_libraries(openiolink dummyhw)
        target_link_libraries(dummyhw openiolink)
    endif()
                            
endif()

set_target_properties(openiolink PROPERTIES CXX_STANDARD_REQUIRED 11 CXX_STANDARD 14)
target_include_directories(openiolink PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})