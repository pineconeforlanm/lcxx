find_package(Boost REQUIRED)
find_package(yaml-cpp REQUIRED)

project(lcxx_base VERSION ${CMAKE_PROJECT_VERSION} DESCRIPTION "lcxx base" LANGUAGES CXX)

set(LCXX_BASE_NAME lcxx_base)

file(GLOB_RECURSE LCXX_BASE_SRC "./utils/*.cc" "./config/*.cc")

add_library(${LCXX_BASE_NAME} SHARED)

set_target_properties(${LCXX_BASE_NAME} PROPERTIES
        VERSION ${CMAKE_PROJECT_VERSION}
        SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
        OUTPUT_NAME lcxx_base
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
)

target_sources(${LCXX_BASE_NAME} PRIVATE ${LCXX_BASE_SRC})

file(GLOB_RECURSE LCXX_BASE_MODULE_SRC "./utils/*.ccm" "./config/*.ccm")

target_sources(
        ${LCXX_BASE_NAME} PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES
        FILES ${LCXX_BASE_MODULE_SRC}
)

target_link_libraries(${LCXX_BASE_NAME} PUBLIC stdc++exp yaml-cpp::yaml-cpp boost::boost)

target_compile_definitions(
        ${LCXX_BASE_NAME}
        PRIVATE
        LCXX_UTILS_VERSION="${CMAKE_PROJECT_VERSION}"
        LCXX_UTILS_VERSION_MAJOR=${CMAKE_PROJECT_VERSION_MAJOR}
        LCXX_UTILS_VERSION_MINOR=${CMAKE_PROJECT_VERSION_MINOR}
        LCXX_UTILS_VERSION_PATCH=${CMAKE_PROJECT_VERSION_PATCH}
        LCXX_UTILS_VERSION_TWEAK=${CMAKE_PROJECT_VERSION_TWEAK}
)