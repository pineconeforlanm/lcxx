add_executable(coro_rpc_service coro_rpc_service.cc)

target_link_libraries(coro_rpc_service PUBLIC
        stdc++exp lcxx_base boost::boost
)

add_executable(core_rpc_client core_rpc_client.cc)

target_link_libraries(core_rpc_client PUBLIC
        stdc++exp lcxx_base boost::boost
)