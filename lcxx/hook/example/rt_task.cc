//
// Created by lanm on 2025/8/11.
//

#include <sinsegye_ari_rt.h>

#include <ylt/easylog.hpp>
import lcxx.base.utils;
namespace {

auto real_rt_main(const int argc, const char** argv) -> int {

  rt::hook_init();
  rt::set_hook_enable(true);

  lcxx::base::utils::log::init();

  rt_create_task(argc, argv);
  rt_delete_task();

  return 0;
}

auto real_main(const int argc, const char** argv) -> int {
  try {
    [[maybe_unused]] auto result = real_rt_main(argc, argv);
  } catch (const std::exception& exp) {
    ELOGE << "rt task exception: " << exp.what();
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

}  // namespace
auto main(const int argc, const char** argv) -> int { return real_main(argc, argv); }