#include <mutex>
#include <thread>
#include <exception>

class HierarchicalMutex {
public:
  explicit HierarchicalMutex(unsigned long value) : hierarchy_value_(value){}
  void lock() {
    CheckForHierarchyViolation();
    internal_mutex_.lock();
    UpdateHierarchyValue();
  }
  void unlock() {
    this_thread_hiearchy_value_ = previous_hierarchy_value_;
    internal_mutex_.unlock();
  }
  bool try_lock() {
    CheckForHierarchyViolation();
    if (!internal_mutex_.try_lock())
      return false;
    UpdateHierarchyValue();
    return true;
  }
private:
  std::mutex internal_mutex_;
  const unsigned long hierarchy_value_;
  unsigned long previous_hierarchy_value_ = 0;
  static thread_local unsigned long this_thread_hiearchy_value_;
  
  void CheckForHierarchyViolation() {
    if (this_thread_hiearchy_value_ <= hierarchy_value_) {
      throw std::logic_error("mutex hierarchy violated");
    }
  }
  void UpdateHierarchyValue() {
    previous_hierarchy_value_ = this_thread_hiearchy_value_;
    this_thread_hiearchy_value_ = hierarchy_value_;
  }
};

thread_local unsigned long HierarchicalMutex::this_thread_hiearchy_value_(ULONG_MAX);