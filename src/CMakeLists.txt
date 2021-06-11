
add_library(openiolink  OpenIOLink.hpp
                        protocol/IOLinkConfig.hpp
                        protocol/IOLMessage.hpp
                        protocol/IOLMessage.cpp
                        protocol/IOLMasterPort.hpp
                        protocol/IOLMasterPort.cpp
                        protocol/IOLGenericDevice.hpp
                        protocol/IOLGenericDevice.cpp
#                        board/SpiArduino.hpp
#                        board/SpiArduino.cpp
#                        board/SpiRaspberry.hpp
#                        board/SpiRaspberry.cpp
                        board/MapperIOLPort.hpp)
                        #FIXME: Which files exactly have to be added here?

# Check hardwarespecific Files
if(${CMAKE_SYSTEM_NAME} STREQUAL "Arduino")
    add_library(arduionohw  
                            board/Max14819.hpp
                            board/Max14819.cpp
                            board/HardwareArduino.hpp
                            board/HardwareArduino.cpp)
    target_link_arduino_libraries(arduionohw PRIVATE SPI core)
    target_link_libraries(arduionohw PRIVATE openiolink)
    target_link_libraries(openiolink arduionohw)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
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

set_target_properties(openiolink PROPERTIES CXX_STANDARD_REQUIRED ON CXX_STANDARD 17) # mindestens 17 nötig für static constexpr member
target_include_directories(openiolink PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})