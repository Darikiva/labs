#ifndef MATR_H_INCLUDED
#define MATR_H_INCLUDED
#include <set>
#include <SFML/Graphics.hpp>
using std::cin;
using std::cout;
using std::endl;

const int MAX_VERTICES = 200;

template <typename T>
T min(const T& first, const T& second)
{
    if(first<second) return first;
    else return second;
}

template <typename T>
bool is_in_vector(const std::vector<T>& vec, T value)
{
    for(const auto& i: vec)
        if (i == value) return true;
    return false;
}

struct GraphMatr
{
    int adjacent[MAX_VERTICES][MAX_VERTICES];
    int vertex_count;
    bool is_oriented;
    GraphMatr(int vertices, bool oriented = false)
    {
        if (vertices > MAX_VERTICES)
        {
            throw std::invalid_argument("Too many vertices");
        }
        vertex_count = vertices;
        for(int i = 0; i < vertex_count; i++)
        {
            for(int j = 0; j < vertex_count; j++)
            {
                adjacent[i][j] = 0;
            }
        }
        is_oriented = oriented;
    }
    GraphMatr(bool oriented = false)
    {
        vertex_count = MAX_VERTICES;
        for(int i=0; i<vertex_count; i++)
        {
            for(int j=0; j<vertex_count; j++)
            {
                adjacent[i][j] = 0;
            }
        }
        is_oriented = oriented;
    }
};

int calculate_memory(const GraphMatr& graph)
{
    int answer = sizeof(graph);
    return answer;
}

void add_edge(GraphMatr& graph, int from, int to, int weight = 1 )
{
    if (from >= graph.vertex_count
        || to >= graph.vertex_count)
    {
        throw std::invalid_argument("Vertex is not in the graph");
    }
    if(graph.adjacent[from][to])
    {
        //cout << "Edge is in graph already\n";
        return;
    }
    graph.adjacent[from][to] = weight;
    if (!graph.is_oriented)
    {
        graph.adjacent[to][from] = weight;
    }
}

void print(const GraphMatr& graph)
{
    for(int i=0; i<graph.vertex_count; i++)
    {
        int j = 0;
        if (!graph.is_oriented)
        {
            j = i+1;
        }
        for (; j<graph.vertex_count; j++)
        {
            if (graph.adjacent[i][j])
            {
                cout << "(" << i << "," << j << "," << graph.adjacent[i][j] << ") ";
            }
        }
    }
    cout << endl;
}

GraphMatr rand_GraphMatr(int vertex, int edges, bool is_oriented = false)
{
    GraphMatr answer = GraphMatr(vertex, is_oriented);
    for(int i=0; i<vertex; i++)
    {
        for(int j=0; j<vertex; j++)
        {
            if(rand()%2)
            {
                add_edge(answer, i, j, rand()%10+1);
                edges--;
                if(edges == 0) return answer;
            }
        }
    }
    if(edges>0)
    {
        for(int i=0; i<vertex; i++)
        {
            for(int j=0; j<vertex; j++)
            {
                if(answer.adjacent[i][j] == 0)
                {
                    add_edge(answer, i, j, rand()%10+1);
                    edges--;
                    if(edges == 0) return answer;
                }
            }
        }
    }
    return answer;
}

int dfs(const GraphMatr& graph, int index, std::vector<bool>& visited, bool is_show = false)
{
    if(is_show) cout << index << " ";

    int answer = 0;
    visited[index] = true;
    for(int i=0; i<graph.vertex_count; i++)
    {
        if(graph.adjacent[index][i]>=1 && !visited[i])
        {
            answer += graph.adjacent[index][i];
            answer += dfs(graph, i, visited, is_show);
        }
    }
    return answer;
}

void dfs_in_order(const GraphMatr& graph, int index, std::vector<bool>& visited, bool is_show = false)
{
    if(is_show) cout << index << " ";

    visited[index] = true;
    std::set<std::pair<int, int> > sorted_index;
    for(int i=0; i<graph.vertex_count; i++)
    {
        if(graph.adjacent[index][i]!=0) sorted_index.insert({graph.adjacent[index][i], i});
    }
    for(const auto& i:sorted_index)
    {
        if(!visited[i.second]) dfs_in_order(graph, i.second, visited, is_show);
    }
}

int number_component(const GraphMatr& graph)
{
    int answer = 0;
    std::vector<bool> visited(graph.vertex_count);
    for(int i=0; i<graph.vertex_count; i++)
        visited[i] = false;
    for(int i=0; i<graph.vertex_count; i++)
    {
        if(visited[i]==false)
        {
            dfs_in_order(graph, i, visited);
            answer++;
        }
    }
    return answer;
}

std::vector<int> Dijkstra(const GraphMatr& graph, int index = 0)
{
    std::vector<int> answer(graph.vertex_count);
    std::vector<bool> is_available(graph.vertex_count);
    for(int i=0; i<graph.vertex_count; i++)
    {
        answer[i] = -1;
        is_available[i] = false;
    }
    answer[index] = 0;
    for(int i=index; i<graph.vertex_count; i++)
    {
        if(!is_available[i] && i!=index) continue;
        for(int j=0; j<graph.vertex_count; j++)
        {
            if(graph.adjacent[i][j]>0)
            {
                if(answer[j]<0)
                    answer[j] = answer[i] + graph.adjacent[i][j];
                else
                    answer[j] = min(answer[j], answer[i] + graph.adjacent[i][j]);
                is_available[j] = true;
            }
        }
    }
    for(int i=0; i<index; i++)
    {
        if(!is_available[i]) continue;
        for(int j=0; j<graph.vertex_count; j++)
        {
            if(graph.adjacent[i][j]>0)
            {
                if(answer[j]<0)
                    answer[j] = answer[i] + graph.adjacent[i][j];
                else
                    answer[j] = min(answer[j], answer[i] + graph.adjacent[i][j]);
                is_available[j] = true;
            }
        }
    }
    return answer;
}

void dfs_sort(const GraphMatr& graph, int index, std::vector<int>& visited, std::vector<int>& answer)
{
    if(visited[index] == 2) return;
    if(visited[index] == 1) throw std::runtime_error("Can't be topologically sorted");
    visited[index] = 1;
    for(int i=0; i<graph.vertex_count; i++)
    {
        if(graph.adjacent[index][i]>0)
        {
            dfs_sort(graph, i, visited, answer);
        }
    }
    visited[index] = 2;
    answer.push_back(index);
}

std::vector<int> top_sorting(const GraphMatr& graph) // based on dfs
{
    std::vector<int> answer;
    std::vector<int> visited(graph.vertex_count);
    for(int i=0; i<graph.vertex_count; i++)
        visited[i] = 0;
    for(int i=0; i<graph.vertex_count; i++)
    {
        if(visited[i] == 0)
        {
            dfs_sort(graph, i, visited, answer);
        }
    }
    return answer;
}

void dfs_build(const GraphMatr& graph, GraphMatr& answer, int index, std::vector<bool>& visited)
{
    visited[index] = true;
    for(int i=0; i<graph.vertex_count; i++)
    {
        if(graph.adjacent[index][i]>0 && !visited[i])
        {
            add_edge(answer, index, i, graph.adjacent[index][i]);
            dfs_build(graph, answer, i, visited);
        }
    }
}

void dfs_build_in_order(const GraphMatr& graph, GraphMatr& answer, int index, std::vector<bool>& visited)
{
    visited[index] = true;
    std::set<std::pair<int, int> > sorted_index;
    for(int i=0; i<graph.vertex_count; i++)
        if(graph.adjacent[index][i]!=0) sorted_index.insert({graph.adjacent[index][i], i});
    for(const auto& i:sorted_index)
    {
        if(!visited[i.second])
        {
            add_edge(answer, index, i.second, i.first);
            dfs_build_in_order(graph, answer, i.second, visited);
        }
    }
}

GraphMatr span_tree(const GraphMatr& graph, void (*func) (const GraphMatr&, GraphMatr&, int, std::vector<bool>&) = dfs_build)
{
    GraphMatr answer(graph.vertex_count, graph.is_oriented);
    std::vector<bool> visited(graph.vertex_count);
    for(int i=0; i<graph.vertex_count; i++)
        visited[i] = false;
    for(int i=0; i<graph.vertex_count; i++)
    {
        if(!visited[i]) func(graph, answer, i, visited);
    }
    return answer;
}

GraphMatr min_span_tree(const GraphMatr& graph)
{
    GraphMatr answer(graph.vertex_count, graph.is_oriented);
    std::vector<int> vertexes;
    vertexes.push_back(0);
    for(int counter=0; counter<graph.vertex_count-1; counter++)
    {
        int min = INT_MAX;
        int index1, index2;
        for(int i=0; i<vertexes.size(); i++)
        {
            for(int j=0; j<graph.vertex_count; j++)
            {
                if(graph.adjacent[vertexes[i]][j]>0 && !is_in_vector(vertexes, j))
                {
                    if(graph.adjacent[vertexes[i]][j]<min)
                    {
                        min = graph.adjacent[vertexes[i]][j];
                        index1 = vertexes[i];
                        index2 = j;
                    }
                }
            }
        }
        add_edge(answer, index1, index2, graph.adjacent[index1][index2]);
        vertexes.push_back(index2);
    }
    return answer;
}

void draw_graph(const GraphMatr& graph)
{
    using namespace sf;
    Font font;
    font.loadFromFile("font.ttf");
    RectangleShape rectangles[graph.vertex_count];
    int h = 60;
    int w = 0;
    int index = -1;
    for(int i=0; i<graph.vertex_count; i++)
    {
        if(i/(h/60)>=20)
        {
            w+=60;
            h+=60;
        }
        rectangles[i].setSize(Vector2f(30, 30));
        rectangles[i].setFillColor(Color::Blue);
        rectangles[i].setPosition(60*(i-w), h);
    }
    RenderWindow window(VideoMode(1000, 700), "Graph");
    while (window.isOpen())
    {
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
        }
        window.clear();
        for(int i=0; i<graph.vertex_count; i++)
        {
            if(IntRect(rectangles[i].getPosition().x, rectangles[i].getPosition().y,
                   rectangles[i].getSize().x, rectangles[i].getSize().y).contains(Mouse::getPosition(window))
                &&Mouse::isButtonPressed(Mouse::Left))
            {
                if(index<0 || i==index)
                {
                    rectangles[i].setPosition(Vector2f(Mouse::getPosition(window).x-15, Mouse::getPosition(window).y-15));
                    index = i;
                    break;
                }
            }
        }
        if(!Mouse::isButtonPressed(Mouse::Left)) index = -1;
        for(int i=0; i<graph.vertex_count; i++)
        {
            for(int j=0; j<graph.vertex_count; j++)
            {
                if(graph.adjacent[i][j]!=0)
                {
                    VertexArray line(Lines, 2);
                    line[0].position = Vector2f(rectangles[i].getPosition().x + 15,
                                                rectangles[i].getPosition().y + 15);
                    line[1].position = Vector2f(rectangles[j].getPosition().x + 15,
                                                rectangles[j].getPosition().y + 15);
                    line[0].color = Color::Red;
                    line[1].color = Color::Red;
                    window.draw(line);

                    Text text(std::to_string(graph.adjacent[i][j]), font, 20);
                    text.setPosition((rectangles[i].getPosition().x+rectangles[j].getPosition().x)/2,
                                     (rectangles[i].getPosition().y+rectangles[j].getPosition().y)/2);
                    window.draw(text);
                }
            }
        }
        for(int i=0; i<graph.vertex_count; i++)
            window.draw(rectangles[i]);
        window.display();
    }
}
#endif // MATR_H_INCLUDED
