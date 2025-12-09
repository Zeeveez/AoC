# CMakeList.txt : CMake project for AoC2021, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (AoC2019 "AoC2019.cpp" "AoC2019.h"
    "../Shared/Year/Year.h" "../Shared/Day/Day.h" "../Shared/Day/DayResult.h"
    "../Helpers/Helpers.cpp" "../Helpers/Helpers.h"
    "IntCodeCPU/IntCodeCPU.h" "IntCodeCPU/IntCodeCPU.cpp"    
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
    "Day12/Day12.cpp" "Day12/Day12.h" "Day12/Moon/Moon.cpp" "Day12/Moon/Moon.h"
    "Day13/Day13.cpp" "Day13/Day13.h"
    "Day14/Day14.cpp" "Day14/Day14.h"
    "Day15/Day15.cpp" "Day15/Day15.h"
    "Day16/Day16.cpp" "Day16/Day16.h"
    "Day17/Day17.cpp" "Day17/Day17.h")

set_property(TARGET AoC2019 PROPERTY CXX_STANDARD 20)
set_property(TARGET AoC2019 PROPERTY CXX_STANDARD_REQUIRED ON)

# TODO: Add tests and install targets if needed.

configure_file("Day01/Day01.txt" "./2019/Day01.txt" COPYONLY)
configure_file("Day02/Day02.txt" "./2019/Day02.txt" COPYONLY)
configure_file("Day03/Day03.txt" "./2019/Day03.txt" COPYONLY)
configure_file("Day04/Day04.txt" "./2019/Day04.txt" COPYONLY)
configure_file("Day05/Day05.txt" "./2019/Day05.txt" COPYONLY)
configure_file("Day06/Day06.txt" "./2019/Day06.txt" COPYONLY)
configure_file("Day07/Day07.txt" "./2019/Day07.txt" COPYONLY)
configure_file("Day08/Day08.txt" "./2019/Day08.txt" COPYONLY)
configure_file("Day09/Day09.txt" "./2019/Day09.txt" COPYONLY)
configure_file("Day10/Day10.txt" "./2019/Day10.txt" COPYONLY)
configure_file("Day11/Day11.txt" "./2019/Day11.txt" COPYONLY)
configure_file("Day12/Day12.txt" "./2019/Day12.txt" COPYONLY)
configure_file("Day13/Day13.txt" "./2019/Day13.txt" COPYONLY)
configure_file("Day14/Day14.txt" "./2019/Day14.txt" COPYONLY)
configure_file("Day15/Day15.txt" "./2019/Day15.txt" COPYONLY)
configure_file("Day16/Day16.txt" "./2019/Day16.txt" COPYONLY)
configure_file("Day17/Day17.txt" "./2019/Day17.txt" COPYONLY)