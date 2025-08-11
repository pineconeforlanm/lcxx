cmake_minimum_required(VERSION 4.1.0)

include(cmake/compile_options.cmake)

project(lcxx VERSION 0.1.0.0 DESCRIPTION "learn cxx" LANGUAGES CXX C)

add_subdirectory(example)
add_subdirectory(lcxx)
add_subdirectory(test)
