//
// Created by lanm on 2025/8/11.
//

#include <CLI/CLI.hpp>
#include <ylt/easylog.hpp>

import lcxx.base.config;
import lcxx.base.utils;
import std;

namespace {

auto g_filename = lcxx::base::config::Config::Lookup("root.filename", std::string_view{"default"}, "filename");
auto g_value = lcxx::base::config::Config::Lookup("root.value", 20, "value");
auto g_array = lcxx::base::config::Config::Lookup("root.array", std::vector{10, 20}, "array");

class Application {
 public:
  Application() = default;
  ~Application() = default;

  auto run([[maybe_unused]] const int argc, [[maybe_unused]] char** argv) -> int {
    ELOGI << "Application started with arguments:";

    argv = app_.ensure_utf8(argv);

    auto filename = std::string_view{"default"};
    auto value{0};
    auto array = std::vector{0, 1};
    // app_.add_option("-f,--file", filename, g_filename->GetDescription().data());
    // app_.add_option("-v", value, g_value->GetDescription().data());
    // app_.add_option("--a", array, g_array->GetDescription().data())->capture_default_str();
    //
    // CLI11_PARSE(app_, argc, argv);

    g_filename->SetValue(filename);
    g_value->SetValue(value);
    g_array->SetValue(array);

    ELOGI << "file: " << filename;
    ELOGI << "value=" << value;

    for (const auto& v : array) {
      ELOGI << "array value: " << v;
    }

    return 0;
  }

  static constexpr auto get_app_description() -> std::string_view {
    static constexpr auto app_description_sv = std::string_view{"Application description"};
    return app_description_sv;
  };

 private:
  CLI::App app_{get_app_description().data()};
};

auto cli11_main([[maybe_unused]] const int argc, [[maybe_unused]] const char** const argv) -> int {
  const auto app = std::make_unique<Application>();

  app->run(argc, const_cast<char**>(argv));

  return 0;
}

auto real_main(const int argc, const char** const argv) -> int {
  auto result{EXIT_FAILURE};
  try {
    result = cli11_main(argc, argv);
  } catch (const std::exception& e) {
    ELOGE << "Real Main Exception: " << e.what();
    result = EXIT_FAILURE;
  }
  return result;
}
}  // namespace
auto main(const int argc, const char** const argv) -> int { return real_main(argc, argv); }