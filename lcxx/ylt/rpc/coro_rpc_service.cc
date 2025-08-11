//
// Created by lanm on 2025/8/11.
//

#include <cstdlib>
#include <ylt/coro_rpc/coro_rpc_server.hpp>
#include <ylt/easylog.hpp>
import lcxx.base.utils;
import std;

namespace {

auto rpc_service_main([[maybe_unused]] const int argc, [[maybe_unused]] const char** argv) -> int {
  lcxx::base::utils::log::init();

  auto rpc_service = coro_rpc::coro_rpc_server{/*thread=*/std::thread::hardware_concurrency(),
                                         /*port=*/8801};

  rpc_service.register_handler<lcxx::base::utils::rpc::echo>();
  [[maybe_unused]] const auto res = rpc_service.start();
  return EXIT_SUCCESS;
}

auto real_main(const int argc, const char** argv) -> int {
  try {
    rpc_service_main(argc, argv);
  } catch (std::exception& exp) {
    std::cerr << "Main Exception:" << exp.what() << '\n';
  }
  return EXIT_SUCCESS;
}
}

auto main(const int argc, const char** argv) -> int {
  return real_main(argc, argv);
}


