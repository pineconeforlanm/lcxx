cmake_minimum_required(VERSION 4.1.0)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(lcxx VERSION 0.1.0.0 DESCRIPTION "learn cxx" LANGUAGES CXX C)

add_subdirectory(example)
add_subdirectory(lcxx)
add_subdirectory(test)
