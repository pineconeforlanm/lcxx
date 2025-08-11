//
// Created by lanm on 2025/8/6.
//

#include <boost/asio.hpp>
#include <ylt/easylog.hpp>

import lcxx.base.utils;
import std;
namespace {

using SocketPtr = std::shared_ptr<boost::asio::ip::tcp::socket>;

constexpr auto kMaxBufferSize{1024 * 1024};

std::set<std::shared_ptr<std::thread>> worker_threads;

std::atomic_bool is_exit{false};

auto session(const SocketPtr& socket) -> void {
  try {
    auto buffer = std::array<char, kMaxBufferSize>{};
    while (is_exit.load()) {
      buffer.fill(0);
      auto error_code = boost::system::error_code{};

      do {
        auto bytes_read = socket->read_some(boost::asio::buffer(buffer), error_code);
        if (error_code) {
          break;
        }
        ELOGI << "Received " << bytes_read << " bytes from client: " << std::string_view(buffer.data(), bytes_read);

        boost::asio::write(*socket, boost::asio::buffer(buffer.data(), bytes_read));
        ELOGI << "Sent reply to client: " << buffer << ", length: " << bytes_read;
      } while (false);

      if (error_code == boost::asio::error::eof) {
        ELOGW << "Connection closed by remote endpoint: " << socket->remote_endpoint().address().to_string();
        break;
      } else if (error_code) {
        ELOGE << "Error reading from socket: " << error_code.message();
        throw boost::system::system_error{error_code};
      }
    }

  } catch (const std::exception& exp) {
    ELOGE << "Session error: " << exp.what();
  }
}

auto server(boost::asio::io_context& ioctx, const std::size_t port) -> void {
  auto acceptor =
      boost::asio::ip::tcp::acceptor(ioctx, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
  ELOGI << "Listening on port " << port;
  while (!is_exit.load()) {
    auto socket = std::make_shared<boost::asio::ip::tcp::socket>(ioctx);
    acceptor.accept(*socket);
    ELOGI << "Accepted connection from " << socket->remote_endpoint().address().to_string();
    auto th_session = std::make_shared<std::thread>(session, socket);
    worker_threads.insert(th_session);
  }
}

auto sync_server_main([[maybe_unused]] const int argc, [[maybe_unused]] char** argv) -> int {
  constexpr auto kLocalPort = 12345;
  lcxx::base::utils::log::init();
  auto ioctx = boost::asio::io_context{};

  auto signals = boost::asio::signal_set(ioctx, SIGINT, SIGTERM);
  signals.async_wait([&](const auto /*error*/, auto /*signal_number*/) {
    ELOGI << "Signal received, exiting...";
    is_exit.store(false);
    ioctx.stop();
  });

  server(ioctx, kLocalPort);

  for (auto& th_session : worker_threads) {
    if (th_session->joinable()) {
      th_session->join();
    }
  }

  return 0;
}

auto real_main(const int argc, char** argv) -> int { return sync_server_main(argc, argv); }
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