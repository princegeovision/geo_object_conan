# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${ModernCMakeExample_SOURCE_DIR}/include/modern/*.hpp")
set(HEADER_LIST "..${ModernCMakeExample_SOURCE_DIR}/include/geo_object/geo_object.h")

# Make an automatic library - will be static or dynamic based on user setting
#EX:add_library(modern_library lib.cpp ${HEADER_LIST})
add_library(${GEOOBJECT_OUTPUT_NAME} STATIC geo_object.c ${HEADER_LIST})


# We need this directory, and users of our library will need it too
target_include_directories(${GEOOBJECT_OUTPUT_NAME} PUBLIC ../include/geo_object/)

# All users of this library will need at least C++11
target_compile_features(${GEOOBJECT_OUTPUT_NAME} PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})
