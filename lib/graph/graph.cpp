// K. Kafara

#include "graph.hpp"
#include "./../log/log.hpp"

#include <chrono>
#include <thread>

////////////////////////////////////////////////////////////
// @brief Logger
// ???
////////////////////////////////////////////////////////////
Log graph_logger;
////////////////////////////////////////////////////////////

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
void Graph::Vertex::SetDistance(const int & dist) { distance = dist; }
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
    graph_logger.SetLevel(3);

    graph_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 0, "Dijstra(", s, ", ", t, ")");

    Wait(1000);

    graph_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 3, "Odczekano sekunde");

    MinPriorQueue<int> queue;


    // dodajemy wierzchołek startowy do kolejki. 
    queue.Push(s, 0);

    // Ustawiamy parametry dla wierzchołka startowego
    graph[s].SetDistance(0);
    // kolor na zielony (jako obecnie rozważany wierzchołek)
    graph[s].SetColour(0, 255, 0);

    Wait(1000);
    
    int current_vertex, edge_end, distance;

    while (!queue.IsEmpty())
    {
        // pobieramy wierzchołek z kolejki
        current_vertex = queue.Front();
        queue.Pop();

        graph[current_vertex].SetVisited(true);

        // przeglądamy wszystkich sąsiadów current_vertex
        for (int v = 0; v < graph[current_vertex].GetSize(); ++v)
        {
            edge_end = graph[current_vertex][v].GetEnd();

            // jeżeli sąsiad nie jest odwiedzony 
            if (!graph[edge_end].IsVisited())
            {
                // dokonujemy relaksacji
                distance = graph[current_vertex].GetDistance() + graph[current_vertex][v].GetWeight();

                if (distance < graph[edge_end].GetDistance())
                    graph[edge_end].SetDistance(distance);
                

                queue.Push(edge_end, graph[edge_end].GetDistance());
            }
        }
    }


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