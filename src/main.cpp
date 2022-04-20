#include <iostream>

#include "weighted-graph.hpp"
#include "graph-algorithms.h"

#define GRAPH_TEXT \
"1 2 4 5\n" \
"2 3 4 7\n" \
"3 4\n" \
"4 6 7\n" \
"5\n" \
"6 5\n" \
"7 6\n" \

int main() {
    WeightedGraph<int> intGraph;

    std::string graphText =
    "1 2 10 3 20 5 30\n"
    "2 4 40\n"
    "3\n"
    "4\n"
    "5\n";

    std::istringstream graphStream(graphText);

    graphStream >> intGraph;

    std::cout << intGraph << std::endl;
}
