//
// Created by lanm on 2025/8/6.
//
#include <cstdlib>
import lcxx.utils;
import std;

namespace {
auto sync_server_main() -> int {
  std::println("Hello, sync server {{ version : {} }}...", SYNC_SERVER_VERSION);
  std::println("use lcxx utils version: {}", lcxx::utils::version());
  std::println("use boost version: {}", lcxx::utils::boost::lib_version());
  return 0;
}

auto real_main() -> int { return sync_server_main(); }
}  // namespace

auto main() -> int {
  try {
    [[maybe_unused]] auto result = real_main();
  } catch (const std::exception& exp) {
    std::cerr << "Main Exception:" << exp.what() << '\n';
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}