#include <mutex>
#include <condition_variable>
#include <iostream>
#include <queue>

struct DataChunk {
  int value_ = 0;
  bool is_last_chunk_ = false;
};

namespace Example {
  std::mutex mut;
  std::queue<DataChunk> data_queue;
  std::condition_variable data_cond;

  void DataPrepare() {
    for (int i = 0; i != 20; ++i) {
      DataChunk data;
      data.value_ = i;
      data.is_last_chunk_ = i == 19;
      std::lock_guard<std::mutex> lk(mut);
      data_queue.push(data);
      data_cond.notify_one();
    }
  }

  void DataProcess() {
    while (true) {
      std::unique_lock<std::mutex> lk(mut);
      data_cond.wait(lk, []{ return !data_queue.empty(); });
      DataChunk data = data_queue.front();
      data_queue.pop();
      lk.unlock();
      std::cout << "process " << data.value_ << "...\n";
      if (data.is_last_chunk_) break;
    }
  }
}
