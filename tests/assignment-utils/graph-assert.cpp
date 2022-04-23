#include "graph-assert.h"
#include "sample-graphs.h"

std::ostream & _assert_shortest_paths_match(std::ostream & o, std::string const & type) {
    fs::path graph_path = get_graph_path();

    std::vector<fs::path> graph_paths = get_graphs(graph_path, type);

    for(auto const & graph_path : graph_paths) {
        WeightedGraph<uint> graph = read_graph(graph_path);
        shortest_path_pairs<uint> all_paths = read_paths<uint>(graph_path);
        for(auto const & path : all_paths) {
            std::list<uint> shortest_path = dijkstrasAlgorithm(graph, path.initial_node, path.destination_node);

            if(!path.contains_shortest_path(shortest_path)) {
                o << "Graph: " << graph_path.filename() << std::endl;
                o << "Path: " << graph_path << std::endl;
                o << std::endl;

                o << "Shortest path from initial node " 
                  << path.initial_node
                  << " to destination node " 
                  << path.destination_node << std::endl;
                o << std::endl;

                o << "Dijkstra's algorithm returned path: " << std::endl;
                print_path<uint>(o, shortest_path);
                o << std::endl;

                o << std::endl;

                o << "Shortest path(s) include: " << std::endl;

                for(auto const & path : path.paths) {
                    print_path<uint>(o, path) << std::endl;
                }
                
                return o;
            }
            
        }
    }

    return o;
}