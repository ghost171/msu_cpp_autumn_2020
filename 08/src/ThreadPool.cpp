#include <iostream>
#include <vector>
#include <thread>
#include <memory>
#include <future>
#include <functional>
#include <type_traits>
#include <cassert>
#include <queue>
#include "../hpp/ThreadPool.hpp"

using namespace std;

void TThreadPool::Runner()
{
    while(true) {
        function<void()> task;
        {
            unique_lock<std::mutex> lock(TasksMutex);
            Condition.wait(lock, [this] { return (Stopped || !Tasks.empty());});
            if (Stopped && Tasks.empty()) {
                return;
            }
            task = move(Tasks.front());
            Tasks.pop();
        }
        task();
    }
}

TThreadPool::TThreadPool(int threads) {
    Stopped = false;
    for (int i = 0; i < threads; i++)
    {
        ThreadPool.emplace_back(thread(&TThreadPool::Runner, this));
    }
}

TThreadPool::~TThreadPool()
{
    {
        unique_lock<mutex> lock(TasksMutex);
        Stopped = true;
    }
    Condition.notify_all();
    for (thread &tred : ThreadPool) {
        tred.join();
    }

}