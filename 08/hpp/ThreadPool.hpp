#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <memory>
#include <future>
#include <functional>
#include <type_traits>
#include <cassert>
#include <queue>

using namespace std;

class TThreadPool
{
private:
    vector<thread> ThreadPool;
    queue<function<void()>> Tasks;
    mutex TasksMutex;
    condition_variable Condition;
    bool Stopped;
    void Runner();

public:
    TThreadPool(int threads);
    ~TThreadPool();
    template <class F, class... Args>
    auto Exec(F &&f, Args&&... args) -> std::future<typename result_of<F(Args...)>::type>;
    template <class F>
    auto Exec(F &&f) -> std::future<typename result_of<F()>::type>;
};

template <class F>
auto TThreadPool::Exec(F &&f) -> std::future<typename result_of<F()>::type>
{
    using return_type = typename result_of<F()>::type;
    auto task = make_shared<packaged_task<return_type()>>(bind(forward<F>(f)));
    future<return_type> res = task->get_future();
    {
        unique_lock<mutex> lock(TasksMutex);
        if (Stopped)
        {
            throw runtime_error("Exec on Stopped TThreadPool");
        }
        Tasks.emplace([task]() { (*task)(); });
    }
    Condition.notify_one();
    return res;
}

template <class F, class... Args>
auto TThreadPool::Exec(F &&f, Args &&... args) -> std::future<typename result_of<F(Args...)>::type>
{
    using return_type = typename result_of<F(Args...)>::type;
    auto task = make_shared<packaged_task<return_type()>>(bind(forward<F>(f), forward<Args>(args)...));
    future<return_type> res = task->get_future();
    {
        unique_lock<mutex> lock(TasksMutex);
        if (Stopped)
        {
            throw runtime_error("Exec on Stopped TThreadPool");
        }
        Tasks.emplace([task]() { (*task)(); });
    }
    Condition.notify_one();
    return res;
}