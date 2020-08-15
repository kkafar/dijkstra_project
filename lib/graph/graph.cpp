// K. Kafara

#include "graph.hpp"
#include "./../log/log.hpp"

#define __GRAPH_LOG__
// #include <chrono>
// #include <thread>



////////////////////////////////////////////////////////////
// @brief Logger
// ???
////////////////////////////////////////////////////////////
Log graph_logger;
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
Graph::Edge::Edge(const int e, const int weight) : e(e), weight(weight) {}
////////////////////////////////////////////////////////////
Graph::Vertex::Vertex(sf::Color color, bool visited) : visited(visited) 
{
    static int id = 0;
    rect.setFillColor(color);
    rect.setPosition ({ 
        (id * settings::tiles::TILE_WIDTH) % settings::window::WIDTH,
        (id * settings::tiles::TILE_WIDTH * settings::tiles::TILE_HEIGHT) / settings::window::WIDTH
    });
    rect.setSize({
        settings::tiles::TILE_WIDTH, 
        settings::tiles::TILE_HEIGHT
    });
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(-3);
    ++id;
    // rect.setSize({TODO});
}
////////////////////////////////////////////////////////////
void Graph::Vertex::SetColour(const int& r, const int& g, const int& b, const int& alpha)
{
    rect.setFillColor(sf::Color(r, g, b, alpha));
}
////////////////////////////////////////////////////////////
Graph::Vertex::Vertex() : visited(false)
{
    static int id = 0;

#ifdef __GRAPH_LOG__
    graph_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 2, "Konstrutkor domyslny klasy Graph::Vertex, id=", id);
#endif

    rect.setFillColor(sf::Color::White);
    rect.setPosition({ 
        (id * settings::tiles::TILE_WIDTH) % settings::window::WIDTH,
        (id / settings::tiles::TILES_IN_ROW) * settings::tiles::TILE_HEIGHT
    });

#ifdef __GRAPH_LOG__
    graph_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 2, "Ustawiam plytke na poz.: (", 
        (id * settings::tiles::TILE_WIDTH) % settings::window::WIDTH, ", ",
        (id / settings::tiles::TILES_IN_ROW) * settings::tiles::TILE_HEIGHT, ")");
#endif

    rect.setSize({
        settings::tiles::TILE_WIDTH, 
        settings::tiles::TILE_HEIGHT
    });

#ifdef __GRAPH_LOG__
    graph_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 2, "Rozmiar plytki: (", 
        settings::tiles::TILE_WIDTH, ", ",
        settings::tiles::TILE_HEIGHT, ")");
#endif
 
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(-3);
    ++id;
}
////////////////////////////////////////////////////////////
void Graph::Vertex::SetVisited(const bool & val) { visited = val; }
////////////////////////////////////////////////////////////
[[nodiscard]] bool Graph::Vertex::IsVisited() const { return visited; }
////////////////////////////////////////////////////////////
void Graph::Vertex::SetDistance(const int & dist) { distance = dist; }
////////////////////////////////////////////////////////////
Graph::Graph(const int rank) 
    : rank(rank) 
{
#ifdef __GRAPH_LOG__
    graph_logger.SetLevel(2);
    graph_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 1, "Konstruktor klasy Graph");
#endif
    graph = new Vertex[rank];

    // Dodawanie krawędzi (budowanie grafu)
    // Dodajemy krawędzie nieskierowane do wierzchołka na prawo i pod ==>
    // dlatego ostatni rząd oraz ostatnią kolumnę osobno
    int rows = rank / settings::tiles::TILES_IN_ROW;
    int cols = rank / settings::tiles::TILES_IN_COL;
    int id = 0; 

    for (int row = 0; row < rows - 1; ++row)
    {
        for (int col = 0; col < cols - 1; ++col, ++id)
        {
            AddUndirectedEdge(id, id + 1, 1);
            AddUndirectedEdge(id, id + settings::tiles::TILES_IN_ROW, 7);
        }
        ++id;
    }

    for (int col = 0; col < cols - 1; ++col, ++id)
        AddUndirectedEdge(id, id + 1, 5);
    
    id = settings::tiles::TILES_IN_ROW - 1;

    for (int row = 0; row < rows - 1; ++row, id = id + settings::tiles::TILES_IN_ROW)
        AddUndirectedEdge(id, id + settings::tiles::TILES_IN_ROW, 7);
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
void Graph::AddUndirectedEdge(const int b, const int e, const int weight)
{
    graph[b].PushBack(Edge(e, weight));
    graph[e].PushBack(Edge(b, weight));
    // TODO: Obliczanie indeksu reverse
}
////////////////////////////////////////////////////////////
// void Graph::Wait(const int & miliseconds) const
// {
//     std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
// }
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
void Graph::Dijkstra(const int s, const int t, MyVec<AlgLog> & log)
{
#ifdef __GRAPH_LOG__
    // graph_logger.SetLevel(3);

    graph_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 0, "Dijstra(", s, ", ", t, ")");

    // Wait(1000);

    graph_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 3, "Odczekano sekunde");
#endif /* __GRAPH_LOG__ */

    MinPriorQueue<int> queue;
    AlgLog logger;

    // Dodajemy wierzchołek startowy do kolejki. 
    queue.Push(s, 0);


    // Ustawiamy wartości dla wierzchołka początkowego i końcowego
    graph[s].SetColour(0, 0, 200);
    graph[t].SetColour(0, 0, 200);


    // Ustawiamy parametry dla wierzchołka startowego
    graph[s].SetDistance(0);

    int current_vertex, edge_end, distance;

    while (!queue.IsEmpty())
    {
        // pobieramy wierzchołek z kolejki
        current_vertex = queue.Front();
        queue.Pop();

        if (current_vertex == t)
        {
            // graph[t].rect.setFillColor(sf::Color::Yellow);
            break;
        }

        graph[current_vertex].SetVisited(true);

        // przeglądamy wszystkich sąsiadów current_vertex
        for (int v = 0; v < graph[current_vertex].GetSize(); ++v)
        {
            edge_end = graph[current_vertex][v].GetEnd();


            logger.SetValues(current_vertex, edge_end);
            log.PushBack(logger);


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
void Graph::Vertex::ChangeTone(const uint& delta_r, const uint& delta_g, const uint& delta_b, const uint& delta_alpha)
{
    sf::Color color = rect.getFillColor();

    int r = color.r - delta_r, g = color.g - delta_g, b = color.b - delta_g;

    if (r < 0)
        r = 0;

    if (g < 0)
        g = 0;

    if (b < 0)
        b = 0;
    
    rect.setFillColor(sf::Color(r, g, b, 255));
}
////////////////////////////////////////////////////////////
void Graph::MakeStep(MyVec<AlgLog>& log)
{
    static int step_number = 0;
    if (step_number < log.GetSize())
    {
        // graph[ log[step_number].current ].SetColour(250, 0, 0);
        graph[ log[step_number].current ].ChangeTone(0, settings::tiles::COLOR_MODIFIER, settings::tiles::COLOR_MODIFIER);
        ++step_number;
    }
    else
        return;

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
void Graph::DrawTo(sf::RenderWindow& window) const
{
    for (int i = 0; i < rank; ++i)
    {
        // graph_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 2, "Rysuje plytke ", i);
        window.draw(graph[i].rect);
    }
}
////////////////////////////////////////////////////////////