//
// Created by lanm on 2025/8/6.
//
#include <cstdlib>
import std;

namespace {
auto sync_client_main() -> int {
  std::println("Hello, sync client {{ version : {} }}...", SYNC_CLIENT_VERSION);
  return 0;
}

auto real_main() -> int { return sync_client_main(); }
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