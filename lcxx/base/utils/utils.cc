module;

#include <boost/version.hpp>
#include <ylt/easylog.hpp>

module lcxx.base.utils;  // 明确指定属于哪个模块，不需要再import

import std;

namespace lcxx::base::utils {

inline auto GetThreadId() -> pid_t {
  thread_local auto const s_pid = static_cast<pid_t>(::syscall(SYS_gettid));
  return s_pid;
}

inline auto GetHostName() -> std::optional<std::string_view> {
  static auto s_host_name = std::array<char, 1024>{0};
  if (const auto status = gethostname(s_host_name.data(), s_host_name.size()); status < 0) {
    ELOGE << "gethostname() failed";
  }
  return s_host_name.data()[0] ? std::optional<std::string_view>{s_host_name.data()} : std::nullopt;
}

namespace boost {  // 与接口中的命名空间保持一致
auto version() -> std::size_t { return BOOST_VERSION; }
auto lib_version() -> std::string_view { return BOOST_LIB_VERSION; }
}  // namespace boost

auto version() -> std::string_view { return LCXX_UTILS_VERSION; }
auto major_version() -> std::size_t { return LCXX_UTILS_VERSION_MAJOR; }
auto minor_version() -> std::size_t { return LCXX_UTILS_VERSION_MINOR; }
auto patch_version() -> std::size_t { return LCXX_UTILS_VERSION_PATCH; }
auto tweak_version() -> std::size_t { return LCXX_UTILS_VERSION_TWEAK; }

namespace log {
auto init() -> void {
  easylog::init_log(easylog::Severity::INFO);
}
}

namespace rpc {
auto echo(const std::string_view data) -> std::string_view {
  ELOGI << "call echo with data: " << data;
  return data;
}
}  // namespace rpc

}  // namespace lcxx::utils