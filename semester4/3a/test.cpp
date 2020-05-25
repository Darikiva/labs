//
// Created by darik on 5/18/2020.
//
#include "Graph.hpp"
#include "algorithms.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <thread>
#include <iostream>

using namespace algorithms;

TEST_CASE ("Testing graph") {
    using namespace std;
    Graph<int> graph;
    for (int i = 0; i < 10; ++i) {
        graph.add_vertex(make_shared<int>(rand() % 500));
    }
            CHECK(graph.vertex_count() == 10);
    graph.add_edge(3, 5, 10);
    graph.add_edge(1, 5, 4);
    graph.add_edge(2, 7, 1);
    graph.add_edge(5, 7, -59);
    graph.add_edge(6, 6, 0);
    graph.add_edge(9, 3, 10);
            REQUIRE(graph.is_connected(3, 5));
            REQUIRE(graph.is_connected(6, 6));
            REQUIRE(graph.weight(1, 5) == 4);
            REQUIRE(graph.weight(5, 7) == -59);
    graph.changeWeight(9, 3, 130);
            REQUIRE(graph.weight(9, 3) == 130);
}

TEST_CASE ("Testing Dijkstra algorithm") {
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
    std::vector<int> answer(dijkstra(graph));
            REQUIRE(answer == wow);
}

TEST_CASE ("Testing Ford-Bellman algorithm") {
    using namespace std;
    Graph<int> graph;
    graph.randGraph(10, 80);
    graph.print();
    CHECK(dijkstra(graph) == fordBellman(graph));
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
