module lcxx.utils;  // 明确指定属于哪个模块，不需要再import
#include <boost/version.hpp>

import std;

namespace lcxx::utils {

namespace boost {  // 与接口中的命名空间保持一致
auto version() -> std::size_t { return BOOST_VERSION; }
auto lib_version() -> std::string_view { return BOOST_LIB_VERSION; }
}  // namespace boost

auto version() -> std::string_view { return LCXX_UTILS_VERSION; }
auto major_version() -> std::size_t { return LCXX_UTILS_VERSION_MAJOR; }
auto minor_version() -> std::size_t { return LCXX_UTILS_VERSION_MINOR; }
auto patch_version() -> std::size_t { return LCXX_UTILS_VERSION_PATCH; }
auto tweak_version() -> std::size_t { return LCXX_UTILS_VERSION_TWEAK; }

}  // namespace lcxx::utils