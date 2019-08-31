#Install test executables
add_executable(arithmetic arithmetic.cpp)
target_link_libraries(arithmetic)
install(TARGETS arithmetic DESTINATION bin)

#Install reference results
add_subdirectory(reference)

#Add tests to CTest's implicitly generated testing framework
add_test(NAME test_arithmetic COMMAND ${CMAKE_INSTALL_PREFIX}/bin/arithmetic)
set_tests_properties(test_arithmetic PROPERTIES PASS_REGULAR_EXPRESSION "${test_arithmetic_reference}")
add_test(NAME test_assertCompatibleUnits COMMAND ${CMAKE_CXX_COMPILER} -I${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/assertCompatibleUnits.cpp)
set_tests_properties(test_assertCompatibleUnits PROPERTIES WILL_FAIL TRUE)
