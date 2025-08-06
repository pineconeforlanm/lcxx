
set(SYNC_CLIENT_SRC sync_client.cc)

add_executable(sync_client ${SYNC_CLIENT_SRC})

target_link_libraries(sync_client boost::boost)