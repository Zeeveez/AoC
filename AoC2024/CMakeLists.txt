# CMakeList.txt : CMake project for AoC2021, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (AoC2024 "AoC2024.cpp" "AoC2024.h"
    "../Shared/Year/Year.h" "../Shared/Day/Day.h" "../Shared/Day/DayResult.h"
    "../Helpers/Helpers.cpp" "../Helpers/Helpers.h"
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
    "Day24/Day24.cpp" "Day24/Day24.h" 
    "Day25/Day25.cpp" "Day25/Day25.h"  )

set_property(TARGET AoC2024 PROPERTY CXX_STANDARD 23)
set_property(TARGET AoC2024 PROPERTY CXX_STANDARD_REQUIRED ON)

# TODO: Add tests and install targets if needed.

configure_file("Day01/Day01.txt" "./2024/Day01.txt" COPYONLY)
configure_file("Day02/Day02.txt" "./2024/Day02.txt" COPYONLY)
configure_file("Day03/Day03.txt" "./2024/Day03.txt" COPYONLY)
configure_file("Day04/Day04.txt" "./2024/Day04.txt" COPYONLY)
configure_file("Day05/Day05.txt" "./2024/Day05.txt" COPYONLY)
configure_file("Day06/Day06.txt" "./2024/Day06.txt" COPYONLY)
configure_file("Day07/Day07.txt" "./2024/Day07.txt" COPYONLY)
configure_file("Day08/Day08.txt" "./2024/Day08.txt" COPYONLY)
configure_file("Day09/Day09.txt" "./2024/Day09.txt" COPYONLY)
configure_file("Day10/Day10.txt" "./2024/Day10.txt" COPYONLY)
configure_file("Day11/Day11.txt" "./2024/Day11.txt" COPYONLY)
configure_file("Day12/Day12.txt" "./2024/Day12.txt" COPYONLY)
configure_file("Day13/Day13.txt" "./2024/Day13.txt" COPYONLY)
configure_file("Day14/Day14.txt" "./2024/Day14.txt" COPYONLY)
configure_file("Day15/Day15.txt" "./2024/Day15.txt" COPYONLY)
configure_file("Day16/Day16.txt" "./2024/Day16.txt" COPYONLY)
configure_file("Day17/Day17.txt" "./2024/Day17.txt" COPYONLY)
configure_file("Day18/Day18.txt" "./2024/Day18.txt" COPYONLY)
configure_file("Day19/Day19.txt" "./2024/Day19.txt" COPYONLY)
configure_file("Day20/Day20.txt" "./2024/Day20.txt" COPYONLY)
configure_file("Day21/Day21.txt" "./2024/Day21.txt" COPYONLY)
configure_file("Day22/Day22.txt" "./2024/Day22.txt" COPYONLY)
configure_file("Day23/Day23.txt" "./2024/Day23.txt" COPYONLY)
configure_file("Day24/Day24.txt" "./2024/Day24.txt" COPYONLY)
configure_file("Day25/Day25.txt" "./2024/Day25.txt" COPYONLY)