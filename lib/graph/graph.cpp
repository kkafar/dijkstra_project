// K. Kafara

#include "graph.hpp"
#include "./../log/log.hpp"

#include <chrono>
#include <thread>

////////////////////////////////////////////////////////////
Graph::Edge::Edge(const int e, const int weight) : e(e), weight(weight) {}
////////////////////////////////////////////////////////////
Graph::Vertex::Vertex(sf::Color color, bool visited) : color(color), visited(visited) {}
////////////////////////////////////////////////////////////
Graph::Vertex::Vertex() 
{
    visited = false;
    color.r = color.g = color.b = 0;
    color.a = 255;
    // rect.setSize({tile_size, tile_size});
}
////////////////////////////////////////////////////////////
void Graph::Vertex::SetColour(const int& r, const int& g, const int& b, const int& alpha)
{
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = alpha;
}
////////////////////////////////////////////////////////////
void Graph::Vertex::SetVisited(const bool & val) { visited = val; }
////////////////////////////////////////////////////////////
bool Graph::Vertex::IsVisited() const { return visited; }
////////////////////////////////////////////////////////////
Graph::Graph(const int rank, const int tile_size) : rank(rank) 
{
    graph = new Vertex[rank];
}
////////////////////////////////////////////////////////////
Graph::~Graph()
{
    delete[] graph;
}
////////////////////////////////////////////////////////////
void Graph::AddDirectedEdge(const int b, const int e, const int weight)
{
    graph[b].PushBack(Edge(e, weight));
}
////////////////////////////////////////////////////////////
void Graph::Wait(const int & miliseconds) const
{
    std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
}
////////////////////////////////////////////////////////////

void Graph::Dijkstra(const int s, const int t)
{
    MinPriorQueue<int> queue;


    // dodajemy wierzchołek startowy do kolejki. 
    queue.Push(s, 0);


    graph[s].distance = 0;


}
////////////////////////////////////////////////////////////
/* void Graph::Print() const
{
    for (int i = 0; i < rank; ++i)
    {
        std::cout << i << ": ";
        for (Node<Edge> * iter = graph[i].begin(); iter != graph[i].end(); iter = iter->next)
            std::cout << "(b=" << i << ", e=" << (iter->data).e << ", w=" << (iter->data).weight << ")  ";

        std::cout << "\n";
        
    } 
} */
////////////////////////////////////////////////////////////