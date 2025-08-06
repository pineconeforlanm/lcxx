project(lcxx_utils VERSION ${CMAKE_PROJECT_VERSION} DESCRIPTION "lcxx utils" LANGUAGES CXX)

set(LCXX_UTILS_NAME lcxx_utils)

set(LCXX_UTILS_SRC utils.cc)

add_library(${LCXX_UTILS_NAME} SHARED utils.cc)

target_sources(
        ${LCXX_UTILS_NAME}
        PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES
        FILES utils.ccm
)

target_link_libraries(${LCXX_UTILS_NAME} boost::boost)

target_compile_definitions(
        ${LCXX_UTILS_NAME}
        PRIVATE
        LCXX_UTILS_VERSION="${CMAKE_PROJECT_VERSION}"
        LCXX_UTILS_VERSION_MAJOR=${CMAKE_PROJECT_VERSION_MAJOR}
        LCXX_UTILS_VERSION_MINOR=${CMAKE_PROJECT_VERSION_MINOR}
        LCXX_UTILS_VERSION_PATCH=${CMAKE_PROJECT_VERSION_PATCH}
        LCXX_UTILS_VERSION_TWEAK=${CMAKE_PROJECT_VERSION_TWEAK}
)