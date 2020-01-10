cmake_minimum_required( VERSION 2.8.12 )
project( BaseUnits )

include(CTest)
include(CMakePackageConfigHelpers)

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

#Make this package findable CMake for other package
write_basic_package_version_file(BaseUnitsConfigVersion.cmake
                                 COMPATIBILITY SameMajorVersion
                                 VERSION 1.0.0)
configure_package_config_file(PackageConfig.cmake.in
                              BaseUnitsConfig.cmake
                              PATH_VARS CMAKE_INSTALL_PREFIX
                              INSTALL_DESTINATION lib/${CMAKE_PROJECT_NAME}/cmake)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/BaseUnitsConfigVersion.cmake ${CMAKE_CURRENT_BINARY_DIR}/BaseUnitsConfig.cmake DESTINATION lib/${CMAKE_PROJECT_NAME}/cmake)
