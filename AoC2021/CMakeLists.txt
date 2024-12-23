# CMakeList.txt : CMake project for AoC2021, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (AoC2021 "AoC2021.cpp" "AoC2021.h" "../Helpers/Helpers.cpp" "../Helpers/Helpers.h"
    "../AoC/Day/Day.cpp" "../AoC/Day/Day.h"
    "Day01/Day01.cpp" "Day01/Day01.h"
    "Day02/Day02.cpp" "Day02/Day02.h"
    "Day03/Day03.cpp" "Day03/Day03.h"
    "Day04/Day04.cpp" "Day04/Day04.h"
    "Day05/Day05.cpp" "Day05/Day05.h"
    "Day06/Day06.cpp" "Day06/Day06.h"
    "Day07/Day07.cpp" "Day07/Day07.h"
    "Day08/Day08.cpp" "Day08/Day08.h"
    "Day09/Day09.cpp" "Day09/Day09.h"
    "Day10/Day10.cpp" "Day10/Day10.h"
    "Day11/Day11.cpp" "Day11/Day11.h"
    "Day12/Day12.cpp" "Day12/Day12.h"
    "Day13/Day13.cpp" "Day13/Day13.h"
    "Day14/Day14.cpp" "Day14/Day14.h"
    "Day15/Day15.cpp" "Day15/Day15.h"
    "Day16/Day16.cpp" "Day16/Day16.h"
    "Day17/Day17.cpp" "Day17/Day17.h"
    "Day18/Day18.cpp" "Day18/Day18.h"
    "Day19/Day19.cpp" "Day19/Day19.h"
    "Day20/Day20.cpp" "Day20/Day20.h"
    "Day21/Day21.cpp" "Day21/Day21.h"
    "Day22/Day22.cpp" "Day22/Day22.h"
    "Day23/Day23.cpp" "Day23/Day23.h"
    "Day25/Day25.cpp" "Day25/Day25.h")

set_property(TARGET AoC2021 PROPERTY CXX_STANDARD 20)
set_property(TARGET AoC2021 PROPERTY CXX_STANDARD_REQUIRED ON)

# TODO: Add tests and install targets if needed.

configure_file("Day01/Day01.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day02/Day02.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day03/Day03.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day04/Day04.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day05/Day05.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day06/Day06.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day07/Day07.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day08/Day08.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day09/Day09.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day10/Day10.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day11/Day11.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day12/Day12.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day13/Day13.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day14/Day14.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day15/Day15.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day16/Day16.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day17/Day17.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day18/Day18.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day19/Day19.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day20/Day20.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day21/Day21.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day22/Day22.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day23/Day23.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Day25/Day25.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)