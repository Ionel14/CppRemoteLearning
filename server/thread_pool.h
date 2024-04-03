#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <condition_variable> 
#include <functional> 
#include <iostream> 
#include <mutex> 
#include <queue> 
#include <thread> 

namespace smart_home
{


class ThreadPool { 
public:  
    ThreadPool(int num_threads = 2);
    ~ThreadPool();
  
    void enqueue(std::function<void()> task);
  
private: 
    std::vector<std::thread> threads_;   
    std::queue<std::function<void()>> tasks_; 
    std::mutex queue_mutex_; 
    std::condition_variable mutex_condition; 
    bool stop_ = false; 
};
    
} // namespace smart_home

#endif