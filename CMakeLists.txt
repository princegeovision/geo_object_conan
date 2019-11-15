cmake_minimum_required(VERSION 3.11...3.15)

# new cmake command not support in conan
#project(geo_object VERSION 1.1 LANGUAGES C CXX)
project(geo_object)

# Step00: 
# Setup Conan in CMake
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Step01:
# Set a output name of library
set(GEOOBJECT_OUTPUT_NAME "geo_object")

# Step02: Source code
# The compiled library code is here
add_subdirectory(src)

# Step03: New Test way (Catch2)
add_subdirectory(test_package)

# Step02: old way , Make a Library
#add_library(${GEOOBJECT_OUTPUT_NAME} STATIC geo_object.c geo_object.h)

# Make a  public header include (mov into src)
#target_include_directories(${GEOOBJECT_OUTPUT_NAME} PUBLIC include)

# Step03:
# Make a EXE to test in Development
#add_executable(test_geo_object catch.hpp test_main.cpp)
#target_link_libraries(test_geo_object ${GEOOBJECT_OUTPUT_NAME})
