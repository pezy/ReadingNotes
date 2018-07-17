#include <exception>
#include <memory>
#include <mutex>
#include <stack>

struct EmptyStack : std::exception {
  const char* what() const throw() {
    return "empty stack";
  }
};

template<typename T>
class ThreadSafeStack {
public:
  ThreadSafeStack(){}
  ThreadSafeStack(const ThreadSafeStack& other) {
    std::lock_guard<std::mutex> lock(other.m_);
    data_ = other.data_;
  }
  ThreadSafeStack& operator=(const ThreadSafeStack&) = delete;
  
  void Push(T new_value){
    std::lock_guard<std::mutex> lock(m_);
    data_.push(new_value);
  }
  std::shared_ptr<T> Pop(){
    std::lock_guard<std::mutex> lock(m_);
    if (data_.empty()) throw EmptyStack();
    const std::shared_ptr<T> res(std::make_shared<T>(data_.top()));
    data_.pop();
    return res;
  }
  void Pop(T& value){
    std::lock_guard<std::mutex> lock(m_);
    if (data_.empty()) throw EmptyStack();
    value = data_.top();
    data_.pop();
  }
  bool Empty() const {
    std::lock_guard<std::mutex> lock(m_);
    return data_.empty();
  }
  
private:
  std::stack<T> data_;
  mutable std::mutex m_;
};