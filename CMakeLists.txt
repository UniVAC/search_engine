cmake_minimum_required(VERSION 3.25)
project(search_engine)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(gtest_disable_pthreads on)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(nlohmann_json)

add_executable(
        search_engine
        main.cpp
        converterjson.cpp
        invertedindex.cpp
        searchserver.cpp
)
target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)

add_executable(
        my_tests
        tests.cpp
        converterjson.cpp
        invertedindex.cpp
        searchserver.cpp
)
target_link_libraries(my_tests PRIVATE gtest_main nlohmann_json::nlohmann_json)

include(GoogleTest)
gtest_discover_tests(my_tests)