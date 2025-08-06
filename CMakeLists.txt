cmake_minimum_required(VERSION 4.1.0)
cmake_policy(SET CMP0077 NEW)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_MODULE_STD 1)
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE BOOL "No dev warnings")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lcxx VERSION 1.0.0 DESCRIPTION "learn cxx" LANGUAGES CXX C)

add_subdirectory(example)
add_subdirectory(lcxx)
add_subdirectory(test)
