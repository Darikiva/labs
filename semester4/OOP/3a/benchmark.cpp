//
// Created by darik on 5/25/2020.
//
#include "Graph.hpp"
#include "algorithms.hpp"
#include "multiTheadAlgorithms.hpp"
#include <chrono>
#include <fstream>

using namespace std::chrono;

template <typename Function, typename Item>
int benchmark(Function function, Graph<Item>& graph) {
    auto start = steady_clock::now();
    function(graph);
    auto end = steady_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}

template <typename Function, typename Item>
int benchmark(Function function, Graph<Item>& graph, int thread_number) {
    auto start = steady_clock::now();
    function(graph, thread_number);
    auto end = steady_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}

void benchmark() {
    std::ofstream file(R"(..\benchmark.txt)");
    if (file.is_open()) std::cout << "WOW";
    for(int i = 10; i < 400; i += 10) {
        Graph<int> graph;
        graph.randGraph(i, i * (i - 1) / 50);
        file << "Graph: " << i << " vertexes; " << i * (i - 1) / 50 << " edges\n";
        file << "Not thread: " << benchmark(algorithms::johnson<int>, graph) << "ms \t";
        file << "2 thread: " << benchmark(mAlgorithms::johnson<int>, graph, 2) << "ms \t";
        file << "3 thread: " << benchmark(mAlgorithms::johnson<int>, graph, 3) << "ms" << std::endl;
    }
    file.close();
}

int main() {
    benchmark();
    return 0;
}