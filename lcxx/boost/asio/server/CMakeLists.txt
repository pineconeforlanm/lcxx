set(SYNC_SERVER_SRC sync_server.cc)

add_executable(sync_server ${SYNC_SERVER_SRC})

target_link_libraries(sync_server boost::boost)