#include <async_simple/coro/Lazy.h>
#include <async_simple/coro/SyncAwait.h>
#include <async_simple/executors/SimpleExecutor.h>

#include <iostream>

// 模拟IO密集型任务（应在IO执行器上运行）
async_simple::coro::Lazy<std::string> readFile(const std::string& filename) {
  std::cout << "Reading file: " << filename
            << " (thread: " << std::this_thread::get_id() << ")" << std::endl;
  co_await async_simple::coro::Yield{};  // 模拟IO等待
  co_return "Content of " + filename;
}

// 模拟计算密集型任务（应在CPU执行器上运行）
async_simple::coro::Lazy<int> heavyCompute(int data) {
  std::cout << "Heavy compute with data: " << data
            << " (thread: " << std::this_thread::get_id() << ")" << std::endl;
  co_await async_simple::coro::Yield{};  // 模拟计算过程
  co_return data * 2;
}

// 主任务：先IO读取，再计算处理
async_simple::coro::Lazy<void> ioThenCompute(
    async_simple::Executor* ioExecutor,
    async_simple::Executor* cpuExecutor
) {
  // 1. 在IO执行器上读取文件
  std::string content = co_await readFile("test.txt").via(ioExecutor);
  std::cout << "Read content: " << content << std::endl;

  // 2. 切换到CPU执行器进行计算
  int result = co_await heavyCompute(100).via(cpuExecutor);
  std::cout << "Compute result: " << result << std::endl;

  co_return;
}

int main() {
  // 创建两个执行器：IO执行器（1线程）、CPU执行器（4线程）
  async_simple::executors::SimpleExecutor ioExecutor(1);
  async_simple::executors::SimpleExecutor cpuExecutor(4);

  // 启动任务，初始执行器可任意（后续会切换）
  syncAwait(ioThenCompute(&ioExecutor, &cpuExecutor).via(&ioExecutor));
  return 0;
}
