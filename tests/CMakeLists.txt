file(GLOB_RECURSE test_list "*_test.cpp")
file(GLOB_RECURSE src_list "../src/feedback-ingest/*.cpp")
add_executable(feedback_ingest_test ${src_list} ${test_list} main.cpp)
target_include_directories(feedback_ingest_test PRIVATE ../include)
target_link_libraries(feedback_ingest_test PRIVATE
  project_options
  project_warnings
  doctest::doctest
  nlohmann_json::nlohmann_json
  boost::boost
)
