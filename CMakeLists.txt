cmake_minimum_required(VERSION 3.27.6)
project(search_engine VERSION 0.1.0)

include(CTest)

enable_testing()

add_executable(search_engine main.cpp working_with_json.h working_with_json.cpp)

set(JSON_BuildTests OFF CACHE INTERNAL "")
set(Boost_INCLUDE_DIR "D:\\boost_1_83_0")
set(Boost_LIBRARY_DIR "D:\\boost_1_83_0\\stage\\lib")
find_package(Boost COMPONENTS REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_libraries(${Boost_LIBRARY_DIR})


add_subdirectory(nlohmann_json)
target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json ${Boost_LIBRARIES} ws2_32)