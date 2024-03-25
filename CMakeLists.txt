cmake_minimum_required(VERSION 3.27.6)
project(search_engine VERSION 0.1.0)

include(CTest)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

enable_testing()

add_executable(search_engine main.cpp working_with_json.h working_with_json.cpp)

set(gtest_disable_pthreads ON)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(JSON_BuildTests OFF CACHE INTERNAL "")


add_subdirectory(nlohmann_json)
target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json gtest_main)

include(GoogleTest)
gtest_discover_tests(search_engine)