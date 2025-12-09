# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("AoC")

# Include sub-projects.
add_subdirectory ("AoC2015")
add_subdirectory ("AoC2019")
add_subdirectory ("AoC2021")
add_subdirectory ("AoC2022")
add_subdirectory ("AoC2023")
add_subdirectory ("AoC2024")
add_subdirectory ("AoC2025")