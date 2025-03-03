#include <vector>
#include <folly/Benchmark.h>
#include <folly/init/Init.h>
#include <folly/container/Foreach.h>
using namespace std;
using namespace folly;
BENCHMARK(insertFrontVector) {
  // Let's insert 100 elements at the front of a vector
  vector<int> v;
  FOR_EACH_RANGE (i, 0, 100) {
    v.insert(v.begin(), i);
  }
}

// 画一条虚线（单行）
// 它的时间，会平分到上下两个测试中，因此会影响测试结果（增加了insertFrontVector 的耗时基数）
BENCHMARK_DRAW_LINE();

BENCHMARK(insertBackVector) {
  // Let's insert 100 elements at the back of a vector
  vector<int> v;
  FOR_EACH_RANGE (i, 0, 100) {
    v.insert(v.end(), i);
  }
}

int main() {
  runBenchmarks();
}