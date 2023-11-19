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


file(GLOB BENCH_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/benchmarks/*.cpp)
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS *.cpp)
foreach(BENCH_SRC ${BENCH_SOURCES})
  get_filename_component(BENCH_NAME ${BENCH_SRC} NAME_WE)
  add_executable(${BENCH_NAME} ${BENCH_SRC})
  target_link_libraries(${BENCH_NAME} benchmark::benchmark)
  list(APPEND ALL_BENCHMARKS ${BENCH_NAME})
endforeach()





set(ALL_BENCHMARKS ${ALL_BENCHMARKS} PARENT_SCOPE)