//
// Created by lanm on 2025/8/6.
//
#include <cstdlib>
import lcxx.utils;
import std;

namespace {

auto exp_import_std_main(int argc, char** argv) -> int {
  try {
    std::println("this is exp_import_std_main, argc: {}, argv[0]: {}", argc, argv[0]);

    std::println("lcxx.utils version: {}", lcxx::utils::version());

    std::println("boost version: {}", lcxx::utils::boost::lib_version());

  } catch (std::exception& exp) {
    std::cerr << "Main Exception:" << exp.what() << '\n';
  }
  return EXIT_SUCCESS;
}

auto real_main(const int argc, char** argv) -> int {
  try {
    return exp_import_std_main(argc, argv);
  } catch (const std::exception& exp) {
    std::cerr << exp.what() << '\n';
  }
  return 0;
}
}  // namespace
auto main(const int argc, char** argv) -> int { return real_main(argc, argv); }