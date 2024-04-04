#ifndef SMARTHOME_THREADPOOL_H_
#define SMARTHOME_THREADPOOL_H_

#include <condition_variable> 
#include <functional> 
#include <iostream> 
#include <mutex> 
#include <queue> 
#include <thread> 

namespace smarthome {

class ThreadPool { 
public: 
    ThreadPool(size_t n = std::thread::hardware_concurrency());
  
    ~ThreadPool();
  
    void enqueue(std::function<void()> task);
  
private: 
    std::vector<std::thread> threads; 
    std::queue<std::function<void()> > tasks; 
    std::mutex queueMutex; 
    std::condition_variable cv; 
    bool stop = false; 
};

} // namespace smarthome
#endif  // SMARTHOME_THREADPOOL_H_