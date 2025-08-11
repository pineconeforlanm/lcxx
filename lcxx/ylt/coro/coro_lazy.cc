//
// Created by lanm on 2025/8/11.
//
#include <ylt/coro_io/coro_io.hpp>
#include <async_simple/executors/SimpleExecutor.h>

auto basic_test_3() -> async_simple::coro::Lazy<int> {
  ELOGI << "basic_test_3 start";
  ELOGI << "basic_test_3 retrn 3";
  co_await async_simple::coro::Yield{};
  ELOGI << "basic_test_3 retrn 33";
  co_await async_simple::coro::Yield{};
  ELOGI << "basic_test_3 retrn 333";
  co_await async_simple::coro::Yield{};
  ELOGI << "basic_test_3 retrn 3333";
  co_return 3333;
}

auto basic_test_2() -> async_simple::coro::Lazy<int> {
  ELOGI << "basic_test_2 start";
  ELOGI << "basic_test_2 retrn 2";
  co_await async_simple::coro::Yield{};
  ELOGI << "basic_test_2 retrn 22";
  co_await async_simple::coro::Yield{};
  ELOGI << "basic_test_2 retrn 222";
  co_await async_simple::coro::Yield{};
  ELOGI << "basic_test_2 retrn 2222";
  co_return 2222;
}

auto basic_test_1() -> async_simple::coro::Lazy<void> {
  auto result = co_await basic_test_2();
  ELOGI << "result: " << result;
  result = co_await basic_test_3();
  ELOGI << "result: " << result;
  result = co_await basic_test_2();
  ELOGI << "result: " << result;
  result = co_await basic_test_3();
  ELOGI << "result: " << result;
  result = co_await basic_test_2();
  ELOGI << "result: " << result;
  result = co_await basic_test_3();
  ELOGI << "result: " << result;
  result = co_await basic_test_2();
  ELOGI << "result: " << result;
  co_return;
}

auto basic_usage() -> async_simple::coro::Lazy<void> {
  co_await basic_test_1();
  co_return;
}

auto main(int argc, char** argv) -> int {
  async_simple::executors::SimpleExecutor executor{24};
  async_simple::coro::syncAwait(basic_usage().via(&executor));
  return 0;
}