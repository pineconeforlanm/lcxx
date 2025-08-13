find_package(SqliteOrm REQUIRED)

add_executable(db_sqlite_orm db_sqlite_orm.cc)

target_link_libraries(db_sqlite_orm
    PUBLIC
    lcxx_base
    stdc++exp
    sqlite_orm::sqlite_orm
)