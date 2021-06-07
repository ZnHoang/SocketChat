cmake_minimum_required(VERSION 2.8)

project(server)

add_compile_options(-std=c++2a)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

aux_source_directory(src SRC_LIST)

include_directories(include)

set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

add_executable(server ${SRC_LIST})

set(THREADS_PREFER_FLAG ON)

find_package(Threads REQUIRED)

target_link_libraries(
    server PUBLIC Threads::Threads 
)
