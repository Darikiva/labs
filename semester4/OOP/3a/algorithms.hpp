//
// Created by darik on 5/18/2020.
//

#ifndef INC_3A_ALGORITHMS_HPP
#define INC_3A_ALGORITHMS_HPP

#include "Graph.hpp"
#include <vector>
#include <thread>
#include <chrono>

using namespace std::chrono;

namespace algorithms {
    template<typename Item>
    std::vector<int> dijkstra(Graph<Item> &graph, int index = 0) {
        std::vector<int> answer(graph.vertex_count());
        std::vector<bool> used(graph.vertex_count());
        for (int i = 0; i < graph.vertex_count(); i++) {
            answer[i] = INT_MAX;
            used[i] = false;
        }
        answer[index] = 0;
        for (int i = 0; i < graph.vertex_count(); i++) {
            int v{-1};
            for (int j = 0; j < graph.vertex_count(); ++j) {
                if (!used[j] && (v == -1 || answer[j] < answer[v]))
                    v = j;
            }
            if (answer[v] == INT_MAX)
                break;
            used[v] = true;
            auto current_vertex = graph.vertex(v);
            auto curr = current_vertex->next;
            while (curr != nullptr) {
                if (answer[v] + curr->weight < answer[curr->num])
                    answer[curr->num] = answer[v] + curr->weight;
                curr = curr->next;
            }
        }
        return answer;
    }

    template<typename Item>
    bool fordBellman(Graph<Item> &graph, int index, std::vector<int> &answer) {
        answer.resize(graph.vertex_count());
        for (auto &i: answer) i = INT_MAX;
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
    std::vector<int> fordBellman(Graph<Item> &graph, int index = 0) {
        std::vector<int> answer;
        if (fordBellman(graph, index, answer)) return answer;
        else return {};
    }

    template<typename Item>
    std::vector<std::vector<int>> johnson(const Graph<Item> &graph) {
        std::vector<std::vector<int>> answer;

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
                auto tmp = dijkstra(last_graph, i);
                std::vector<int> for_ans;
                for (auto j = 0; j < tmp.size(); ++j) {
                    if (tmp[j] != -1) for_ans.push_back(tmp[j] + v[j] - v[i]); // restoring weights
                }
                answer.push_back(for_ans);
            }
        }

        return answer;
    }
}

#endif //INC_3A_ALGORITHMS_HPP
