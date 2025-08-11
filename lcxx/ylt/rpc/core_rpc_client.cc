//
// Created by lanm on 2025/8/11.
//
#include <async_simple/coro/Lazy.h>

#include <cstdlib>
#include <ylt/coro_rpc/coro_rpc_client.hpp>
#include <ylt/easylog.hpp>
import lcxx.base.utils;
import std;

namespace {

std::uint64_t send_times{0};

// 时间转换工具类
class TimeConverter {
 public:
  // 从chrono时间点转换为uint64_t（微秒级时间戳）
  static auto chrono_to_uint64(const std::chrono::system_clock::time_point& time_point) -> uint64_t {
    const auto duration = time_point.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
  }

  // 从uint64_t（微秒级时间戳）转换为chrono时间点
  static auto uint64_to_chrono(uint64_t timestamp) -> std::chrono::system_clock::time_point {
    return std::chrono::system_clock::time_point(std::chrono::microseconds(timestamp));
  }

  // 将chrono时间点格式化为年月日时分秒微秒字符串
  static auto format_chrono_time(const std::chrono::system_clock::time_point& time_point) -> std::string {
    constexpr auto kMicroWigth{6};
    // 转换为时间_t（秒级精度）
    const std::time_t time_t_val = std::chrono::system_clock::to_time_t(time_point);

    // 获取微秒部分
    const auto microseconds =
        std::chrono::duration_cast<std::chrono::microseconds>(time_point.time_since_epoch() % std::chrono::seconds(1))
            .count();

    // 转换为本地时间
    auto const* tm_val = std::localtime(&time_t_val);
    if (tm_val == nullptr) {
      return "Invalid time";
    }

    // 格式化输出
    std::stringstream out;
    out << std::put_time(tm_val, "%Y-%m-%d %H:%M:%S") << "." << std::setw(kMicroWigth) << std::setfill('0')
        << microseconds;
    return out.str();
  }

  // 将uint64_t时间戳格式化为年月日时分秒微秒字符串
  static auto format_uint64_time(uint64_t timestamp) -> std::string {
    const auto time_point = uint64_to_chrono(timestamp);
    return format_chrono_time(time_point);
  }
};

class Statistics {
 public:
  Statistics() = default;

  auto update(uint64_t value) -> void {
    constexpr auto kMillSeconds{1000};
    static uint64_t counter = 0;
    if (value >= kMillSeconds) {
      overflow_++;
    }
    if (value > max_ || max_ == 0) {
      max_ = value;
    }
    if (value < min_ || min_ == 0) {
      min_ = value;
    }
    sum_ += value;
    avg_ = static_cast<double>(sum_) / static_cast<double>(++counter);
  }

  auto get_max() const -> uint64_t { return max_; }
  auto get_min() const -> uint64_t { return min_; }
  auto get_sum() const -> uint64_t { return sum_; }
  auto get_avg() const -> double { return avg_; }

  auto show_stats() const -> void {
    ELOGI << "echo times [ " << send_times << "], overflow 1ms times [" << overflow_ << "] Max: " << max_
              << "us, Min: " << min_ << "us, Sum: " << sum_ << "us, Avg: " << avg_ << "us\n";
  }

 private:
  uint64_t max_{};
  uint64_t min_{};
  uint64_t sum_{};
  uint64_t overflow_{};
  mutable double avg_{};
};

Statistics recv_stats;
constexpr auto kEchoTimes{1000 * 10};

auto rpc_client_main(const int argc, const char** argv) -> async_simple::coro::Lazy<void> {
  lcxx::base::utils::log::init();
  auto rpc_client = coro_rpc::coro_rpc_client{};
  [[maybe_unused]] const auto erc = co_await rpc_client.connect("127.0.0.1", "8801");
  assert(!erc);

  auto ofs = std::ofstream{"coro_rpc_echo.csv"};
  while (send_times++ < kEchoTimes) {
    auto now = TimeConverter::chrono_to_uint64(std::chrono::system_clock::now());
    [[maybe_unused]] const auto ret = co_await rpc_client.call<lcxx::base::utils::rpc::echo>("hello");
    auto ent = TimeConverter::chrono_to_uint64(std::chrono::system_clock::now());
    recv_stats.update(ent - now);
    ELOGI << "ECHO:" << ret.value() << ", send_times: " << send_times
          << ", now: " << TimeConverter::format_uint64_time(now)
          << ", ent: " << TimeConverter::format_uint64_time(ent)
          << ", cost: " << (ent - now) << "us";
    ofs << now << "," << ent << "\n";
  }
  co_return;
}

auto real_main(const int argc, const char** argv) -> int {
  try {
    async_simple::coro::syncAwait(rpc_client_main(argc, argv));
  } catch (std::exception& exp) {
    std::println("Main Exception: {}", exp.what());
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
}  // namespace
auto main(const int argc, const char** argv) -> int { return real_main(argc, argv); }