enable_testing()

include(FetchContent)
if(${CMAKE_VERSION} VERSION_LESS "3.25")
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
else()
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)
endif()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)
add_subdirectory(Sub)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/unittests)
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS *.cpp)
foreach(TEST_SRC ${TEST_SOURCES})
    
    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)
    
    add_executable(${TEST_NAME} ${TEST_SRC})
    target_link_libraries(${TEST_NAME} GTest::gtest_main com)
    target_include_directories(${TEST_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
    
    list(APPEND ALL_TESTS ${TEST_NAME})

    gtest_discover_tests(${TEST_NAME})
endforeach()

set(ALL_TESTS ${ALL_TESTS} PARENT_SCOPE)