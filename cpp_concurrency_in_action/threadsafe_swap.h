#include <mutex>

typedef std::vector<int> BigObject;

class X {
public:
  X() = default;
  X(const X& other) : big_object_(other.big_object_) {}
  X& operator=(X x) {
    swap(*this, x);
    return *this;
  }
  X(const BigObject& b) : big_object_(b) {}
  friend void swap(X& lhs, X& rhs) {
    if (&lhs == &rhs)
      return;
    // attempting to acquire a lock on a `std::mutex` when you already hold it
    // **is undefined behavior**.
    std::lock(lhs.m_, rhs.m_);
    // `std::lock` can lock a series of calls to lock.
    std::lock_guard<std::mutex> lock_a(lhs.m_, std::adopt_lock);
    std::lock_guard<std::mutex> lock_b(rhs.m_, std::adopt_lock);
    // `std::adopt_lock` indicates to the `std::lock_guard` objects that the
    // mutexes are already locked.
    swap(lhs.big_object_, rhs.big_object_);
  }
  
  const BigObject& big_object() const {
    return big_object_;
  }
private:
  BigObject big_object_;
  std::mutex m_;
};