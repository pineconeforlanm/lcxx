//
// Created by lanm on 2025/8/6.
//
import std;

auto main() -> int {
  try {
    std::println("Hello, this project is learn cxx!");
    const auto vec = std::vector<int>{1, 2, 3, 4, 5};
    std::print("Vector elements: ");
    for (const auto& elem : vec) {
      std::print("{} ", elem);
    }
    std::println();
  } catch (const std::exception& exp) {
    std::cerr << exp.what() << '\n';
  }
  return 0;
}