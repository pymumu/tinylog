cmake_minimum_required(VERSION 2.8)
project(example)

include_directories(../)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DBASE_FILE_NAME='\"$(notdir $<)\"'")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DBASE_FILE_NAME='\"$(notdir $<)\"'")

add_executable(example example.cpp ../tlog.c)
target_link_libraries(example pthread)
