#ifndef STRCT_H_INCLUDED
#define STRCT_H_INCLUDED

#include <SFML/Graphics.hpp>

using std::cin;
using std::cout;
using std::endl;

const int MAX_V = 2000;

struct Node
{
    int vertex;
    int weight;
    Node* next;
    Node(int _vertex, int weight_ = 1, Node* _next=nullptr)
    {
        vertex = _vertex;
        next = _next;
        weight = weight_;
    }
};

struct List
{
    Node* start;
    Node* end;
    List()
    {
        start = end = nullptr;
    }
};

void add_to_list(List& list, int vertex, int weight)
{
    Node* new_node = new Node(vertex, weight);
    if (list.start)
    {
        list.end->next = new_node;
    }
    else
    {
        list.start = new_node;
    }
    list.end = new_node;
}

Node* search_list(const List& list, int vertex)
{
    Node* result = list.start;
    while(result)
    {
        if(result->vertex==vertex)
        {
            return result;
        }
        result = result->next;
    }
    return result;
}

struct GraphStruct
{
    List neighbours[MAX_V];
    int vertex_count;
    bool is_oriented;
    GraphStruct(int vertices, bool oriented = true)
    {
        /*if (vertices>MAX_VERTICES)
        {
            throw std::invalid_argument("Too many vertices");
        }*/
        vertex_count = vertices;
        is_oriented = oriented;
    }
    GraphStruct(bool oriented = true){
        vertex_count = MAX_VERTICES;
        is_oriented = oriented;
    }
};

int calculate_memory(const GraphStruct& graph)
{
    int answer = sizeof(graph);
    for(int i=0; i<graph.vertex_count; i++)
    {
        Node* next = graph.neighbours[i].start;
        while(next)
        {
            answer += sizeof(*next);
            next = next->next;
        }
    }
    return answer;
}

void add_edge(GraphStruct& graph, int from, int to, int weight = 1 )
{
    if (from>=graph.vertex_count
        || to>=graph.vertex_count)
    {
        throw std::invalid_argument("Vertex not in graph");
    }
    List& from_neighbours = graph.neighbours[from];
    if (search_list(from_neighbours, to))
    {
        //cout<<"Already in graph"<<endl;
    }
    else
    {
        add_to_list(from_neighbours, to, weight);
        if(!graph.is_oriented)
        {
            add_to_list(graph.neighbours[to], from, weight);
        }
    }
}

void print(const GraphStruct& graph)
{
    for (int i=0; i<graph.vertex_count; i++)
    {
        Node* cur = graph.neighbours[i].start;
        while(cur)
        {
            int j = cur->vertex;
            if(graph.is_oriented || cur->vertex > i)
                cout << "(" << i << "," << j << "," << cur->weight << ") ";
            cur = cur->next;
        }
    }
    cout << endl;
}

GraphStruct rand_GraphStruct(int vertex, int edges, bool is_oriented = false)
{
    GraphStruct answer(vertex, is_oriented);
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
                if(search_list(answer.neighbours[i], j) == nullptr)
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

int dfs(const GraphStruct& graph, int index, std::vector<bool>& visited, bool is_show = false)
{
    if(is_show) cout << index << " ";

    visited[index] = true;
    int answer = 0;
    Node* next = graph.neighbours[index].start;
    while(next!=nullptr)
    {
        if(!visited[next->vertex])
        {
            answer += next->weight + dfs(graph, next->vertex, visited, is_show);
        }
        next = next->next;
    }
    return answer;
}


void dfs_in_order(const GraphStruct& graph, int index, std::vector<bool>& visited, bool is_show = false)
{
    if(is_show) cout << index << " ";

    visited[index] = true;
    std::set<std::pair<int, int> > sorted_index;
    Node* next = graph.neighbours[index].start;
    while(next!=nullptr)
    {
        sorted_index.insert({next->weight, next->vertex});
        next = next->next;
    }
    for(const auto& i:sorted_index)
    {
        if(!visited[i.second]) dfs_in_order(graph, i.second, visited, is_show);
    }
}

int number_component(const GraphStruct& graph)
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

std::vector<int> Dijkstra(const GraphStruct& graph, int index = 0)
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
        Node* next = graph.neighbours[i].start;
        while(next!=nullptr)
        {
            if(answer[next->vertex]<0)
                answer[next->vertex] = answer[i] + next->weight;
            else
                answer[next->vertex] = min(answer[next->vertex], answer[i] + next->weight);
            is_available[next->vertex] = true;
            next = next->next;
        }
    }

    for(int i=0; i<index; i++)
    {
        if(!is_available[i]) continue;
        Node* next = graph.neighbours[i].start;
        while(next!=nullptr)
        {
            if(answer[next->vertex]<0)
                answer[next->vertex] = answer[i] + next->weight;
            else
                answer[next->vertex] = min(answer[next->vertex], answer[i] + next->weight);
            is_available[next->vertex] = true;
            next = next->next;
        }
    }
    return answer;
}

void dfs_sort(const GraphStruct& graph, int index, std::vector<int>& visited, std::vector<int>& answer)
{
    if(visited[index]==2) return;
    if(visited[index]==1) throw std::runtime_error("Can't be topologically sorted");
    visited[index] = 1;
    Node* next = graph.neighbours[index].start;
    while(next!=nullptr)
    {
        dfs_sort(graph, next->vertex, visited, answer);
        next = next->next;
    }
    visited[index] = 2;
    answer.push_back(index);
}

std::vector<int> top_sorting(const GraphStruct& graph) // based on dfs
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

void dfs_build(const GraphStruct& graph, GraphStruct& answer, int index, std::vector<bool>& visited)
{
    visited[index] = true;
    Node* next = graph.neighbours[index].start;
    while(next!=nullptr)
    {
        if(!visited[next->vertex])
        {
            add_edge(answer, index, next->vertex, next->weight);
            dfs_build(graph, answer, next->vertex, visited);
        }
        next = next->next;
    }
}

void dfs_build_in_order(const GraphStruct& graph, GraphStruct& answer, int index, std::vector<bool>& visited)
{
    visited[index] = true;
    std::set<std::pair<int, int> > sorted_index;
    Node* next = graph.neighbours[index].start;
    while(next!=nullptr)
    {
        sorted_index.insert({next->weight, next->vertex});
        next = next->next;
    }
    for(const auto& i:sorted_index)
    {
        if(!visited[i.second])
        {
            add_edge(answer, index, i.second);
            dfs_build_in_order(graph, answer, i.second, visited);
        }
    }
}


GraphStruct span_tree(const GraphStruct& graph,
                      void (*func) (const GraphStruct&, GraphStruct&, int, std::vector<bool>&) = dfs_build)
{
    GraphStruct answer(graph.vertex_count, graph.is_oriented);
    std::vector<bool> visited(graph.vertex_count);
    for(int i=0; i<graph.vertex_count; i++)
        visited[i] = false;
    for(int i=0; i<graph.vertex_count; i++)
    {
        if(!visited[i]) func(graph, answer, i, visited);
    }
    return answer;
}

GraphStruct min_span_tree(const GraphStruct& graph)
{
    GraphStruct answer(graph.vertex_count, graph.is_oriented);
    std::vector<int> vertexes;
    vertexes.push_back(0);
    for(int counter=0; counter<graph.vertex_count-1; counter++)
    {
        int index1, index2;
        int min = INT_MAX;
        for(int i=0; i<vertexes.size(); i++)
        {
            Node* node = graph.neighbours[vertexes[i]].start;
            while(node)
            {
                if(!is_in_vector(vertexes, node->vertex))
                {
                    if(node->weight<min)
                    {
                        min = node->weight;
                        index1 = vertexes[i];
                        index2 = node->vertex;
                    }
                }
                node = node->next;
            }
        }
        add_edge(answer, index1, index2, min);
        vertexes.push_back(index2);
    }
    return answer;
}

void draw_graph(const GraphStruct& graph)
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
            w+=20;
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
            Node* next = graph.neighbours[i].start;
            while(next)
            {
                if(next->weight!=0)
                {
                    VertexArray line(Lines, 2);
                    line[0].position = Vector2f(rectangles[i].getPosition().x + 15,
                                                rectangles[i].getPosition().y + 15);
                    line[1].position = Vector2f(rectangles[next->vertex].getPosition().x + 15,
                                                rectangles[next->vertex].getPosition().y + 15);
                    line[0].color = Color::Red;
                    line[1].color = Color::Red;
                    window.draw(line);

                    Text text(std::to_string(next->weight), font, 20);
                    text.setPosition((rectangles[i].getPosition().x+rectangles[next->vertex].getPosition().x)/2,
                                     (rectangles[i].getPosition().y+rectangles[next->vertex].getPosition().y)/2);
                    window.draw(text);
                }
                next = next->next;
            }
        }
        for(int i=0; i<graph.vertex_count; i++)
            window.draw(rectangles[i]);
        window.display();
    }
}
#endif // STRCT_H_INCLUDED
