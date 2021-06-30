# configure_file(OpenIOLinkConfig.h.in OpenIOLinkConfig.h) # TODO to configure the library from CMake, not directly in the source code

# library openiolink
add_library(openiolink  OpenIOLink.hpp
                        protocol/IOLinkConfig.hpp
                        protocol/IOLMessage.hpp
                        protocol/IOLMessage.cpp
                        protocol/IOLMasterPort.hpp
                        protocol/IOLMasterPort.cpp
                        protocol/IOLGenericDevice.hpp
                        protocol/IOLGenericDevice.cpp
                        board/MapperIOLPort.hpp
                        #board/OpeniolinkShieldHat.hpp
                        #board/OpeniolinkShieldHat.cpp
                        )
                        #FIXME: Which files exactly have to be added here?

# hardware-dependent library (arduinohw / raspberrypihw / dummyhw)
# Check hardwarespecific Files
if(${CMAKE_SYSTEM_NAME} STREQUAL "Arduino")
# (1) platform Arduino
    add_library(arduionohw  #FIXME typo!
                            board/Max14819.hpp
                            #board/Max14819.cpp # .cpp from class templates are included by their .hpp and should therefore not be compiled independently.
                            #board/arduino/HardwareArduino.hpp
                            #board/arduino/HardwareArduino.cpp
                            #TODO complete or change
                            board/arduino/MapperChip_Arduino.hpp
                            board/arduino/MapperIOLPort_Arduino.hpp
                            board/arduino/Pin_Arduino.hpp
                            #board/arduino/Pin_Arduino.cpp
                            board/PrintAndWait.hpp
                            board/arduino/PrintAndWait_Arduino.cpp
                            board/arduino/Spi_Arduino.hpp
                            #board/arduino/Spi_Arduino.cpp
                            )
    target_link_arduino_libraries(arduionohw PRIVATE SPI core)
    target_link_libraries(arduionohw PRIVATE openiolink)
    target_link_libraries(openiolink arduionohw)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
    # (2) platform Raspberry
    add_compile_definitions(RASPBERRY) #for platform specific header inclusion control
        add_library(raspberrypihw
                                board/Max14819.hpp
                                #board/Max14819.cpp
                                #board/raspberry/HardwareRaspberry.hpp
                                #board/raspberry/HardwareRaspberry.cpp
                                board/raspberry/MapperChip_Raspberry.hpp
                                board/raspberry/MapperIOLPort_Raspberry.hpp
                                board/raspberry/Pin_Raspberry.hpp
                                #board/raspberry/Pin_Raspberry.cpp
                                board/PrintAndWait.hpp
                                board/raspberry/PrintAndWait_Raspberry.cpp
                                board/raspberry/Spi_Raspberry.hpp
                                #board/raspberry/Spi_Raspberry.cpp
                                )
        target_link_libraries(openiolink raspberrypihw)
        target_link_libraries(raspberrypihw openiolink)
        find_library(WIRINGPI_LIB wiringPi REQUIRED) # TODO clean-up
        target_link_libraries(openiolink ${WIRINGPI_LIB})
        target_link_libraries(openiolink pthread rt) # TODO clean-up
    else()
    # (3) no platform (linux)
        add_library(dummyhw board/HardwareDummy.hpp
                            board/HardwareDummy.cpp
                            board/HardwareDummyChip.hpp
                            board/HardwareDummyChip.cpp)
        target_link_libraries(openiolink dummyhw)
        target_link_libraries(dummyhw openiolink)
    endif()
                            
endif()

# properties for the library openiolink
set_target_properties(openiolink
    PROPERTIES
        CXX_STANDARD_REQUIRED ON
        CXX_STANDARD 17  # mindestens 17 nötig für static constexpr member
)

# Define incluce directories
target_include_directories(openiolink
    # TODO use  $<INSTALL_INTERFACE:...> and $<BUILD_INTERFACE:...> generator expressions to distinguish between building and installing the library
    PUBLIC              # means "INTERFACE" and "PRIVATE"
        ${CMAKE_CURRENT_SOURCE_DIR}
    # TODO INTERFACE    everything that only the user of the library needs
    # TODO PRIVATE      everything that's only needed to build the library
)
