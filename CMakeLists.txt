cmake_minimum_required(VERSION 3.27.6)
project(search_engine VERSION 0.1.0)

include(CTest)

enable_testing()

add_executable(search_engine main.cpp working_with_json.h working_with_json.cpp)

set(JSON_BuildTests OFF CACHE INTERNAL "")


add_subdirectory(nlohmann_json)
target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)

include(GoogleTest)
gtest_discover_tests(search_engine)