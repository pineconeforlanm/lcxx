find_package(Boost REQUIRED)
find_package(CLI11 REQUIRED)
find_package(yaml-cpp REQUIRED)

add_executable(cli11 cli11.cc)

target_include_directories(
        cli11
        PUBLIC
        ${CMAKE_SOURCE_DIR}/lcxx/base/utils
)

target_link_libraries(cli11 lcxx_base stdc++exp CLI11::CLI11 boost::boost yaml-cpp::yaml-cpp)