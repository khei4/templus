cmake_minimum_required(VERSION 3.16)
project(template-project CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_COLOR_DIAGNOSTICS ON)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
   add_compile_options (-fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
   add_compile_options (-fcolor-diagnostics)
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fsanitize=undefined,address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

option(ENABLE_WERROR "Enable -Werror options" OFF)
if (ENABLE_WERROR)
  set(CMAKE_CXX_FLAGS "-Werror ${CMAKE_CXX_FLAGS}")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)
add_subdirectory(lib)
add_subdirectory(tools)



# Testing and Benchmarking

enable_testing()
set(ALL_TESTS CACHE PATH "" FORCE)
add_subdirectory(unittests)

include(ProcessorCount)
ProcessorCount(N)
# FIXME: work filter
add_custom_target(unittests
  COMMAND ctest --test-dir ./unittests/ --output-on-failure --timeout 5 -j ${N}
  DEPENDS ${ALL_TESTS}
)

set(ALL_BENCHMARKS CACHE PATH "" FORCE)
add_subdirectory(benchmarks)


foreach(BENCH_NAME ${ALL_BENCHMARKS})
  message(STATUS "Adding benchmark-${BENCH_NAME}")
  add_custom_target(benchmark-${BENCH_NAME}
    COMMAND ${CMAKE_BINARY_DIR}/benchmarks/${BENCH_NAME}
    DEPENDS ${BENCH_NAME}
  )
endforeach()
