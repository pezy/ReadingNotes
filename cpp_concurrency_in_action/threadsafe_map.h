#include <unordered_map>
#include <string>
#include <mutex>
#include <utility>
#include "boost/thread.hpp"

struct DnsEntry {
  DnsEntry() = default;
  DnsEntry(std::string&& ip) : ip_(std::forward<std::string>(ip)) {}
  std::string ip_;
};

class DnsCache {
public:
  DnsEntry FindEntry(const std::string& domain) const {
    boost::shared_lock<boost::shared_mutex> lk(entry_mutex_);
    const auto iter = entries_.find(domain);
    return (iter == entries_.end()) ? DnsEntry() : iter->second;
  }
  void UpdateOrAddEntry(const std::string& domain, const DnsEntry& dns_detail) {
    std::lock_guard<boost::shared_mutex> lk(entry_mutex_);
    entries_[domain] = dns_detail;
  }
private:
  std::unordered_map<std::string, DnsEntry> entries_;
  mutable boost::shared_mutex entry_mutex_;
};