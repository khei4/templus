file(GLOB COMMON_SOURCES CONFIGURE_DEPENDS *.cpp)
add_library(com SHARED ${COMMON_SOURCES})
target_include_directories(com PUBLIC ${PROJECT_SOURCE_DIR}/include)

file(GLOB SUB_SOURCES CONFIGURE_DEPENDS Sub/*.cpp)
add_library(hoge SHARED ${SUB_SOURCES})
target_link_libraries(hoge com)
target_include_directories(hoge PUBLIC ${PROJECT_SOURCE_DIR}/include)