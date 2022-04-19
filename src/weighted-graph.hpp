#pragma once

#include <list>
#include <unordered_map>
#include <utility>

template <typename T>
class WeightedGraph {
public:
    using value_type = T;
    using size_type = size_t;
    using weight_type = int;

    using edge_type = std::pair<T, weight_type>;
    using adjacency_list = std::list<edge_type>;

    using iterator = typename std::unordered_map<value_type, std::list<edge_type>>::iterator;
    using const_iterator = typename std::unordered_map<value_type, std::list<edge_type>>::const_iterator;
private:
    std::unordered_map<value_type, adjacency_list> graph;
public:
    WeightedGraph() = default;
    WeightedGraph(const WeightedGraph& other) = default;
    WeightedGraph(WeightedGraph&& other) = default;
    WeightedGraph& operator=(const WeightedGraph& other) = default;
    WeightedGraph& operator=(WeightedGraph&& other) = default;

    bool empty() const { return graph.empty(); }
    size_type size() const { return graph.size(); }
    
    std::pair<iterator, bool> push_vertex(const T& vertex) { return graph.insert(vertex, adjacency_list{}); }
    std::pair<iterator, bool> push_vertex(T&& vertex) { return graph.insert(vertex, adjacency_list{}); }

    void clear() { graph.clear(); }

};