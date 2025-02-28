add_executable(atomic_map_test atomic_map_test.cc)
target_link_libraries(atomic_map_test folly)

add_executable(benchmark_test benchmark_test.cc)
target_link_libraries(benchmark_test folly follybenchmark)

add_executable(queue_test queue_test.cc)
target_link_libraries(queue_test folly)

add_executable(conv_test conv_test.cc)
target_link_libraries(conv_test folly)

add_executable(dynamic_test dynamic_test.cc)
target_link_libraries(dynamic_test folly)