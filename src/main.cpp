#include <fstream>
#include <iostream>

#include "weighted-graph.hpp"
#include "graph-algorithms.h"

#define GRAPH_TEXT \
"1: 2(4) → 4(3) → 5(3)\n" \
"2: 3(3) → 4(3) → 7(6)\n" \
"3: 4(1)\n" \
"4: 6(6) → 7(8)\n" \
"5:\n" \
"6: 5(5)\n" \
"7: 6(6)"

template <typename T>
void getGraph(WeightedGraph<T>& graph, int argc, char* argv[]) {
    if (argc < 2) {
        std::istringstream(GRAPH_TEXT) >> graph;
    } else {
        std::ifstream(argv[1]) >> graph;
    }
}

int main(int argc, char* argv[]) {
    WeightedGraph<int> graph; // most input files
    // WeightedGraph<std::string> graph; // inputCourses.dat

    getGraph(graph, argc, argv);

    std::cout << graph << std::endl;
}
