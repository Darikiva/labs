

// ************************************
///////////////////////////////////////
// BLOCK    TASK
// 0        1, 2
// 1        6
// 2        12
// 3        14
// 4        18
// 5        19
// 6        22
///////////////////////////////////////
// ************************************


#include <vector>
#include <iostream>
#include <set>
#include <chrono>
#include "matr.h"
#include "strct.h"


GraphMatr strct_to_matr(const GraphStruct& strct)
{
    GraphMatr answer(strct.vertex_count);
    for(int i=0; i<strct.vertex_count; i++)
    {
        Node* beg = strct.neighbours[i].start;
        while(beg)
        {
            add_edge(answer, i, beg->vertex, beg->weight);
            beg = beg->next;
        }
    }
    return answer;
}

GraphStruct matr_to_strct(const GraphMatr& matr)
{
    GraphStruct answer(matr.vertex_count);
    for(int i=0; i<matr.vertex_count; i++)
        for(int j=0; j<matr.vertex_count; j++)
            add_edge(answer, i, j, matr.adjacent[i][j]);
    return answer;
}

int help()
{
    cout << "1. Add edges\n";
    cout << "2. Print\n";
    cout << "3. Number of components\n";
    cout << "4. DFS\n";
    cout << "5. DFS in order\n";
    cout << "6. Minimal distance between 2 vertexes\n";
    cout << "7. Minimal distance from 1 vertex to others\n";
    cout << "8. Minimal distances among all vertexes\n";
    cout << "9. Topological sort\n";
    cout << "10. Build span tree\n";
    cout << "11. Build min span tree\n";
    cout << "12. Exit\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    return choice;
}

template <typename T>
void Interactive(T&);

void Demonstration_Matr();
void Demonstration_Struct();

void Benchmark_Matr();
void Benchmark_Struct();

int main()
{
    cout << "1. Matrix\n";
    cout << "2. Structure\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    switch(choice)
    {
    case 1:
        {
            cout << "1. Interactive\n";
            cout << "2. Demonstrative\n";
            cout << "3. Benchmark\n";
            cout << "Enter your choice: ";
            int mode;
            cin >> mode;
            switch(mode)
            {
            case 1:
                {
                    cout << "Enter number of vertex (not more than " << MAX_VERTICES << " ): ";
                    int number;
                    cin >> number;
                    if(number>MAX_VERTICES)
                    {
                        cout << "Error\n";
                        break;
                    }
                    cout << "Is graph oriented? Enter 1 - yes, 0 - no";
                    bool is_oriented;
                    cin >> is_oriented;
                    GraphMatr graph(number, is_oriented);
                    if(is_oriented) graph.is_oriented = true;
                    else graph.is_oriented = false;
                    Interactive(graph);
                }
                break;
            case 2:
                Demonstration_Matr();
                break;
            case 3:
                Benchmark_Matr();
                break;
            }
        }
        break;
    case 2:
        {
            cout << "1. Interactive\n";
            cout << "2. Demonstrative\n";
            cout << "3. Benchmark\n";
            cout << "Enter your choice: ";
            int mode;
            cin >> mode;
            switch(mode)
            {
            case 1:
                {
                    cout << "Enter number of vertex (not more than " << MAX_VERTICES << " ): ";
                    int number;
                    cin >> number;
                    if(number>MAX_VERTICES)
                    {
                        cout << "Error\n";
                        break;
                    }
                    cout << "Is graph oriented? Enter 1 - yes, 0 - no";
                    bool is_oriented;
                    cin >> is_oriented;
                    GraphStruct graph = new GraphStruct(number);
                    if(is_oriented) graph.is_oriented = true;
                    else graph.is_oriented = false;
                    Interactive(graph);
                }
                break;
            case 2:
                Demonstration_Struct();
                break;
            case 3:
                Benchmark_Struct();
                break;
            }
        }
        break;
    default:
        cout << "No such option!\n";
    }
    return 0;
}

template <typename T>
void Interactive(T& graph)
{
    if(graph.is_oriented) cout << "MDA";
    for(;;)
    {
        switch(help())
        {
        case 1:
            {
                cout << "How much edges do you want to add? ";
                int number;
                cin >> number;

                int index1;
                int index2;
                int weight;
                cout << "Enter 2 vertexes and weight: ";

                for(int i=0; i<number; i++)
                {
                    cin >> index1 >> index2 >> weight;
                    try
                    {
                        add_edge(graph, index1, index2, weight);
                    }
                    catch(std::invalid_argument& ex)
                    {
                        cout << ex.what();
                    }
                }
            }
            break;
        case 2:
            print(graph);
            break;
        case 3:
            cout << number_component(graph) << endl;
            break;
        case 4:
            {
                cout << "From which vertex? ";
                int vertex;
                std::vector<bool> visited(graph.vertex_count);
                cin >> vertex;
                if(vertex<0 || vertex>=graph.vertex_count)
                {
                    cout << "No such vertex!\n";
                    break;
                }
                else
                {
                    std::vector<bool> visited(graph.vertex_count);
                    dfs(graph, vertex, visited, true);
                }
                cout << endl;
            }
            break;
        case 5:
            {
                int vertex;
                std::vector<bool> visited(graph.vertex_count);
                cout << "From which vertex? ";
                cin >> vertex;
                if(vertex<0 || vertex>=graph.vertex_count)
                {
                    cout << "No such vertex!\n";
                    break;
                }
                else
                {
                    std::vector<bool> visited(graph.vertex_count);
                    dfs_in_order(graph, vertex, visited, true);
                }
                cout << endl;
            }
            break;
        case 6:
            {
                if(graph.is_oriented)
                {
                    cout << "Impossible!\n";
                    break;
                }
                int vertex1;
                int vertex2;
                cout << "Enter 2 vertexes: ";
                cin >> vertex1 >> vertex2;
                if(vertex1<0 || vertex2<0 || vertex1>=graph.vertex_count || vertex2>=graph.vertex_count)
                {
                    cout << "No such vertex!\n";
                    break;
                }
                std::vector<int> distances = Dijkstra(graph, vertex1);
                cout << distances[vertex2];
                cout << endl;
            }
            break;
        case 7:
            {
                if(graph.is_oriented)
                {
                    cout << "Impossible\n";
                    break;
                }
                int vertex;
                cout << "Enter vertex: ";
                cin >> vertex;
                if(vertex<0 || vertex>=graph.vertex_count)
                {
                    cout << "No such vertex\n";
                    break;
                }
                std::vector<int> distances = Dijkstra(graph, vertex);
                for(const auto& i:distances) cout << i << " ";
                cout << endl;
            }
            break;
        case 8:
            {
                if(graph.is_oriented)
                {
                    cout << "Impossible\n";
                    break;
                }
                for(int i=0; i<graph.vertex_count; i++)
                {
                    std::vector<int> distances = Dijkstra(graph, i);
                    for(const auto& i:distances) cout << i << " ";
                    cout << endl;
                }
            }
            break;
        case 9:
            {
                try
                {
                    std::vector<int> vertexes = top_sorting(graph);
                    for(const auto& i:vertexes) cout << i << " ";
                    cout << endl;
                }
                catch(std::runtime_error& ex)
                {
                    cout << ex.what();
                    cout << endl;
                }
            }
            break;
        case 10:
            {
                print(span_tree(graph));
                cout << endl;
            }
            break;
        case 11:
            {
                T new_graph = min_span_tree(graph);
                print(new_graph);
                cout << endl;
            }
            break;
        case 12:
            return;
        default:
            cout << "No such option\n";
        }
    }
}

void Demonstration_Matr()
{
    cout << "Make random not oriented graph with 13 vertexes and 30 edges:";
    GraphMatr graph = rand_GraphMatr(13, 30);
    print(graph);
    cout << endl;

    int vertex = rand()%13;
    std::vector<bool> visited(graph.vertex_count);
    for(int i=0; i<graph.vertex_count; i++) visited[i] = false;
    cout << "Dfs from vertex " << vertex << ": ";
    dfs(graph, vertex, visited, true);
    cout << endl;

    vertex = rand()%13;
    for(int i=0; i<graph.vertex_count; i++) visited[i] = false;
    cout << "Dfs in order from vertex " << vertex << ": ";
    dfs_in_order(graph, vertex, visited, true);
    cout << endl;

    cout << "Number components: " << number_component(graph);
    cout << endl;

    cout << "Matrix of minimal distances: " << endl;
    for(int i=0; i<graph.vertex_count; i++)
    {
        std::vector<int> distances = Dijkstra(graph, i);
        for(const auto& i:distances) cout << i << " ";
        cout << endl;
    }
    cout << endl;

    cout << "Span tree based on dfs: " << endl;
    print(span_tree(graph));
    cout << endl;

    cout << "Span tree based on dfs in order: " << endl;
    print(span_tree(graph, dfs_build_in_order));
    cout << endl;

    cout << "Minimal span tree: " << endl;
    print(min_span_tree(graph));
    for(int i=0; i<graph.vertex_count; i++) visited[i] = false;
    cout << endl << "The weight of min span tree: " << dfs(min_span_tree(graph), 0, visited, false);
    cout << endl << endl;




    cout << "Make new oriented graph with 5 vertexes and 8 edges:";
    GraphMatr new_graph(5, true);
    add_edge(new_graph, 0, 1, rand()%25+1);
    add_edge(new_graph, 0, 2, rand()%25+1);
    add_edge(new_graph, 0, 3, rand()%25+1);
    add_edge(new_graph, 0, 4, rand()%25+1);
    add_edge(new_graph, 1, 3, rand()%25+1);
    add_edge(new_graph, 2, 3, rand()%25+1);
    add_edge(new_graph, 2, 4, rand()%25+1);
    add_edge(new_graph, 3, 4, rand()%25+1);
    print(new_graph);
    cout << endl;

    vertex = rand()%5;
    visited.resize(5);
    for(int i=0; i<new_graph.vertex_count; i++) visited[i] = false;
    cout << "Dfs from vertex " << vertex << ": ";
    dfs(new_graph, vertex, visited, true);
    cout << endl;

    vertex = rand()%5;
    for(int i=0; i<new_graph.vertex_count; i++) visited[i] = false;
    cout << "Dfs in order from vertex " << vertex << ": ";
    dfs_in_order(new_graph, vertex, visited, true);
    cout << endl;

    cout << "Number components: " << number_component(new_graph);
    cout << endl;

    cout << "Span tree based on dfs: " << endl;
    print(span_tree(new_graph));
    cout << endl;

    cout << "Span tree based on dfs in order: " << endl;
    print(span_tree(new_graph, dfs_build_in_order));
    cout << endl;

    cout << "Topological sorting based on dfs: " << endl;
    for(const auto i:top_sorting(new_graph)) cout << i << " ";
}

void Demonstration_Struct()
{
    cout << "Make random not oriented graph with 13 vertexes and 30 edges:";
    GraphStruct graph = rand_GraphStruct(13, 30, false);
    print(graph);
    cout << endl;

    int vertex = rand()%13;
    std::vector<bool> visited(graph.vertex_count);
    for(int i=0; i<graph.vertex_count; i++) visited[i] = false;
    cout << "Dfs from vertex " << vertex << ": ";
    dfs(graph, vertex, visited, true);
    cout << endl;

    vertex = rand()%13;
    for(int i=0; i<graph.vertex_count; i++) visited[i] = false;
    cout << "Dfs in order from vertex " << vertex << ": ";
    dfs_in_order(graph, vertex, visited, true);
    cout << endl;

    cout << "Number components: " << number_component(graph);
    cout << endl;

    cout << "Matrix of minimal distances: " << endl;
    for(int i=0; i<graph.vertex_count; i++)
    {
        std::vector<int> distances = Dijkstra(graph, i);
        for(const auto& i:distances) cout << i << " ";
        cout << endl;
    }
    cout << endl;

    cout << "Span tree based on dfs: " << endl;
    print(span_tree(graph));
    cout << endl;

    cout << "Span tree based on dfs in order: " << endl;
    print(span_tree(graph, dfs_build_in_order));
    cout << endl;

    cout << "Minimal span tree: " << endl;
    print(min_span_tree(graph));
    for(int i=0; i<graph.vertex_count; i++) visited[i] = false;
    cout << endl << "The weight of min span tree: " << dfs(min_span_tree(graph), 0, visited, false);
    cout << endl << endl;




    cout << "Make new oriented graph with 5 vertexes and 8 edges:";
    GraphStruct new_graph(5, true);
    add_edge(new_graph, 0, 1, rand()%25+1);
    add_edge(new_graph, 0, 2, rand()%25+1);
    add_edge(new_graph, 0, 3, rand()%25+1);
    add_edge(new_graph, 0, 4, rand()%25+1);
    add_edge(new_graph, 1, 3, rand()%25+1);
    add_edge(new_graph, 2, 3, rand()%25+1);
    add_edge(new_graph, 2, 4, rand()%25+1);
    add_edge(new_graph, 3, 4, rand()%25+1);
    print(new_graph);
    cout << endl;

    vertex = rand()%5;
    visited.resize(5);
    for(int i=0; i<new_graph.vertex_count; i++) visited[i] = false;
    cout << "Dfs from vertex " << vertex << ": ";
    dfs(new_graph, vertex, visited, true);
    cout << endl;

    vertex = rand()%5;
    for(int i=0; i<new_graph.vertex_count; i++) visited[i] = false;
    cout << "Dfs in order from vertex " << vertex << ": ";
    dfs_in_order(new_graph, vertex, visited, true);
    cout << endl;

    cout << "Number components: " << number_component(new_graph);
    cout << endl;

    cout << "Span tree based on dfs: " << endl;
    print(span_tree(new_graph));
    cout << endl;

    cout << "Span tree based on dfs in order: " << endl;
    print(span_tree(new_graph, dfs_build_in_order));
    cout << endl;

    cout << "Topological sorting based on dfs: " << endl;
    for(const auto i:top_sorting(new_graph)) cout << i << " ";
}

void Benchmark_Matr()
{
    using namespace std::chrono;

    int vertex = 10;
    int edges = 20;
    unsigned time=0;

    while(vertex < MAX_VERTICES && time < 10000)
    {
        GraphMatr graph = rand_GraphMatr(vertex, edges);

        cout << vertex << " vertexes, " << edges << " edges" << endl;
        cout << '\t' << "Memory: " << calculate_memory(graph) << endl;

        auto start = steady_clock::now();
        number_component(graph);
        auto finish = steady_clock::now();

        time = duration_cast<milliseconds>(finish-start).count();
        cout << '\t' << "Number components: " << time << " ms" << endl;


        start = steady_clock::now();
        for(int i=0; i<graph.vertex_count; i++)
        {
            Dijkstra(graph, i);
        }
        finish = steady_clock::now();

        time = duration_cast<milliseconds>(finish-start).count();
        cout << '\t' << "Matrix of minimal distances: " << time << " ms" << endl;


        start = steady_clock::now();
        span_tree(graph);
        finish = steady_clock::now();

        time = duration_cast<milliseconds>(finish-start).count();
        cout << '\t' << "Span tree based on dfs: " << time << " ms" << endl;

        start = steady_clock::now();
        span_tree(graph, dfs_build_in_order);
        finish = steady_clock::now();

        time = duration_cast<milliseconds>(finish-start).count();
        cout << '\t' << "Span tree based on dfs in order: " << time << " ms" << endl;

        start = steady_clock::now();
        min_span_tree(graph);
        finish = steady_clock::now();

        time = duration_cast<milliseconds>(finish-start).count();
        cout << '\t' << "Minimal span tree: " << time << " ms" << endl;

        if((edges+edges*0.5)*2 > vertex*(vertex-1))
        {
            vertex += 0.5*vertex;
            edges = vertex;
        }
        else
        {
            edges+=0.5*edges;
        }
    }

    cout << '\t' << "For oriented graph" << endl;
    vertex = 10;
    edges = 10;
    time = 0;

    while(vertex < MAX_VERTICES && time < 10000)
    {
        GraphStruct graph = rand_GraphStruct(vertex, edges, true);

        cout << vertex << " vertexes, " << edges << " edges" << endl;
        cout << '\t' << "Memory: " << calculate_memory(graph) << endl;

        auto start = steady_clock::now();
        number_component(graph);
        auto finish = steady_clock::now();

        time = duration_cast<milliseconds>(finish-start).count();
        cout << '\t' << "Number components: " << time << " ms" << endl;

        start = steady_clock::now();
        span_tree(graph);
        finish = steady_clock::now();

        time = duration_cast<milliseconds>(finish-start).count();
        cout << '\t' << "Span tree based on dfs: " << time << " ms" << endl;

        start = steady_clock::now();
        span_tree(graph, dfs_build_in_order);
        finish = steady_clock::now();

        time = duration_cast<milliseconds>(finish-start).count();
        cout << '\t' << "Span tree based on dfs in order: " << time << " ms" << endl;

        try
        {
            start = steady_clock::now();
            top_sorting(graph);
            finish = steady_clock::now();

            time = duration_cast<milliseconds>(finish-start).count();
            cout << '\t' << "Topological sorting: " << time << " ms" << endl;
        }
        catch(std::runtime_error& ex){
            cout << '\t' << ex.what() << endl;
        }

        if((edges+edges*0.5)*2 > vertex*(vertex-1))
        {
            vertex += 0.5*vertex;
            edges = vertex;
        }
        else
        {
            edges+=0.5*edges;
        }
    }
}

void Benchmark_Struct()
{
    using namespace std::chrono;

    int vertex = 10;
    int edges = 20;
    unsigned time=0;

    while(vertex < MAX_V && time < 10000)
    {
        GraphStruct graph = rand_GraphStruct(vertex, edges);

        cout << vertex << " vertexes, " << edges << " edges" << endl;

        cout << '\t' << "Memory: " << calculate_memory(graph) << endl;
        auto start = steady_clock::now();
        number_component(graph);
        auto finish = steady_clock::now();

        time = duration_cast<milliseconds>(finish-start).count();
        cout << '\t' << "Number components: " << time << " ms" << endl;


        start = steady_clock::now();
        for(int i=0; i<graph.vertex_count; i++)
        {
            Dijkstra(graph, i);
        }
        finish = steady_clock::now();

        time = duration_cast<milliseconds>(finish-start).count();
        cout << '\t' << "Matrix of minimal distances: " << time << " ms" << endl;


        start = steady_clock::now();
        span_tree(graph);
        finish = steady_clock::now();

        time = duration_cast<milliseconds>(finish-start).count();
        cout << '\t' << "Span tree based on dfs: " << time << " ms" << endl;

        start = steady_clock::now();
        span_tree(graph, dfs_build_in_order);
        finish = steady_clock::now();

        time = duration_cast<milliseconds>(finish-start).count();
        cout << '\t' << "Span tree based on dfs in order: " << time << " ms" << endl;

        start = steady_clock::now();
        min_span_tree(graph);
        finish = steady_clock::now();

        time = duration_cast<milliseconds>(finish-start).count();
        cout << '\t' << "Minimal span tree: " << time << " ms" << endl;

        if(edges*4 > vertex*(vertex-1))
        {
            vertex += vertex;
            edges = 3*vertex;
        }
        else
        {
            edges+=edges;
        }
    }

    cout << '\t' << "For oriented graph" << endl;
    vertex = 10;
    edges = 10;
    time = 0;

    while(vertex < MAX_V && time < 10000)
    {
        GraphStruct graph = rand_GraphStruct(vertex, edges, true);

        cout << vertex << " vertexes, " << edges << " edges" << endl;
        cout << '\t' << "Memory: " << calculate_memory(graph) << endl;

        auto start = steady_clock::now();
        number_component(graph);
        auto finish = steady_clock::now();

        time = duration_cast<milliseconds>(finish-start).count();
        cout << '\t' << "Number components: " << time << " ms" << endl;

        start = steady_clock::now();
        span_tree(graph);
        finish = steady_clock::now();

        time = duration_cast<milliseconds>(finish-start).count();
        cout << '\t' << "Span tree based on dfs: " << time << " ms" << endl;

        start = steady_clock::now();
        span_tree(graph, dfs_build_in_order);
        finish = steady_clock::now();

        time = duration_cast<milliseconds>(finish-start).count();
        cout << '\t' << "Span tree based on dfs in order: " << time << " ms" << endl;

        try
        {
            start = steady_clock::now();
            top_sorting(graph);
            finish = steady_clock::now();

            time = duration_cast<milliseconds>(finish-start).count();
            cout << '\t' << "Topological sorting: " << time << " ms" << endl;
        }
        catch(std::runtime_error& ex){
            cout << '\t' << ex.what() << endl;
        }

        if(edges*4 > vertex*(vertex-1))
        {
            vertex += vertex;
            edges = vertex;
        }
        else
        {
            edges+=edges;
        }
    }
}
