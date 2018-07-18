#include <iostream>
#include <thread>
#include <numeric>
#include <vector>

#include "parallel_accumulate.h"
#include "threadsafe_stack.h"
#include "threadsafe_swap.h"
#include "hierarchical_mutex.h"
#include "threadsafe_map.h"

#define TEST_THREADSAFE_MAP 1

template<typename C>
void Print(const C& c) {
  for (auto&& i : c) std::cout << i << " ";
  std::cout << std::endl;
}

void hello() {
	std::cout << "Hello Concurrent World\n";
}

void simple_example() {
	// For the initial thread in an applicaiton, this is `main()`,
	// but for every other thread it's specified in the constructor of
	// a `std::thread` object.
	std::thread t(hello);

	// now, the thread count is two.
	// After the new thread has been launched,
	// the initial thread continues execution.
	// If it didn't wait for the new thread to finish,
	// it would merrily continue to the end of `main()` and thus end the program.
	// possibly before the new thread had had a chance to run.

	t.join();
	// `join()` causes the calling thread(in main()) to wait for
	// the thread associated withe the `t`.
}

class background_task {
public:
	void operator()() const {
		std::cout << "do something\n";
		std::cout << "do something else\n";
	}
};

void callable_example() {
	// background_task bt;

	// the supplied function object is **copied** into the storage belonging
	// to the newly created thread of execution and invoked from there.

	// ```cpp
	// std::thread my_thread(background_task());
	// ```
	// declares a function `my_thread` that takes a single parameter,
	// and returns a std::thread object, rather than launching a new thread.

	// you can avoid this by nameing your function object as shown previously:
	std::thread my_thread{ background_task() };
	// or std::thread my_thread((background_task()));
	// of course, you can use lambda.

	std::thread my_thread2([](int i) {
		std::cout << i << "from lambda\n";
		std::cout << "else from lambda too\n";
	}, 3);

	my_thread.join();
	my_thread2.join();
}

struct func {
	double& d_;
	//double d_;
	func(double& d) : d_(d) {}
	//func(double d) : d_(d) {}

	void operator()() {
		for (unsigned i = 0; i < 1000000; ++i) {
			std::cout << "do something (d = " << d_ << ")\n";
		}
	}
};

void do_something_in_current_thread() {
  std::this_thread::sleep_for(std::chrono::milliseconds(2));
	throw;
}

void oops() {
	double some_local_state = 3.0;
	func my_func(some_local_state);
	std::thread t(my_func);
	//t.detach(); // don't wait for thread to finish.

	try {
		do_something_in_current_thread();
	}
	catch (...) {
		t.join();
		throw;
	}
	t.join();
} // new thread might still be running.

// How to fix it?
// One common way to handle this scenario is to make the thread
// function self-contained and copy the data into the thread rather
// than sharing the data.

// Using RAII to wait for a thread to complete

class thread_guard {
	std::thread& t_;
public:
	explicit thread_guard(std::thread& t) : t_(t) {}
	~thread_guard() {
		if (t_.joinable())
			t_.join();
	}

	thread_guard(const thread_guard&) = delete;
	thread_guard& operator=(const thread_guard&) = delete;
};

void no_oops() {
	double some_local_state = 2.0;
	func my_func(some_local_state);
	std::thread t(my_func);
	thread_guard g(t);
	do_something_in_current_thread();
}

class scoped_thread {
public:
  explicit scoped_thread(std::thread t) : t_(std::move(t)) {
    if (!t_.joinable())
      throw std::logic_error("No thread");
  }
  ~scoped_thread() { 
    t_.join(); 
  }

  scoped_thread(const scoped_thread&) = delete;
  scoped_thread& operator=(const scoped_thread&) = delete;

private:
  std::thread t_;
};

int main()
{
#ifdef TEST_CALLABLE
  callable_example();
#endif

#ifdef TEST_PARALLEL_ACCUMULATE
  unsigned int n = std::thread::hardware_concurrency();
  std::cout << n << " concurrent threads are supported.\n";
  
  std::vector<int> vec{1,3,4,5,6,80,7,8,4,3,2,4,5,64,23,4,5,4,32,53,2323,23,2,23,89,67,7878,9};
  auto sum = parallel_accumulate(vec.begin(), vec.end(), 0);
  std::cout << sum << std::endl;

  std::cout << std::this_thread::get_id() << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
#endif

#ifdef TEST_THREADSAFE_STACK
  ThreadSafeStack<int> stack;
  
  std::thread productor([](ThreadSafeStack<int> &s){
    int n = 10;
    while (n --> 0) {
      s.Push(n);
      std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
  }, std::ref(stack));
  
  std::thread customer([](ThreadSafeStack<int> &s){
    while (true) {
      if (!s.Empty())
        std::cout << *s.Pop() << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
  }, std::ref(stack));
  
  productor.join();
  customer.join();
#endif

#ifdef TEST_THREADSAFE_SWAP
  X safe_big_a(BigObject{3, 5, 7, 8, 0, 2});
  X safe_big_b(BigObject{4, 6, 8, 9, 2, 1});
  
  std::thread swap_thread([](X& lhs, X& rhs){
    std::swap(lhs, rhs);
  }, std::ref(safe_big_a), std::ref(safe_big_b));
  
  swap_thread.join();
  
  Print(safe_big_a.big_object());
  Print(safe_big_b.big_object());
#endif

#ifdef TEST_HIERARCHICAL_MUTEX
  HierarchicalMutex high_level_mutex(10000);
  HierarchicalMutex low_level_mutex(5000);
  
  auto LowLevelFunc = [&](){
    std::lock_guard<HierarchicalMutex> lk(low_level_mutex);
    std::cout << "do some low level stuff..." << std::endl;
  };
  
  auto HighLevelFunc = [&](){
    std::lock_guard<HierarchicalMutex> lk(high_level_mutex);
    std::cout << "do some low level stuff...\ndo some high level stuff..." << std::endl;
  };
  
  HierarchicalMutex other_mutex(100);
  auto OtherStuff = [&](){
    HighLevelFunc();
    std::cout << "do other stuff..." << std::endl;
  };
  
  std::thread thread_a([&](){
    HighLevelFunc();
  });
  
  std::thread thread_b([&](){
    std::lock_guard<HierarchicalMutex> lk(other_mutex);
    try {
      OtherStuff();
    } catch (std::logic_error e) {
      // HighLevelFunc tries to acquire the high_level_mutex, which has a value 
      // 10000, considerably more than the current hierarchy value of 100.
      // The HierarchicalMutex will therefore report an error.
      std::cout << e.what() << std::endl;
    }
  });
  
  thread_a.join();
  thread_b.join();
#endif

#ifdef TEST_THREADSAFE_MAP
  DnsCache cache;
  std::thread writer([&cache](){
    cache.UpdateOrAddEntry("www.baidu.com", DnsEntry("220.181.112.244"));
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    cache.UpdateOrAddEntry("www.sina.com", DnsEntry("66.102.251.33"));
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    cache.UpdateOrAddEntry("www.google.com", DnsEntry("69.171.248.112"));
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    cache.UpdateOrAddEntry("www.zhihu.com", DnsEntry("118.89.204.100"));
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    cache.UpdateOrAddEntry("www.douban.com", DnsEntry("154.8.131.171"));
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
  });
  
  auto view_web = [&cache](const std::string& domain) {
    for (int i = 0; i != 4; ++i) {
      const auto& entry = cache.FindEntry(domain);
      std::cout << (entry.ip_.empty() ? "cannot find..." : entry.ip_) << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
  };
  
  std::thread reader_douban(view_web, "www.douban.com");
  std::thread reader_zhihu(view_web, "www.zhihu.com");
  std::thread reader_baidu(view_web, "www.baidu.com");
  
  writer.join();
  reader_douban.join();
  reader_zhihu.join();
  reader_baidu.join();
#endif
}