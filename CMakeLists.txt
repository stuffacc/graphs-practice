cmake_minimum_required(VERSION 3.31)

project(graphs C)

add_library(graph graph.c)
add_library(queue queue.c)

add_executable(graphs main.c)

target_link_libraries(graphs PRIVATE graph)
target_link_libraries(graphs PRIVATE queue)