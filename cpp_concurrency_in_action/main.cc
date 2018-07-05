#include <iostream>
#include <thread>
#include <numeric>
#include <algorithm>
#include <vector>

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

	std::thread my_thread2([]() {
		std::cout << "from lambda\n";
		std::cout << "else from lambda too\n";
	});

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

void f() {
  double some_local_state  = 2.0;
  scoped_thread t(std::thread(func(some_local_state)));
  do_something_in_current_thread();
}

template<typename Iterator, typename T>
struct accumulate_block {
  void operator()(Iterator first, Iterator last, T& result) {
    result = std::accumulate(first, last, result);
  }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
  const unsigned long length = std::distance(first, last);
  if (!length) return init;

  const unsigned long min_per_thread = 25;
  const unsigned long max_threads = (length + min_per_thread - 1) / min_per_thread;
  const unsigned long hardware_threads = std::thread::hardware_concurrency();
  const unsigned long num_threads = std::min(hardware_threads ? hardware_threads : 2, max_threads);
  const unsigned long block_size = length / num_threads;

  std::vector<T> results(num_threads);
  std::vector<std::thread> threads(num_threads - 1);

  Iterator block_start = first;
  for (unsigned long i = 0; i < num_threads - 1; ++i) {
    Iterator block_end = block_start;
    std::advance(block_end, block_size);
    threads[i] = std::thread(accumulate_block<Iterator, T>(), block_start, block_end, std::ref(results[i]));
    block_start = block_end;
  }

  accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);
  std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
  return std::accumulate(results.begin(), results.end(), init);
}

int main()
{
  unsigned int n = std::thread::hardware_concurrency();
  std::cout << n << " concurrent threads are supported.\n";

	// every thread has to have an `initial function`, 
	// which is where the new thread of execution begins.

	//simple_example();
	//callable_example();
	//no_oops();
	//f();

  std::vector<int> vec{1,3,4,5,6,80,7,8,4,3,2,4,5,64,23,4,5,4,32,53,2323,23,2,23,89,67,7878,9};
  auto sum = parallel_accumulate(vec.begin(), vec.end(), 0);
  std::cout << sum << std::endl;

  std::cout << std::this_thread::get_id() << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
}