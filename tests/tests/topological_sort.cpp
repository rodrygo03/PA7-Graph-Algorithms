#include "executable.h"

TEST(gnp_dag) {
    fs::path graph_path = get_graph_path();
    std::vector<fs::path> graph_paths = get_graphs(graph_path, "gnp_dag");

    for(auto const & graph_path : graph_paths) {
        WeightedGraph<uint> graph = read_graph(graph_path);
        // TODO
    }
}