add_library(openiolink  OpenIOLink.hpp
                        board/IOLMasterPortMax14819.hpp
                        board/IOLMasterPortMax14819.cpp
                        board/Max14819.hpp
                        board/Max14819.cpp
                        $<$<PLATFORM_ID:Arduino>:board/HardwareArduino.hpp board/HardwareArduino.cpp>
                        $<$<PLATFORM_ID:Linux>:board/HardwareRaspberry.hpp board/HardwareRaspberry.cpp>
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

set_target_properties(openiolink PROPERTIES CXX_STANDARD_REQUIRED 11 CXX_STANDARD 14)
target_include_directories(openiolink PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
    find_library(WIRINGPI_LIB wiringPi REQUIRED) # TODO clean-up
    target_link_libraries(openiolink ${WIRINGPI_LIB})
    target_link_libraries(openiolink pthread rt) # TODO clean-up
endif()