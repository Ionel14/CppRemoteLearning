#include "thread_pool.h"

namespace smart_home
{

    ThreadPool::ThreadPool(int num_threads)
    { 
  
        for (int i = 0; i < num_threads; ++i) { 
            threads_.emplace_back([this] { 
                while (true) { 
                    std::function<void()> task; 
                    {  
                        std::unique_lock<std::mutex> lock(queue_mutex_); 
  
                        mutex_condition.wait(lock, [this] { 
                            return !tasks_.empty() || stop_; 
                        }); 
  
                        if (stop_ && tasks_.empty()) { 
                            return; 
                        } 
  
                        task = std::move(tasks_.front()); 
                        tasks_.pop(); 
                    } 
  
                    task(); 
                } 
            }); 
        } 
    }

    ThreadPool::~ThreadPool()
    { 
        { 
            std::unique_lock<std::mutex> lock(queue_mutex_); 
            stop_ = true; 
        } 
  
        mutex_condition.notify_all(); 
  
        // Joining all worker threads to ensure they have 
        // completed their tasks 
        for (auto& thread : threads_) { 
            thread.join(); 
        } 
    }
    
    void ThreadPool::enqueue(std::function<void()> task)
    { 
        std::unique_lock<std::mutex> lock(queue_mutex_); 
        tasks_.emplace(std::move(task));  
        mutex_condition.notify_one(); 
    } 

} // namespace smart_home