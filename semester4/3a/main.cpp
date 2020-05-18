#include "FibonacciHeap.hpp"
#include "Graph.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>
//#include <thread>
#include <chrono>
#include "catch.hpp"


using std::shared_ptr;
using std::vector;
using std::make_shared;
using namespace std::chrono;


bool operator<(const std::pair<int, int> lhs, const std::pair<int, int> rhs) {
    return (lhs.first < rhs.first);
}

template<typename Item>
std::vector<int> dijkstra(Graph<Item> &graph, int index = 0) {
    std::cout << "F";
    if (graph.vertex_count() <= 0) return {};

    std::vector<int> answer(graph.vertex_count());
    std::vector<bool> visited(graph.vertex_count()); // to avoid visiting vertexes, that were visited already
    for (int i = 0; i < graph.vertex_count(); i++) {
        answer[i] = -1;
        visited[i] = false;
    }
    answer[index] = 0;
    FibonacciHeap<std::pair<int, int>> heap;
    std::vector<FibonacciHeap<std::pair<int, int>>::Node *> nodes(graph.vertex_count()); // keep pointers for nodes in
    // the heap
    nodes[index] = heap.insert(std::make_pair(0, index));

    visited[index] = true; // we started with vertex index
    while (!heap.isEmpty()) { // while not visited all vertex that can be reached
        auto current_vertex = heap.getMin(); // visit the vertex with min way at the current moment
        heap.extractMin();
        nodes[current_vertex.second] = nullptr;
        answer[current_vertex.second] = current_vertex.first;
        auto curr = graph.vertex(current_vertex.second)->next;
        std::cout << "FSDFSDFSDFDSFSFEJIJFWEF" << std::endl;
        while (curr != nullptr) { // relaxation egdes that started with this vertex
            int new_dist = current_vertex.first + curr->weight;
            if (!visited[curr->num]) {
                visited[curr->num] = true;

                std::cout << "!!!" << curr->num << "!!!" << nodes.size() << std::endl;
             //   nodes[curr->num] = heap.insert(std::make_pair(new_dist, curr->num));
                //heap.insert(std::make_pair(new_dist, curr->num));
                nodes[curr->num] = heap.insert(std::make_pair(new_dist, curr->num));
            } else {
                heap.decrease(nodes[curr->num], std::make_pair(new_dist, curr->num));
            }
            curr = curr->next;
        }
    }
    return answer;
}

template<typename Item>
bool fordBellman(Graph<Item> &graph, int index, std::vector<int> &answer) {
    answer.resize(graph.vertex_count());
    for (auto &i: answer) i = 1;
    answer[index] = 0;
    for (int i = 0; i < graph.vertex_count(); ++i) {
        for (int j = 0; j < graph.vertex_count(); ++j) {
            auto current_vertex = graph.vertex(j);
            auto curr = current_vertex->next;
            while (curr != nullptr) {
                if (answer[curr->num] > answer[current_vertex->num] + curr->weight) // method of relaxation
                    answer[curr->num] = answer[current_vertex->num] + curr->weight;
                curr = curr->next;
            }
        }
    }


    for (int j = 0; j < graph.vertex_count(); ++j) { // check for existence of negative cycle
        auto current_vertex = graph.vertex(j);
        auto curr = current_vertex->next;
        while (curr != nullptr) {
            if (answer[curr->num] > answer[current_vertex->num] + curr->weight) {
                return false;
            }
            curr = curr->next;
        }
    }

    return true;
}

template<typename Item>
std::vector<std::vector<std::pair<int, int>>> johnson(const Graph<Item>& graph) {
    std::vector<std::vector<std::pair<int, int>>> answer;

    Graph<Item> new_graph = graph;

    new_graph.add_vertex(nullptr);
    for (int i = 0; i < graph.vertex_count(); ++i) {
        new_graph.add_edge(graph.vertex_count(), i, 0); // add zero vertex
    }


    std::vector<int> v;
    if (!fordBellman(new_graph, graph.vertex_count(), v)) {
        std::cout << "Has negative cycle" << std::endl;
        return {{}};
    } else {
        Graph<Item> last_graph = graph; // graph for reweighting
        for (int i = 0; i < last_graph.vertex_count(); ++i) { // process of reweighting
            for (int j = i + 1; j < last_graph.vertex_count(); ++j) {
                if (last_graph.is_connected(i, j)) {
                    last_graph.changeWeight(i, j, last_graph.weight(i, j) + v[i] - v[j]);
                }
                if (last_graph.is_connected(j, i)) {
                    last_graph.changeWeight(j, i, last_graph.weight(j, i) + v[j] - v[i]);
                }
            }
        }


        for (int i = 0; i < last_graph.vertex_count(); ++i) {
            std::cout << std::endl << "!!!!!!!!" << i << "!!!!!!!!!!!";
            auto tmp = dijkstra(last_graph, i);
            std::vector<std::pair<int, int>> for_ans;
            for (auto j = 0; j < tmp.size(); ++j) {
                if (tmp[j] != -1) for_ans.push_back(std::make_pair(j, tmp[j] + v[j] - v[i])); // restoring weights
            }
            std::cout << std::endl << "!!!!!!!!" << i << "!!!!!!!!!!!";
            answer.push_back(for_ans);
        }
    }

    return answer;
}


int main() {
    Graph<int> graph;
    graph.randGraph(10, 40);
    graph.print();
    std::cout << std::endl << "WRGSD";
    std::cout << "WTF";
    auto k = johnson(graph);
    std::cout << "WTF" << k.size();
    for (auto i = 0; i < k.size(); ++i) {
        std::cout << i << ": ";
        for (const auto &element: k[i]) {
            std::cout << element.first << "{" << element.second << "} ";
        }
        std::cout << std::endl;
    };
    return 0;
}
