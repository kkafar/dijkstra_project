// K. Kafara

#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__


#include  "./../linkedlist/linkedlist.hpp"

class V
{
private:
    int colour;
    bool visited;
public:
    V(const int colour = 0, bool visited = false) : colour(colour), visited(visited) {}
    // ~V();
    void SetColour(const int & val) { colour = val; }
    void SetVisited(const bool & val) { visited = val; }
    bool IsVisited() { return visited; }
};

class E
{
private:
    int weight;
public:
    E(const int weight = 0) : weight(weight) {}
    // ~E();
    void SetWeight(const int & w) { weight = w; }

};

/**
 * Klasa reprezentująca graf w postaci listy sąsiedztwa
 */
template<class V, class E> class Graph
{
private:
    int rank;
        
public:
    struct Edge : public E 
    {
        int e; 

        Edge(const int e = 0, E data = E());
    };

    struct Vertex : public LinkedList<Edge>, public V {};

    Vertex * graph;
    
    Graph(const int rank = 0);
    ~Graph();

    void AddDirectedEdge(const int b, const int e, E data = E());
    
};

#include "graph.tpp"


#endif
