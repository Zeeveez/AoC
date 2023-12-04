# CMakeList.txt : CMake project for AoC2021, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (AoC2023 "AoC2023.cpp" "AoC2023.h" "../Helpers/Helpers.cpp" "../Helpers/Helpers.h"
    "Day01/Day01.cpp" "Day01/Day01.h"
    "Day02/Day02.cpp" "Day02/Day02.h"
    "Day03/Day03.cpp" "Day03/Day03.h"
    "Day04/Day04.cpp" "Day04/Day04.h")

set_property(TARGET AoC2023 PROPERTY CXX_STANDARD 20)
set_property(TARGET AoC2023 PROPERTY CXX_STANDARD_REQUIRED ON)

# TODO: Add tests and install targets if needed.

configure_file("Day01/Day01.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day02/Day02.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day03/Day03.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day04/Day04.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)