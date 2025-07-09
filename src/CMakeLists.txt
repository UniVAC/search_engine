cmake_minimum_required(VERSION 3.25)

include(FetchContent)

option(FOO_USE_EXTERNAL_JSON "Use an external JSON library" OFF)

set(JSON_BuildTests OFF CACHE INTERNAL "")
FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.12.0
        )
FetchContent_MakeAvailable(json)

configure_file(${CMAKE_SOURCE_DIR}/config/config.json ${CMAKE_CURRENT_BINARY_DIR})
configure_file(${CMAKE_SOURCE_DIR}/config/requests.json ${CMAKE_CURRENT_BINARY_DIR})

add_executable(search_engine
                main.cpp
                converterjson.cpp
                invertedindex.cpp
                searchserver.cpp)

target_include_directories(search_engine PUBLIC ${INCLUDE_DIR})

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)