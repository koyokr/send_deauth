cmake_minimum_required(VERSION 2.6)
project(send_deauth CXX)

find_library(TINS_LIBRARY tins)
set(CMAKE_CXX_STANDARD 14)

set(PTHREAD_LINK_LIBRARIES -pthread)
add_compile_options(${PTHREAD_LINK_LIBRARIES})

add_executable(send_deauth main.cpp)
target_link_libraries(send_deauth ${TINS_LIBRARY} ${PTHREAD_LINK_LIBRARIES})
