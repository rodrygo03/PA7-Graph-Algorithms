#pragma once

#include <istream>
#include <ostream>
#include <sstream>
#include <list>
#include <string>
#include "weighted-graph.hpp"

// if the arrow is a box, change to the other line
#define ARROW_SEPARATOR " \u2192 "
// #define ARROW_SEPARATOR " -> "

template <typename T>
using vertex_type = typename WeightedGraph<T>::vertex_type;
template <typename T>
using weight_type = typename WeightedGraph<T>::weight_type;
template <typename T>
using adjacency_list = typename WeightedGraph<T>::adjacency_list;

/**
 * @brief Dijkstra's Algorithm - https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm#Algorithm
 * 
 * @tparam T type of data stored by a vertex
 * @param graph weighted, directed graph to find single-source shortest-path
 * @param initial_node source node in graph for shortest path
 * @param destination_node destination node in graph for shortest path
 * @return std::list<vertex_type<T>> list of nodes along shortest path including initial_node and destination_node, empty if no path exists
 */
template <typename T>
std::list<vertex_type<T>> dijkstrasAlgorithm(const WeightedGraph<T> graph, vertex_type<T> initial_node, vertex_type<T> destination_node) {
    // TODO
    return std::list<vertex_type<T>>();
}

/**
 * @brief Returns a Topological Ordering of the Graph - https://en.wikipedia.org/wiki/Topological_sorting#Depth-first_search
 * 
 * @tparam T type of data stored by a vertex
 * @param graph graph upon which to perform a topological ordering
 * @return std::list<vertex_type<T>> list of nodes in a topological order, or an empty list if no such ordering exists
 */
template <typename T>
std::list<vertex_type<T>> topologicalSort(const WeightedGraph<T> graph) {
    // TODO
    return std::list<vertex_type<T>>();
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
            o << destination << "(" << weight << ')';
            auto next_iter = iit;
            if (++next_iter != list.end()) {
                o << ARROW_SEPARATOR;
            }
        }
        auto next_iter = it;
        if (++next_iter != graph.end()) {
            o << "\n";
        }
    }
    return o;
}

template <typename T>
std::istream& operator>>(std::istream& i, WeightedGraph<T>& graph) {
    using value_type = typename WeightedGraph<T>::value_type;

    std::string line;
    while (std::getline(i, line)) {
        if (line.empty()) continue;
        std::istringstream line_stream(line);
        value_type vertex;
        line_stream >> vertex;
        if (line_stream.fail()) {
            i.setf(line_stream.flags());
            break;
        }
        graph.push_vertex(vertex);
        value_type edge_end;
        weight_type<T> edge_weight;
        while (line_stream >> edge_end >> edge_weight) {
            graph.push_edge(vertex, edge_end, edge_weight);
        }
    }
    return i;
}
