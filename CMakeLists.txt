cmake_minimum_required(VERSION 3.23)
project(classic-algos)

set(CMAKE_CXX_STANDARD 17)

add_executable(manacher src/Manacher/manacher.cpp)
add_executable(kmp src/KMP/kmp.cpp)
add_executable(merge_sort src/MergeSort/merge_sort.cpp)
add_executable(union_find_set src/UnionFindSet/union_find_set.cpp)
add_executable(sparse_graph_dijkstra src/Dijkstra/sparse_graph_dijkstra.cpp)
add_executable(binary_indexed_tree src/BinaryIndexedTree/binary_indexed_tree.cpp)