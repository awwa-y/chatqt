#include "AsioIOServicePool.h"
#include <iostream>

using namespace std;

AsioIOServicePool::AsioIOServicePool(std::size_t size)
    : _ioServices(size),
    _nextIOService(0)
{
    // 为每个 io_context 创建工作对象
    for (std::size_t i = 0; i < size; ++i) {
        // 在 Boost 1.89 中，必须使用 make_work_guard 来创建 executor_work_guard
        _works.emplace_back(
            std::make_unique<Work>(
                boost::asio::make_work_guard(_ioServices[i])
            )
        );
    }

    // 遍历多个 io_context，创建多个线程，每个线程内部启动 io_context
    for (std::size_t i = 0; i < size; ++i) {
        _threads.emplace_back([this, i]() {
            try {
                _ioServices[i].run();
            }
            catch (const std::exception& e) {
                std::cerr << "Exception in thread " << i << ": " << e.what() << std::endl;
            }
            });
    }
}

AsioIOServicePool::~AsioIOServicePool() {
    Stop();
    std::cout << "AsioIOServicePool destruct" << endl;
}

boost::asio::io_context& AsioIOServicePool::GetIOService() {
    auto& service = _ioServices[_nextIOService++];
    if (_nextIOService >= _ioServices.size()) {
        _nextIOService = 0;
    }
    return service;
}

void AsioIOServicePool::Stop() {
    // 1. 先销毁所有工作对象，这样 io_context 会在完成所有任务后自然退出
    for (auto& work : _works) {
        work.reset();
    }

    // 2. 然后停止所有 io_context（这会取消所有未完成的操作）
    for (auto& service : _ioServices) {
        service.stop();
    }

    // 3. 等待所有线程结束
    for (auto& t : _threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    // 4. 清理所有容器
    _threads.clear();
    _works.clear();
}