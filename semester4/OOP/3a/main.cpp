#include "Graph.hpp"
#include "multiTheadAlgorithms.hpp"
#include "algorithms.hpp"
#include <chrono>

void miniBenchmark() {
    using namespace std;
    using namespace std::chrono;
    Graph<int> graph;
    graph.randGraph(1000, 4000);
    auto start = steady_clock::now();
    johnson(graph);
    auto end = steady_clock::now();
    std::cout << "Not thread: " << duration_cast<milliseconds>(end - start).count() << " ms";

    std::cout << std::endl;

    start = steady_clock::now();
    mAlgorithms::johnson(graph);
    end = steady_clock::now();
    std::cout << "Thread: " << duration_cast<milliseconds>(end - start).count() << " ms";

}
int main() {
    miniBenchmark();
    return 0;
}
