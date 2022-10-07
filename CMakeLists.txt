cmake_minimum_required(VERSION 3.20)
project(TP5_Algo_Kruskal_Prim C)

set(CMAKE_C_STANDARD 99)

add_executable(TP5_Algo_Kruskal_Prim main.c Graphe/Graphe.c Graphe/Graphe.h Kruskal/kruskal.c Kruskal/kruskal.h Prim/prim.c Prim/prim.h)
