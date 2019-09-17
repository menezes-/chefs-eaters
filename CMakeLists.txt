cmake_minimum_required(VERSION 3.14)
project(cannibals)


add_executable(cannibals main.cpp Travessa.cpp Travessa.hpp Mutex.cpp Mutex.hpp Randomer.hpp)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
target_link_libraries(cannibals Threads::Threads)

target_compile_features(cannibals PRIVATE cxx_auto_type )
