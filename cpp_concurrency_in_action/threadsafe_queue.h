#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue {
public:
 void Push(T new_value) {
   std::lock_guard<std::mutex> lk(mut_);
   data_queue_.push(new_value);
   data_cond_.notify_one();
 }
 void WaitAndPop(T& value) {
   std::unique_lock<std::mutex> lk(mut_);
   data_cond_.wait(lk, [this]{return !data_queue_.empty();});
   value = data_queue_.front();
   data_queue_.pop();
 }
private:
 std::mutex mut_;
 std::queue<T> data_queue_;
 std::condition_variable data_cond_;
};
