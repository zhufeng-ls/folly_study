#include <signal.h>
#include <csignal>

#include <unistd.h>
#include <thread>

#include "folly/ProducerConsumerQueue.h"
#include "folly/logging/xlog.h"

static bool g_cancel = false;

void SignalHandler(int) {
  XLOG(INFO) << "receive signal";
  g_cancel = true;
}

int main() {
  folly::ProducerConsumerQueue<int> queue(5);

  signal(SIGINT, SignalHandler);
  signal(SIGTERM, SignalHandler);

  int write_idx = 0;
  int read_idx = -1;

  std::thread t([&] {
    while (!g_cancel) {
      if (queue.write(write_idx)) {
        XLOG(INFO) << "write " << write_idx;
      } else {
        XLOG(ERR) << "write(" << write_idx << ") error" << ", full queue!";
      }

      ++write_idx;

      // 多读少写
      usleep(30 * 1000);
    }
  });

  while (!g_cancel) {
    if (queue.read(read_idx)) {
      XLOG(INFO) << "read " << read_idx;
    } else {
      XLOG(ERR) << "read" << " error" << ", empty queue!";
    }

    usleep(60 * 1000);
  }

  t.join();

  XLOG(INFO) << "exit!";
}