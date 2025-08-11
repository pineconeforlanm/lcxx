//
// Created by lanm on 2025/8/6.
//
#include <boost/asio.hpp>
#include <ylt/easylog.hpp>

import lcxx.base.utils;
import std;

namespace {

auto sync_client_main([[maybe_unused]] const int argc, [[maybe_unused]] char** argv) -> int {
  lcxx::base::utils::log::init();

  constexpr int kMaxBufferSize = 1024;
  auto ioctx = boost::asio::io_context{};
  auto socket = boost::asio::ip::tcp::socket(ioctx);
  auto erc = boost::system::error_code{boost::asio::error::host_not_found};

  socket.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address("127.0.0.1"), 12345), erc);
  if (erc) {
    ELOGE << "Connection failed, code: " << erc.value() << ", message: " << erc.message();
    return EXIT_FAILURE;
  }
  constexpr std::string_view request = "Hello, server!";
  ELOGI << "Sending request to server: " << request << ", length: " << request.length();
  boost::asio::write(socket, boost::asio::buffer(request, request.size()));

  char reply[kMaxBufferSize];
  const size_t reply_length = boost::asio::read(socket, boost::asio::buffer(reply, request.size()));
  ELOGI << "Received reply from server: " << std::string_view(reply, reply_length);
  return 0;
}

auto real_main(const int argc, char** argv) -> int { return sync_client_main(argc, argv); }
}  // namespace

auto main(const int argc, char** argv) -> int {
  try {
    [[maybe_unused]] auto result = real_main(argc, argv);
  } catch (const std::exception& exp) {
    ELOGE << "Main Exception:" << exp.what() << '\n';
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}