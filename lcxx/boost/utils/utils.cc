#include <utils/utils.h>
#include <boost/version.hpp>
#include <ylt/easylog.hpp>

namespace lcxx::utils {

namespace boost {
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
#ifdef NDEBUG
  constexpr auto level = easylog::Severity::WARN;
#else
  constexpr auto level = easylog::Severity::DEBUG;
#endif
  easylog::init_log(level);
}
}

}  // namespace lcxx::utils
