project(lcxx_utils VERSION ${CMAKE_PROJECT_VERSION} DESCRIPTION "lcxx utils" LANGUAGES CXX)

set(LCXX_BASE_NAME lcxx_base)
set(LCXX_UTILS_NAME lcxx_utils)

file(GLOB_RECURSE LCXX_UTILS_SRC "./*.cc")

add_library(${LCXX_UTILS_NAME} SHARED)

target_sources(
        ${LCXX_UTILS_NAME}
        PRIVATE
        ${LCXX_UTILS_SRC}
)

target_include_directories(
        ${LCXX_UTILS_NAME}
        PUBLIC
        "${CMAKE_SOURCE_DIR}/lcxx/boost"
)

target_link_libraries(${LCXX_UTILS_NAME} PUBLIC stdc++exp boost::boost)

target_compile_definitions(
        ${LCXX_UTILS_NAME}
        PRIVATE
        LCXX_UTILS_VERSION="${CMAKE_PROJECT_VERSION}"
        LCXX_UTILS_VERSION_MAJOR=${CMAKE_PROJECT_VERSION_MAJOR}
        LCXX_UTILS_VERSION_MINOR=${CMAKE_PROJECT_VERSION_MINOR}
        LCXX_UTILS_VERSION_PATCH=${CMAKE_PROJECT_VERSION_PATCH}
        LCXX_UTILS_VERSION_TWEAK=${CMAKE_PROJECT_VERSION_TWEAK}
)
