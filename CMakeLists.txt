# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("GuesserGame")

# Include sub-projects.
add_subdirectory ("GuesserGame")

target_compile_features(GuesserGame PRIVATE cxx_std_17)