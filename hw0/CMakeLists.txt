cmake_minimum_required(VERSION 3.28)

add_compile_options(-g -Wall -fmodules)

project(hw0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_GENERATOR "Ninja")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

add_library(container)
target_sources(container PUBLIC FILE_SET CXX_MODULES FILES container.cpp)

add_executable(main main.cpp)
target_link_libraries(main container)
