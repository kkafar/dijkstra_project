// K. Kafara

#include "graph.hpp"
#include "./../log/log.hpp"



////////////////////////////////////////////////////////////
Graph::Edge::Edge(const int e, const int weight) : e(e), weight(weight) {}
////////////////////////////////////////////////////////////
Graph::Vertex::Vertex(const int colour, bool visited) : colour(colour), visited(visited) {}
////////////////////////////////////////////////////////////
Graph::Vertex::Vertex() {}
////////////////////////////////////////////////////////////
void Graph::Vertex::SetColour(const int & val) { colour = val; }
////////////////////////////////////////////////////////////
void Graph::Vertex::SetVisited(const bool & val) { visited = val; }
////////////////////////////////////////////////////////////
bool Graph::Vertex::IsVisited() { return visited; }
////////////////////////////////////////////////////////////
Graph::Graph(const int rank) : rank(rank)
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
void Graph::Print() const
{
    for (int i = 0; i < rank; ++i)
    {
        std::cout << i << ": ";
        for (Node<Edge> * iter = graph[i].begin(); iter != graph[i].end(); iter = iter->next)
            std::cout << "(b=" << i << ", e=" << (iter->data).e << ", w=" << (iter->data).weight << ")  ";

        std::cout << "\n";
        
    } 
}
////////////////////////////////////////////////////////////