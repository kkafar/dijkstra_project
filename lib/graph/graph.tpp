// K. Kafara

template<class V, class E> Graph<V, E>::Edge::Edge(const int e, E data) : e(e), E(data) {}

template<class V, class E> Graph<V, E>::Graph(const int rank) : rank(rank)
{
    graph = new Vertex[rank];
}

template<class V, class E> Graph<V, E>::~Graph()
{
    delete[] graph;
}

template<class V, class E> void Graph<V, E>::AddDirectedEdge(const int b, const int e, E data)
{   
    graph[b].PushFront(Edge(e, data));  
}
