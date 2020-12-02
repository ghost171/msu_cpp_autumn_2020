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

void TThreadPool::ShutDown() {
        Terminate = true;
        Condition.notify_all();
        for (thread &thread : ThreadPool) {
            thread.join();
        }
        ThreadPool.clear();
        Stopped = true;
    }

void TThreadPool::Runner() {
    function<void()> task;
    while (true) {
        {
            unique_lock<mutex> lock(TasksMutex);
            Condition.wait(lock, [this] { return !Tasks.empty() || Terminate; });
            if (Terminate && Tasks.empty()) {
                return;
            }
            task = Tasks.front();
            Tasks.pop();
        }
        try {
            task();
        } catch (runtime_error &ex) {
            cout << "at " << this_thread::get_id() << " " << ex.what() << endl;
        }
    }
}

TThreadPool::TThreadPool(int threads) {
    Terminate = false;
    Stopped = false;
    for (int i = 0; i < threads; i++) {
        ThreadPool.emplace_back(thread(&TThreadPool::Runner, this));
    }
}

TThreadPool::~TThreadPool() {
    if (!Stopped) {
        ShutDown();
    }
}