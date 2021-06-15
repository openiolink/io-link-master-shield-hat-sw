cmake_minimum_required(VERSION 3.5)
project(openiolink
    VERSION 0.0.1
    LANGUAGES CXX)

include(GNUInstallDirs)

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(test)
