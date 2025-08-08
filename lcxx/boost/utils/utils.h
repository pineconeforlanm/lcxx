#pragma once

#include <string_view>

namespace lcxx::utils {
namespace boost {
auto version() -> std::size_t;
auto lib_version() -> std::string_view;
}  // namespace boost

auto version() -> std::string_view;
auto major_version() -> std::size_t;
auto minor_version() -> std::size_t;
auto patch_version() -> std::size_t;
auto tweak_version() -> std::size_t;

namespace log {
auto init() -> void;
}

}  // namespace lcxx::utils
