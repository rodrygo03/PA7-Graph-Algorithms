#pragma once

#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include <utility>

template <typename T>
class WeightedGraph {
public:
    using value_type = T;
    using weight_type = int;

    using vertex_type = const value_type;
    using edge_type = std::pair<vertex_type, weight_type>;
    using adjacency_list = std::unordered_map<vertex_type, weight_type>;

private:
    using container_type = std::unordered_map<vertex_type, adjacency_list>;

public:
    using size_type = typename container_type::size_type;
    
    using iterator = typename container_type::iterator;
    using const_iterator = typename container_type::const_iterator;

    using edge_iterator = typename adjacency_list::iterator;
    using const_edge_iterator = typename adjacency_list::const_iterator;

private:
    container_type graph;

public:
    WeightedGraph() = default;
    WeightedGraph(const WeightedGraph& other) = default;
    WeightedGraph(WeightedGraph&& other) = default;
    WeightedGraph& operator=(const WeightedGraph& other) = default;
    WeightedGraph& operator=(WeightedGraph&& other) = default;

    bool empty() const { return graph.empty(); }
    size_type size() const { return graph.size(); }

    const adjacency_list& at(const vertex_type& vertex) const { return graph.at(vertex); }
    
    std::pair<iterator, bool> push_vertex(const vertex_type& vertex) { return graph.insert(vertex, adjacency_list()); }

    size_type pop_vertex(vertex_type& vertex) {
        size_type retval = graph.erase(vertex);
        for (auto& [v, list] : graph) {
            (void) v; // do not use the vertex label
            retval += list.erase(vertex);
        }
        return retval;
    }

    std::pair<edge_iterator, bool> push_edge(const vertex_type& source, const vertex_type& destination, const weight_type& weight) {
        return graph.at(source).insert(std::make_pair(destination, weight));
    }

    size_type pop_edge(const vertex_type& source, const vertex_type& destination) {
        return graph.at(source).erase(destination);
    }

    iterator begin() { return graph.begin(); }
    const_iterator begin() const { return graph.begin(); }

    iterator end() { return graph.end(); }
    const_iterator end() const { return graph.end(); }

    edge_iterator begin(const vertex_type& vertex) { return graph.at(vertex).begin(); }
    const_edge_iterator begin(const vertex_type& vertex) const { return graph.at(vertex).begin(); }

    edge_iterator end(const vertex_type& vertex) { return graph.at(vertex).end(); }
    const_edge_iterator end(const vertex_type& vertex) const { return graph.at(vertex).end(); }

    void clear() { graph.clear(); }

};