//
// Created by darik on 5/18/2020.
//

#ifndef INC_3A_GRAPH_HPP
#define INC_3A_GRAPH_HPP

#include <memory>
#include <vector>
#include <iostream>

template<typename Item>
class Graph {
public:

    class Vertex {
    public:
        int num;
        std::shared_ptr<Item> info;
        std::shared_ptr<Vertex> next;
        int weight;

        Vertex(int num, std::shared_ptr<Item> info, int weight = 0, std::shared_ptr<Vertex> next = nullptr) :
                num{num}, info{info}, weight{weight}, next{next} {}
    };


    std::vector<std::shared_ptr<Vertex>> _graph;
    bool is_oriented{false};

    Graph<Item>() = default;

    Graph<Item>(bool is_oriented) : is_oriented{is_oriented} {}

    Graph<Item>(const Graph<Item> &graph); // in the case our graph consist of pointers on vertexes

    bool is_connected(int i, int j) const; // check if the graph has edge ij

    bool add_edge(int i, int j, int weight = 1); // add edge ij (and ji if graph is not oriented)

    inline auto vertex_count() const {
        return _graph.size();
    }

    inline void add_vertex(std::shared_ptr<Item> data) {
        _graph.push_back(std::make_shared<Vertex>(vertex_count(), data));
    }

    inline std::shared_ptr<Vertex> vertex(size_t index) const {
        return _graph[index];
    }

    int weight(size_t i, size_t j) const; // return weight of edge ij

    void changeWeight(size_t i, size_t j, int w);

    void randGraph(int size, int edges) {
        for (int i = 0; i < size; ++i) {
            add_vertex(std::make_shared<Item>());
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (rand() % 2) {
                    add_edge(i, j, rand() % 10 + 1);
                    edges--;
                    if (edges == 0) return;
                }
            }
        }
        if (edges > 0) {
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (!is_connected(i, j)) {
                        add_edge(i, j, rand() % 10 + 1);
                        edges--;
                        if (edges == 0) return;
                    }
                }
            }
        }
    }

    void print() const;
};

// create graph with size vertexes that randomly connected with random weight
// number of edges is in the variable 'edges'
// info in vertexes is created by default
#include "Graph.tpp"

#endif //INC_3A_GRAPH_HPP
