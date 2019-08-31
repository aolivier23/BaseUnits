add_executable(test_units test_units.cpp)
target_link_libraries(test_units)
install(TARGETS test_units DESTINATION bin)

#TODO: Add a test comparing the output of test_units to reference file.
