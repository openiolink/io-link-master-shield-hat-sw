# only for cmake --version >= 3.5.1
cmake_minimum_required(VERSION 3.5.1)

# creates the variable EXEC and sets it to hello
set(EXEC Demonstrator_v1_0)

# project name
project(${EXEC})

# set the C++14 standard
set(CMAKE_CXX_STANDARD 14)

#  include headers
file(GLOB headers "src/*.h")

# puts all .cpp files inside src to the SOURCES variable
file(GLOB sources src/*.cpp)

# exclude HardwareArduino.cpp
list(FILTER headers EXCLUDE REGEX ".*HardwareArduino.h$")
list(FILTER sources EXCLUDE REGEX ".*HardwareArduino.cpp$")

# compiles the files defined by SOURCES to generante the executable defined by EXEC
add_executable(${EXEC} ${sources} ${headers})

# add Library to Link
target_link_libraries(${EXEC} wiringPi)


