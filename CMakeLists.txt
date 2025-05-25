cmake_minimum_required(VERSION 3.31)
project(DijkstraShortestPath)

set(CMAKE_CXX_STANDARD 23)

add_executable(DijkstraShortestPath src/main.cpp
        include/Stack.h
        include/MinHeap.h
        include/Graph.h)
