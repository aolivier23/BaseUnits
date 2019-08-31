cmake_minimum_required( VERSION 2.8.12 )
project( BaseUnits )
include(CTest)

#Compiler flags
set( GCC_Flags_For_CXX "-std=c++1y -Wall" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_Flags_For_CXX}" )
set( CMAKE_CXX_FLAGS_DEBUG "-ggdb" )
set( CMAKE_CXX_FLAGS_RELEASE "-O2" )

#TODO: Look for ROOT and add appropriate tests only if found.
#Make sure ROOT is included
#list( APPEND CMAKE_PREFIX_PATH $ENV{ROOT_SYS})
#find_package(ROOT REQUIRED COMPONENTS RIO Net Tree Core Geom EG)
#include(${ROOT_USE_FILE})

#Make sure test can see include files for this library
include_directories("${PROJECT_SOURCE_DIR}")

add_subdirectory(core)
add_subdirectory(test)
