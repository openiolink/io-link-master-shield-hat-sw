cmake_minimum_required(VERSION 3.12) # version 3.12 is required for add_compile_definitions()
#cmake_minimum_required(VERSION 3.5) # with this version you have to use add_definitions() instead of add_compile_definitions()
project(openiolink
    VERSION 0.0.1
    LANGUAGES CXX)

include(GNUInstallDirs)

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(test)
