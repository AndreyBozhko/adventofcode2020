cmake_minimum_required(VERSION 3.17)
project(adventofcode)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Werror")

file(GLOB srcs *.cpp)
file(GLOB hdrs *.h)
file(GLOB inputs inputs/*.txt)

add_executable(adventofcode ${hdrs} ${srcs} ${inputs})

file(COPY inputs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
