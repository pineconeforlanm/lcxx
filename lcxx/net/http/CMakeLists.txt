find_package(Boost REQUIRED)

project(coro_http VERSION ${CMAKE_PROJECT_VERSION} DESCRIPTION "asio server example" LANGUAGES CXX)

set(CORO_SERVER_NAME coro_http_server)

set(CORO_SERVER_SRC coro_http.cc)

add_executable(${CORO_SERVER_NAME} ${CORO_SERVER_SRC})

target_include_directories(
        ${CORO_SERVER_NAME}
        PUBLIC
        ${CMAKE_SOURCE_DIR}/lcxx/base/utils
)

target_link_libraries(${CORO_SERVER_NAME} lcxx_base stdc++exp boost::boost)

target_compile_definitions(
        ${CORO_SERVER_NAME}
        PUBLIC
        SYNC_SERVER_VERSION="${CMAKE_PROJECT_VERSION}"
        SYNC_SERVER_VERSION_MAJOR=${CMAKE_PROJECT_VERSION_MAJOR}
        SYNC_SERVER_VERSION_MINOR=${CMAKE_PROJECT_VERSION_MINOR}
        SYNC_SERVER_VERSION_PATCH=${CMAKE_PROJECT_VERSION_PATCH}
        SYNC_SERVER_VERSION_TWEAK=${CMAKE_PROJECT_VERSION_TWEAK}
)