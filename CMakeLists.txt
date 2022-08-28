cmake_minimum_required(VERSION 3.23)
project(classic-algos)

set(CMAKE_CXX_STANDARD 17)

add_executable(manacher Manacher/manacher.cpp)
add_executable(kmp KMP/kmp.cpp)
add_executable(merge_sort MergeSort/merge_sort.cpp)
add_executable(union_find_set UnionFindSet/union_find_set.cpp)
add_executable(sparse_graph_dijkstra Dijkstra/sparse_graph_dijkstra.cpp)