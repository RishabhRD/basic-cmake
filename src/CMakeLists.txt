file(GLOB_RECURSE src_list "**.cpp")
add_executable(monkeyshell ${src_list})
target_include_directories(monkeyshell PRIVATE ../include)
target_link_libraries(monkeyshell PRIVATE project_options project_warnings)
