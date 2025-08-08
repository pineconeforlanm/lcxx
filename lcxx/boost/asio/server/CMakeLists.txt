project(asio_server VERSION ${CMAKE_PROJECT_VERSION} DESCRIPTION "asio server example" LANGUAGES CXX)

set(SYNC_SERVER_NAME sync_server)

set(SYNC_SERVER_SRC sync_server.cc)

add_executable(${SYNC_SERVER_NAME} ${SYNC_SERVER_SRC})

target_include_directories(
        ${SYNC_SERVER_NAME}
        PUBLIC
        ${CMAKE_SOURCE_DIR}/lcxx/boost/utils
)

target_link_libraries(${SYNC_SERVER_NAME} lcxx_utils stdc++exp boost::boost)

target_compile_definitions(
        ${SYNC_SERVER_NAME}
        PUBLIC
        SYNC_SERVER_VERSION="${CMAKE_PROJECT_VERSION}"
        SYNC_SERVER_VERSION_MAJOR=${CMAKE_PROJECT_VERSION_MAJOR}
        SYNC_SERVER_VERSION_MINOR=${CMAKE_PROJECT_VERSION_MINOR}
        SYNC_SERVER_VERSION_PATCH=${CMAKE_PROJECT_VERSION_PATCH}
        SYNC_SERVER_VERSION_TWEAK=${CMAKE_PROJECT_VERSION_TWEAK}
)