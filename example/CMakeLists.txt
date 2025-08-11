find_package(Boost REQUIRED)
find_package(yaml-cpp REQUIRED)

add_executable(exp_import_std exp_import_std.cc)

target_include_directories(exp_import_std PRIVATE ${CMAKE_SOURCE_DIR}/lcxx/boost/asio/utils)

target_link_libraries(exp_import_std PUBLIC stdc++exp yaml-cpp::yaml-cpp boost::boost lcxx_base)