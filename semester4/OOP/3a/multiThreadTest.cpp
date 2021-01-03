//
// Created by darik on 5/25/2020.
//

#include "Graph.hpp"
#include "multiTheadAlgorithms.hpp"

//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <thread>
#include <iostream>

using namespace mAlgorithms;

TEST_CASE("Testing mDijkstra") {
    using namespace std;
    Graph<int> graph;
    for (int i = 0; i < 6; ++i) {
        graph.add_vertex(make_shared<int>(rand() % 50));
    }
    graph.add_edge(0, 1, 7);
    graph.add_edge(1, 3, 15);
    graph.add_edge(3, 4, 6);
    graph.add_edge(4, 5, 9);
    graph.add_edge(0, 5, 14);
    graph.add_edge(0, 2, 9);
    graph.add_edge(2, 5, 2);
    graph.add_edge(2, 3, 11);
    graph.add_edge(1, 2, 10);
    std::vector<int> wow({0, 7, 9, 20, 20, 11});
            REQUIRE(dijkstra(graph).get() == wow);
}

TEST_CASE("Testing Johnson algorithm") {
    using namespace std;
    Graph<int> graph(true);
    for (int i = 0; i < 4; ++i) {
        graph.add_vertex(make_shared<int>(rand()%500));
    }
    graph.add_edge(0, 1, 21);
    graph.add_edge(0, 3, 3);
    graph.add_edge(3, 2, 5);
    graph.add_edge(2, 0, -3);
    graph.add_edge(1, 2, -17);
    vector<vector<int> > right_answer({{0, 21, 4, 3},
                                       {-20, 0, -17, -17},
                                       {-3, 18, 0, 0},
                                       {2, 23, 5, 0}});
            CHECK(johnson(graph) == right_answer);
}
