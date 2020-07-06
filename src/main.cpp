// K. Kafara

// debug, testing
#include <iostream>
#include <string>
#include "./../lib/headers.hpp"

const std::string VERSION = "0.1";


int main()
{
    Log log(2);

    log.LogMessage("MESSAGE", 2, __FILE__, __LINE__);
    STAMP(VERSION);

    LOG_MESSAGE("Point 1", __FILE__, __LINE__);
    Graph graph(10);
    LOG_MESSAGE("Point 2", __FILE__, __LINE__);
    graph.AddDirectedEdge(0, 1, 1);
    graph.AddDirectedEdge(1, 3, 10);
    graph.AddDirectedEdge(2, 5, 16);
    graph.AddDirectedEdge(1, 8, 11);
    LOG_MESSAGE("Point 3", __FILE__, __LINE__);
    
    graph.Print();
    LOG_MESSAGE("Point 4", __FILE__, __LINE__);
    return 0;
}