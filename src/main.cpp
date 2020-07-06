// K. Kafara

// debug, testing
#include <iostream>
#include <string>
#include "./../lib/headers.hpp"

const std::string VERSION = "0.1";


int main()
{
    STAMP(VERSION);

    LOG_MESSAGE("Point 1", __FILE__, __LINE__);
    Graph<V, E> graph;
    LOG_MESSAGE("Point 2", __FILE__, __LINE__);
    V vertex(234, false);
    E edge(30);
    LOG_MESSAGE("Point 3", __FILE__, __LINE__);
    graph.AddDirectedEdge(0, 1, edge);
    LOG_MESSAGE("Point 4", __FILE__, __LINE__);
    return 0;
}