cmake_minimum_required(VERSION 3.25)

project(my_tests)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(my_tests
        tests.cpp
        ${CMAKE_SOURCE_DIR}/src/converterjson.cpp
        ${CMAKE_SOURCE_DIR}/src/invertedindex.cpp
        ${CMAKE_SOURCE_DIR}/src/searchserver.cpp)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(gtest_disable_pthreads on)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

target_include_directories(search_engine PUBLIC ${gtest_SOURCE_DIR}/include ${INCLUDE_DIR})

target_link_libraries(search_engine PRIVATE gtest_main)