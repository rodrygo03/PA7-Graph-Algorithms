#pragma once

#include <list>
#include "weighted-graph.hpp"

template <typename T>
using vertex_type = typename WeightedGraph<T>::vertex_type;

template <typename T>
using weight_type = typename WeightedGraph<T>::weight_type;

template <typename T>
using adjacency_list = typename WeightedGraph<T>::adjacency_list;

/**
 * @brief 
 * 
 * @tparam T - Type of vertices in graph, usually int
 * @param graph - Graph to find Dijkstra's algorithm
 * @return std::list<typename WeightedGraph<T>::vertex_type> 
 */
template <typename T>
std::list<vertex_type<T>> dijkstrasAlgorithm(const WeightedGraph<T> graph, vertex_type<T> initial_node) {
    
}

template <typename T>
std::list<typename WeightedGraph<T>::vertex_type> topologicalSort(const WeightedGraph<T> graph) {
    
}

template <typename T>
std::ostream& operator<<(std::ostream& o, const WeightedGraph<T>& graph) {
    for (auto it = graph.begin(); it != graph.end(); ++it) {
        const vertex_type<T>& vertex = it->first;
        const adjacency_list<T>& list = it->second;
        o << vertex << ": ";
        for (auto iit = list.begin(); iit != list.end(); ++iit) {
            const vertex_type<T>& destination = iit->first;
            const weight_type<T>& weight = iit->second;
            o << '(' << destination << ", w: " << weight << ')';
            auto next_iter = iit;
            if (++next_iter != list.end()) {
                o << ", ";
            }
        }
        auto next_iter = it;
        if (++next_iter != graph.end()) {
            o << "\n";
        }
    }
}