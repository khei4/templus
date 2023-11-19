include(FetchContent)
if(${CMAKE_VERSION} VERSION_LESS "3.25")
FetchContent_Declare(googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG main
)
else()
FetchContent_Declare(googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG main
  DOWNLOAD_EXTRACT_TIMESTAMP true
)
endif()

FetchContent_MakeAvailable(googlebenchmark)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/benchmarks)

# each benchmark is a separate executable
add_executable(bench1 benchmark1.cpp)
target_link_libraries(bench1 benchmark::benchmark)
list(APPEND ALL_BENCHMARKS bench1)





set(ALL_BENCHMARKS ${ALL_BENCHMARKS} PARENT_SCOPE)