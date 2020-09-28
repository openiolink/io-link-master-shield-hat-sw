# only for cmake --version >= 3.5.1
cmake_minimum_required(VERSION 3.5.1)

# creates the variable EXEC and sets it to hello
set(EXEC Demonstrator_v1_0)

# project name
project(${EXEC})

# set the C++14 standard
set(CMAKE_CXX_STANDARD 14)

# puts all .cpp files inside src to the SOURCES variable
set(SOURCES
    src/BalluffBni0088.cpp
    src/BalluffBus0023.cpp
    examples/Demonstrator_V1_0.cpp
    src/HardwareBase.cpp
    src/HardwareRaspberry.cpp
    src/IOLGenericDevice.cpp
    src/IOLMasterPort.cpp
    src/IOLMasterPortMax14819.cpp
    src/Max14819.cpp
    examples/main.cpp)

find_library(WIRINGPI_LIB wiringPi REQUIRED)

# compiles the files defined by SOURCES to generante the executable defined by EXEC
add_executable(${EXEC} ${SOURCES})
target_include_directories(${EXEC} PRIVATE src)

# add Library to Link
target_link_libraries(${EXEC} ${WIRINGPI_LIB})
target_link_libraries(${EXEC} pthread rt)