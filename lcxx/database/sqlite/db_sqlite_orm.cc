// // Created by lanm on 2025/8/11.
#include <sqlite_orm/sqlite_orm.h>
#include <ylt/easylog.hpp>

import lcxx.base.utils;
import std;

namespace {

// 定义实体类
struct User {
    int id;
    std::string name;
    int age;
    std::string email;
    bool active;
    time_t created_at;
};

struct Post {
    int id;
    std::string title;
    std::string content;
    int user_id;  // 外键关联User
    time_t created_at;
};

// 初始化数据库连接
auto init_storage(const std::string& db_path) {
    using namespace sqlite_orm;

    return make_storage(db_path,
        make_table("users",
            make_column("id", &User::id, primary_key().autoincrement()),
            make_column("name", &User::name, not_null()),
            make_column("age", &User::age, check(c(&User::age) > 0 && c(&User::age) < 150)),
            make_column("email", &User::email, unique(), not_null()),
            make_column("active", &User::active, default_value(true)),
            make_column("created_at", &User::created_at, default_value(std::time(nullptr)))
        ),
        make_table("posts",
            make_column("id", &Post::id, primary_key().autoincrement()),
            make_column("title", &Post::title, not_null()),
            make_column("content", &Post::content),
            make_column("user_id", &Post::user_id, not_null(),
                       foreign_key(&Post::user_id).references(&User::id)),
            make_column("created_at", &Post::created_at, default_value(std::time(nullptr))),
            // 创建索引
            make_index("idx_posts_user_id", &Post::user_id)
        )
    );
}

using Storage = decltype(init_storage(""));

// 高级CRUD操作示例
void advanced_operations(Storage& storage) {
    // 1. 批量插入
    std::vector<User> users = {
        {0, "Alice", 28, "alice@example.com", true, 0},
        {0, "Bob", 32, "bob@example.com", true, 0},
        {0, "Charlie", 45, "charlie@example.com", false, 0}
    };
    auto user_ids = storage.insert_range(users.begin(), users.end());
    std::cout << "插入了 " << user_ids.size() << " 个用户" << std::endl;

    // 2. 条件查询 - WHERE子句
    auto adults = storage.get_all<User>(sqlite_orm::where(sqlite_orm::c(&User::age) >= 30 && sqlite_orm::c(&User::active)));
    std::cout << "30岁以上的活跃用户: " << adults.size() << std::endl;

    // 3. 排序和限制结果
    auto sorted_by_age = storage.get_all<User>(sqlite_orm::where(sqlite_orm::c(&User::active)), sqlite_orm::order_by(&User::age).desc(), sqlite_orm::limit(2)
    );
    std::cout << "按年龄降序的前2个活跃用户: " << std::endl;
    for (const auto& u : sorted_by_age) {
        std::cout << "  " << u.name << " (" << u.age << "岁)" << std::endl;
    }

    // 4. 更新部分字段
    storage.update_all(sqlite_orm::set(sqlite_orm::c(&User::active) = true), sqlite_orm::where(sqlite_orm::c(&User::name) == "Charlie")
    );

    // 5. 聚合查询
    auto avg_age = storage.select(sqlite_orm::avg(&User::age));
    auto max_age = storage.select(sqlite_orm::max(&User::age));
    std::cout << "平均年龄: " << avg_age << ", 最大年龄: " << max_age << std::endl;

    // 6. 插入关联数据
    std::vector<Post> posts = {
        {0, "Hello World", "First post", user_ids[0], 0},
        {0, "SQLite ORM", "ORM is great", user_ids[0], 0},
        {0, "C++ Tips", "Modern C++ features", user_ids[1], 0}
    };
    storage.insert_range(posts.begin(), posts.end());

    // 7. 联表查询 (JOIN)
    auto user_posts = storage.select(sqlite_orm::columns(&User::name, &Post::title),
        sqlite_orm::inner_join<Post>(sqlite_orm::on(sqlite_orm::c(&Post::user_id) == sqlite_orm::c(&User::id))),
        sqlite_orm::where(sqlite_orm::c(&User::id) == user_ids[0])
    );
    std::cout << "Alice的帖子: " << std::endl;
    for (const auto& up : user_posts) {
        std::string name;
        std::string title;
        std::tie(name, title) = up;
        std::cout << "  " << title << std::endl;
    }

    // 8. 事务处理
    auto transaction = storage.transaction();
    try {
        // 批量删除
        storage.remove_all<User>(sqlite_orm::where(sqlite_orm::c(&User::age) < 30));

        // 验证删除结果
        auto remaining = storage.count<User>();
        std::cout << "删除后剩余用户: " << remaining << std::endl;

        transaction.commit();  // 提交事务
    } catch (...) {
        transaction.rollback();  // 出错时回滚
        throw;
    }

    // 9. 复杂查询 - 子查询
    auto subquery = storage.select(&Post::user_id, sqlite_orm::where(sqlite_orm::length(&Post::content) > 20));
    auto active_post_authors = storage.get_all<User>(sqlite_orm::where(sqlite_orm::in(&User::id, subquery) && sqlite_orm::c(&User::active))
    );
    std::cout << "发表过长文的活跃用户: " << active_post_authors.size() << std::endl;
}

auto sqlite_orm_main(const int argc, const char** argv) -> int {
  auto storage = init_storage("advanced_example.db");
  storage.sync_schema();  // 创建表结构

  advanced_operations(storage);
  return 0;
}

auto real_main(const int argc, const char** argv) -> int {
  try {
    [[maybe_unused]] auto result = sqlite_orm_main(argc, argv);
  } catch (std::exception& exp) {
    ELOGI << "SQLite ORM exception: " << exp.what();
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
}  // namespace

auto main(const int argc, const char** argv) -> int { return real_main(argc, argv); }