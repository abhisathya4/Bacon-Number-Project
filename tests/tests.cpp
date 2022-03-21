#include "../cs225/catch/catch.hpp"

#include "../graph.h"

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <utility>

using namespace std;

/** Constructor Test(s) */
TEST_CASE("Graph: Constructor - Num Nodes", "[graph_ctor]") {
    Graph imdbgraph("tests/data/constructor_data.csv");
    
    REQUIRE(imdbgraph.size() == 6);

    ifstream nodes("tests/data/constructor_nodes.csv");
    string actor;
    vector<string> actor_list_file;
    vector<string> actor_list_graph;
    
    while (getline(nodes, actor)) {
        actor_list_file.push_back(actor);
    }

    for (auto pair : imdbgraph.get_unordered_map()) {
        actor_list_graph.push_back(pair.first);
    }
    sort(actor_list_file.begin(), actor_list_file.end());
    sort(actor_list_graph.begin(), actor_list_graph.end());
    REQUIRE(actor_list_graph == actor_list_file);
}

/** BFS Tests */
TEST_CASE("Testing BFS Small - One Hop","[traversals][bfs]") {
    Graph imdbgraph_small("tests/data/small_data.csv");
    vector<Graph::Connection> bfs = imdbgraph_small.BFS("NodeA","NodeF");
      
    REQUIRE(bfs.size() == 1);
    vector<Graph::Connection> bfs_required;
    Graph::Connection con_1;
    con_1.name = "NodeA";
    con_1.destination = "NodeF";
    con_1.rating = 7.8;
    con_1.title = "EdgeAF";
    bfs_required.push_back(con_1);

    REQUIRE(bfs == bfs_required);
}
TEST_CASE("Testing BFS Small - Multiple Hops","[bfs]") {
    Graph imdbgraph_small("tests/data/small_data.csv");
    vector<Graph::Connection> bfs = imdbgraph_small.BFS("NodeB","NodeF");
      
    REQUIRE(bfs.size() == 2);
 }

TEST_CASE("Testing BFS Medium - Single Path","[bfs]") {
    Graph imdbgraph_medium("tests/data/medium_data.csv");
    vector<Graph::Connection> bfs1 = imdbgraph_medium.BFS("Node3","Node11");
    vector<Graph::Connection> bfs2 = imdbgraph_medium.BFS("Node7","Node12");

    REQUIRE(bfs1.size() == 3);
    REQUIRE(bfs2.size() == 5);
}
TEST_CASE("Testing BFS Medium - Multiple Paths","[bfs]") {
    Graph imdbgraph_medium("tests/data/medium_data.csv");
    vector<Graph::Connection> bfs1 = imdbgraph_medium.BFS("Node1","Node7");
    vector<Graph::Connection> bfs2 = imdbgraph_medium.BFS("Node12","Node10");

    REQUIRE(bfs1.size() == 4);
    REQUIRE(bfs2.size() == 5);
}
TEST_CASE("Testing BFS Small - Unconnected","[bfs]") {
    Graph imdbgraph_small_unconnected("tests/data/small_unconnected_data.csv");
    vector<Graph::Connection> bfs = imdbgraph_small_unconnected.BFS("NodeA","NodeI");

    REQUIRE(bfs.size() == 0);
}
TEST_CASE("Testing BFS Symmetric -> (Node1--Node2 == Node2--Node1)","[traversals][bfs]") {
    Graph imdbgraph_small("tests/data/small_data.csv");
    vector<Graph::Connection> bfs1 = imdbgraph_small.BFS("NodeA","NodeD");
    vector<Graph::Connection> bfs2 = imdbgraph_small.BFS("NodeD","NodeA");

    REQUIRE(bfs1.size() == bfs2.size());

    Graph imdbgraph_medium("tests/data/medium_data.csv");
    vector<Graph::Connection> bfs3 = imdbgraph_medium.BFS("Node1","Node11");
    vector<Graph::Connection> bfs4 = imdbgraph_medium.BFS("Node11","Node1");

    REQUIRE(bfs3.size() == bfs4.size());
}
 
/** Dijkstras Tests */
TEST_CASE("Testing Dijkstras Small - Least Hops Path","[dijkstras]") {
    Graph imdbgraph_small("tests/data/small_data.csv");
    vector<Graph::Connection> dij = imdbgraph_small.dijkstras("NodeA","NodeE");

    float path_rating = 0;
    for ( Graph::Connection connection : dij) {
        path_rating += connection.rating;
    }
        
    REQUIRE(fabs(path_rating - 16) < 0.0001);

}
TEST_CASE("Testing Dijkstras Small - Paths Have Equal Hops, Prefer Higher Rating","[dijkstras]") {
    Graph imdbgraph_small("tests/data/small_data_dijkstras.csv");
    vector<Graph::Connection> dij = imdbgraph_small.dijkstras("NodeA","NodeE");

    float path_rating = 0;
    for ( Graph::Connection connection : dij) {
        path_rating += connection.rating;
    }
    
    REQUIRE(fabs(path_rating - 16.1) < 0.0001);
}
TEST_CASE("Testing Dijkstras Medium - One Hop","[dijkstras]") {
    Graph imdbgraph_medium("tests/data/medium_data_dijkstras.csv");
    vector<Graph::Connection> dij = imdbgraph_medium.dijkstras("Node6","Node8");

    float path_rating = 0;
    for ( Graph::Connection connection : dij) {
        path_rating += connection.rating;
    }
    REQUIRE(fabs(path_rating - 7.2) < 0.0001);
}
TEST_CASE("Testing Dijkstras Medium - Paths Have Equal Hops, Prefer Higher Rating","[dijkstras]") {
    Graph imdbgraph_medium("tests/data/medium_data.csv");
    vector<Graph::Connection> dij = imdbgraph_medium.dijkstras("Node1","Node7");

    float path_rating = 0;
    for ( Graph::Connection connection : dij) {
        path_rating += connection.rating;
    }
        
        REQUIRE(fabs(path_rating - 33.3) < 0.0001);
}
TEST_CASE("Testing Dijkstras Medium - Paths Have Equal Hops, Prefer Higher Rating Symmetric","[dijkstras]") {
    Graph imdbgraph_medium("tests/data/medium_data.csv");
    vector<Graph::Connection> dij = imdbgraph_medium.dijkstras("Node7","Node1");

    float path_rating = 0;
    for ( Graph::Connection connection : dij) {
        path_rating += connection.rating;
    }
        
    REQUIRE(fabs(path_rating - 33.3) < 0.0001);
}
TEST_CASE("Testing Dijkstras Medium - Least Hops Low Ratings, Prefer More Hops Better Rating","[dijkstras]") {
    Graph imdbgraph_medium("tests/data/medium_data_dijkstras.csv");
    vector<Graph::Connection> dij = imdbgraph_medium.dijkstras("Node2","Node3");

    float path_rating = 0;
    for ( Graph::Connection connection : dij) {
        path_rating += connection.rating;
    }

    REQUIRE(dij.size() == 7);
    REQUIRE(fabs(path_rating - 61.3) < 0.0001);
}
TEST_CASE("Testing Dijkstras Medium - Prefer More Hops Better Rating Symmetric","[dijkstras]") {
    Graph imdbgraph_medium("tests/data/medium_data_dijkstras.csv");
    vector<Graph::Connection> dij = imdbgraph_medium.dijkstras("Node3","Node2");

    float path_rating = 0;
    for ( Graph::Connection connection : dij) {
        path_rating += connection.rating;
    }

    REQUIRE(dij.size() == 7);
    REQUIRE(fabs(path_rating - 61.3) < 0.0001);
}
TEST_CASE("Testing Dijkstras Medium - Bypass Direct Edge Due To Low Rating","[dijkstras]") {
    Graph imdbgraph_medium("tests/data/medium_data_dijkstras.csv");
    vector<Graph::Connection> dij = imdbgraph_medium.dijkstras("Node8","Node9");

    float path_rating = 0;
    for ( Graph::Connection connection : dij) {
        path_rating += connection.rating;
    }
    REQUIRE(fabs(path_rating - 17) < 0.0001);
}
TEST_CASE("Testing Dijkstras Medium - Bypass Direct Edge Symmetric","[dijkstras]") {
    Graph imdbgraph_medium("tests/data/medium_data_dijkstras.csv");
    vector<Graph::Connection> dij = imdbgraph_medium.dijkstras("Node9","Node8");

    float path_rating = 0;
    for ( Graph::Connection connection : dij) {
        path_rating += connection.rating;
    }
    REQUIRE(fabs(path_rating - 17) < 0.0001);
}

/**Brandes' Betweenness Centrality Tests */
TEST_CASE("Testing Brandes' - Graph Small","[brandes]") {
    Graph imdbgraph_small("tests/data/small_data_brandes.csv");
    pair<string, float> node_name = imdbgraph_small.brandes();

    REQUIRE(node_name.first == "NodeA");
}
TEST_CASE("Testing Brandes' - Two Central Nodes, Other Have Equal Centrality","[brandes]") {
    Graph imdbgraph_sym("tests/data/sym_data_brandes.csv");
    pair<string, float> node_name = imdbgraph_sym.brandes();

    REQUIRE((node_name.first == "NodeC" || node_name.first == "NodeD"));
}
TEST_CASE("Testing Brandes' - Two Central Nodes, Nodes Have Different Centrality","[brandes]") {
    Graph imdbgraph_asym("tests/data/asym_data_brandes.csv");
    pair<string, float>  node_name = imdbgraph_asym.brandes();

    REQUIRE((node_name.first == "NodeB" || node_name.first == "NodeC"));
}
TEST_CASE("Testing Brandes' - Graph Small Unconnected","[brandes]") {
    Graph imdbgraph_small("tests/data/small_unconnected_data_brandes.csv");
    pair<string, float>  node_name = imdbgraph_small.brandes();

    REQUIRE(node_name.first == "NodeE");
}

