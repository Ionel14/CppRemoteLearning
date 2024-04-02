#include "../headers/thread_pool.h"

namespace smarthome {

ThreadPool::ThreadPool(size_t n) { 
  for (size_t i = 0; i < n; ++i) { 
    threads.emplace_back([this] { 
      while (true) { 
        std::function<void()> task; 
        { 
          std::unique_lock<std::mutex> lock(queueMutex); 

          // Wait until there is a task or the pool is stopped 
          cv.wait(lock, [this] { 
              return !tasks.empty() || stop; 
          }); 

          // Exit the thread if the pool is stopped and there are no tasks 
          if (stop && tasks.empty()) { 
              return; 
          } 

          // Get the next task from the queue 
          task = move(tasks.front()); 
          tasks.pop(); 
        } 

        task(); 
      } 
    }); 
  } 
} 

ThreadPool::~ThreadPool() { 
  { 
    std::unique_lock<std::mutex> lock(queueMutex); 
    stop = true; 
  } 

  cv.notify_all(); 
  for (auto& thread : threads) { 
      thread.join(); 
  } 
} 

void ThreadPool::enqueue(std::function<void()> task) { 
  { 
    std::unique_lock<std::mutex> lock(queueMutex); 
    tasks.emplace(move(task)); 
  } 
  cv.notify_one(); 
} 

} // namespace smarthome
