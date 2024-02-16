cmake_minimum_required(VERSION 3.12)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set compiler flags for debug build
add_compile_options(-g -Wall)

project(hw2 CXX)

# Set the C++ standard version (optional but recommended)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.8
)
FetchContent_MakeAvailable(Catch2)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Create the executable from the source file
add_executable(main main.cpp hockey_stats.cpp)
add_executable(test test.cpp hockey_stats.cpp)

target_link_libraries(test PRIVATE Catch2::Catch2)
# target_link_libraries(main Boost::Boost)
