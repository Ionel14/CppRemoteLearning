#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

namespace smartHome{
    class MyThreadPool{
    public:
        explicit MyThreadPool(size_t numThreads);
        ~MyThreadPool();
        void enqueue(std::function<void()> task);

    private:
        std::vector<std::thread> threads;
        std::queue<std::function<void()>> tasks;
        std::mutex queueMutex;
        std::condition_variable condition;
        bool stop;
    };
}

#endif // THREADPOOL_H
