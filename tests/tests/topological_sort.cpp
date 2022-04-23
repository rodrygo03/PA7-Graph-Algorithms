#include "executable.h"

TEST(gnp_dag) {
    fs::path graph_path = get_graph_path();
    std::vector<fs::path> graph_paths = get_graphs(graph_path, "gnp_dag");
    
    for(auto const & graph_path : graph_paths) {
        WeightedGraph<uint> graph = read_graph(graph_path);
        std::unordered_set<uint> visited;
        auto sorted_graph = topologicalSort(graph);
        for(auto vertex: sorted_graph) {
            visited.insert(vertex);
            for(auto adjacent_vertex_weight_pair: graph.at(vertex)) {
                // for some reason ASSERT_EQ doesn't compile here
                ASSERT_TRUE(visited.end() == visited.find(adjacent_vertex_weight_pair.first));
            }
        }
    }
}