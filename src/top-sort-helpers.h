#pragma once

#include <unordered_map>

#include "weighted-graph.hpp"
#include "graph-types.h"

template <typename T>
void computeIndegrees(const WeightedGraph<T>& graph, std::unordered_map<value_type<T>, int>& indegrees) {
    // TODO store the indegree for each vertex in the graph in the indegrees map
    using const_itr = typename WeightedGraph<T>::const_iterator;
    for (const_itr i=graph.begin(); i!=graph.end(); i++)    {
        indegrees[i->first] = 0;
    }

   
    using edge_itr = typename WeightedGraph<T>::const_edge_iterator;
    const_itr i = graph.begin();
    while (i != graph.end())    {
        for (edge_itr j= i->second.begin(); j!=i->second.end(); j++)    {
            indegrees[j->first] += 1;
        }
        i++;
    }
}
