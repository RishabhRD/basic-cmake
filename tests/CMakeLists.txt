file(GLOB_RECURSE test_list "*_test.cpp")
file(GLOB_RECURSE src_list "../src/monkey/*.cpp")
add_executable(monkeyshell_tests ${src_list} ${test_list} main.cpp)
target_link_libraries(monkeyshell_tests PRIVATE
  project_options
  project_warnings
  doctest::doctest
)
