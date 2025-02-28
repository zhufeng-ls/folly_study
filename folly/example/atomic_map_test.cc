#include <unistd.h>
#include <iostream>
#include <thread>
#include <vector>

#include <folly/AtomicHashMap.h>
#include <folly/logging/xlog.h>

// 定义哈希表类型：键类型为int，值类型为std::string
// 初始桶大小1024，最大容量100,000
using MapType = folly::AtomicHashMap<int, std::string>;

void insert_task(MapType* map, int start, int end) {
  for (int i = start; i < end; ++i) {
    auto ret = map->insert(i, "Value_" + std::to_string(i));
    if (!ret.second) { // 插入失败处理
      std::cerr << "Key " << i << " already exists\n";
    }
  }
}

int main() {
  // 初始化哈希表（预分配内存）
  MapType map(1024);

  XLOG(INFO) << "===start===";

  // 单线程基础操作演示
  map.insert(0, "Initial_Value"); // 插入元素

  XLOG(INFO) << "insert Initial_Value";

  auto it = map.find(0); // 查找元素
  if (it != map.end()) {
    XLOG(INFO) << "Found: " << it->second;
  }

  map.erase(0); // 删除元素
  XLOG(INFO) << "Size after erase: " << map.size() << "\n\n";

  // 多线程并发写入演示
  const int num_threads = 4;
  const int per_thread = 1000;
  std::vector<std::thread> threads;

  for (int i = 0; i < num_threads; ++i) {
    threads.emplace_back(
        insert_task, &map, i * per_thread, (i + 1) * per_thread);
  }

  for (auto& t : threads) {
    t.join();
  }

  // 验证结果
  XLOG(INFO) << "Final size: " << map.size() << "\n";
  XLOG(INFO) << "Find key 42: " << map.find(42)->second << "\n";

  return 0;
}
