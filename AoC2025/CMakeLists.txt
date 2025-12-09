# CMakeList.txt : CMake project for AoC2021, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (AoC2025 "AoC2025.cpp" "AoC2025.h"
    "../Shared/Year/Year.h" "../Shared/Day/Day.h" "../Shared/Day/DayResult.h"
    "../Helpers/Helpers.cpp" "../Helpers/Helpers.h"
    "Day01/Day01.cpp" "Day01/Day01.h"
    "Day02/Day02.cpp" "Day02/Day02.h" 
    "Day03/Day03.cpp" "Day03/Day03.h" 
    "Day04/Day04.cpp" "Day04/Day04.h"   
    "Day05/Day05.cpp" "Day05/Day05.h"   
    "Day06/Day06.cpp" "Day06/Day06.h"   
    "Day07/Day07.cpp" "Day07/Day07.h"
    "Day08/Day08.cpp" "Day08/Day08.h")

set_property(TARGET AoC2025 PROPERTY CXX_STANDARD 20)
set_property(TARGET AoC2025 PROPERTY CXX_STANDARD_REQUIRED ON)

# TODO: Add tests and install targets if needed.

configure_file("Day01/Day01.txt" "./2025/Day01.txt" COPYONLY)
configure_file("Day02/Day02.txt" "./2025/Day02.txt" COPYONLY)
configure_file("Day03/Day03.txt" "./2025/Day03.txt" COPYONLY)
configure_file("Day04/Day04.txt" "./2025/Day04.txt" COPYONLY)
configure_file("Day05/Day05.txt" "./2025/Day05.txt" COPYONLY)
configure_file("Day06/Day06.txt" "./2025/Day06.txt" COPYONLY)
configure_file("Day07/Day07.txt" "./2025/Day07.txt" COPYONLY)
configure_file("Day08/Day08.txt" "./2025/Day08.txt" COPYONLY)