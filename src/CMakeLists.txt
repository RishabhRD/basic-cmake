file(GLOB_RECURSE src_list "**.cpp")
add_executable(feedback_ingest ${src_list})
target_include_directories(feedback_ingest PRIVATE ../include)
target_link_libraries(feedback_ingest PRIVATE
  project_options
  project_warnings
  nlohmann_json::nlohmann_json
  boost::boost
)
