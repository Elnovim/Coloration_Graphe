cmake_minimum_required(VERSION 2.6)
project(coloration_graphe)

add_definitions(-std=c++1y -ggdb -O3)
add_executable(coloration_graphe Noeud.cpp Graphe.cpp Moteur.cpp main.cpp)

install(TARGETS coloration_graphe RUNTIME DESTINATION bin)

SET(CMAKE_CXX_FLAGS "-std=c++1y")
