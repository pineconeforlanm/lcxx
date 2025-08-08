find_package(Boost REQUIRED)

add_executable(exp_import_std exp_import_std.cc)

target_include_directories(exp_import_std PRIVATE ${CMAKE_SOURCE_DIR}/lcxx/boost/asio/utils)

target_link_libraries(exp_import_std PUBLIC lcxx_utils boost::boost)