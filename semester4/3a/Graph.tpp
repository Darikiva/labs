//
// Created by darik on 5/18/2020.
//

#include "Graph.hpp"

template<typename Item>
Graph<Item>::Graph(const Graph<Item> &graph) { // in the case our graph consist of pointers on vertexes
    for (int i = 0; i < graph.vertex_count(); ++i) {
        _graph.push_back(std::make_shared<Graph<Item>::Vertex>(i, graph.vertex(i)->info));
        auto current_vertex = graph.vertex(i)->next;
        auto curr1 = &_graph[i];
        while (current_vertex != nullptr) {
            (*curr1)->next = std::make_shared<Graph<Item>::Vertex>(current_vertex->num, current_vertex->info,
                                                 current_vertex->weight);
            curr1 = &(*curr1)->next;
            current_vertex = current_vertex->next;
        }
        this->is_oriented = graph.is_oriented;
    }
}

template<typename Item>
bool Graph<Item>::is_connected(int i, int j) const { // check if the graph has edge ij
    if (i < 0 || j < 0 || i >= _graph.size() || j >= _graph.size()) return false;
    else {
        auto vertex = _graph[i];
        while (vertex != nullptr) {
            if (vertex->num == j) return true;
            vertex = vertex->next;
        }
    }
    return false;
}

template<typename Item>
bool Graph<Item>::add_edge(int i, int j, int weight) { // add edge ij (and ji if graph is not oriented)
    if (i < 0 || j < 0 || i >= _graph.size() || j >= _graph.size()) return false;
    std::shared_ptr<Vertex> vertex(_graph[i]);
    bool should_be_add = true;
    while (vertex->next != nullptr) {
        vertex = vertex->next;
        if (vertex->num == j) should_be_add = false;
    }
    if (should_be_add) vertex->next = std::make_shared<Vertex>(j, _graph[j]->info, weight);

    if (!is_oriented) {
        should_be_add = true;
        vertex = _graph[j];
        while (vertex->next != nullptr) {
            vertex = vertex->next;
            if (vertex->num == i) should_be_add = false;
        }
        if (should_be_add) vertex->next = std::make_shared<Vertex>(i, _graph[i]->info, weight);
    }
    return true;
}

template<typename Item>
int Graph<Item>::weight(size_t i, size_t j) const { // return weight of edge ij
    auto vertex = _graph[i];
    while (vertex->num != j && vertex != nullptr)
        vertex = vertex->next;

    if (vertex) return vertex->weight;
    else return -1;
}

template<typename Item>
void Graph<Item>::changeWeight(size_t i, size_t j, int w) {
    auto vertex = _graph[i];
    while (vertex->num != j && vertex != nullptr)
        vertex = vertex->next;
    if (vertex == nullptr) return;
    else vertex->weight = w;
}

template<typename Item>
void Graph<Item>::print() const {
    for (const auto &vertex: _graph) {
        auto curr = vertex;
        std::cout << curr->num << "[" << *curr->info << "]: ";
        curr = curr->next;
        while (curr != nullptr) {
            std::cout << curr->num << "{" << curr->weight << "}, ";
            curr = curr->next;
        }
        std::cout << std::endl;
    }
}
