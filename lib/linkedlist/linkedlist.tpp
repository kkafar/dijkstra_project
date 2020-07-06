// K. Kafara

// #include "linkedlist.hpp"


template<class T> Node<T> * LinkedList<T>::NewNode(const T data, Node<T> * next, Node<T> * prev) const
{

    Node<T> * node = new Node<T>;
    node->data = data;
    node->next = next;
    node->prev = prev;
    std::cout << __FILE__ << ": " << __LINE__ << ": zarezerwowano " << sizeof(Node<T>) << " bajtow.\n";
    return node;
}

template<class T> Node<T> * LinkedList<T>::NewNode() const
{
//    static long long int allocated_mem = 0;
    Node<T> * node = new Node<T>;
//    allocated_mem += sizeof(Node<T>);
//    std::cout << __FILE__ << ": " << __LINE__ << ": zarezerwowano " << sizeof(Node<T>) << " bajty. Razem: " << allocated_mem << " ( " << node << " )\n";
    return node;
}

template<class T> LinkedList<T>::LinkedList()
{
    tail = NewNode();
    head = NewNode();
    tail->next = nullptr;
    tail->prev = head;
    head->next = tail;
    head->prev = nullptr;
}

template<class T> LinkedList<T>::~LinkedList()
{
    Node<T> * tmp = head->next;

    delete head;

    while (tmp != nullptr)
    {
        head = tmp;
        tmp = tmp->next;

        delete head;
    }
}   

template<class T> void LinkedList<T>::PushBack(const T data)
{
    Node<T> * node = NewNode(data, tail, tail->prev);
    tail->prev->next = node;
    tail->prev = node;
}

template<class T> void LinkedList<T>::PushFront(const T data)
{
    Node<T> * node = NewNode(data, head->next, head);
    head->next->prev = node;
    head->next = node;
}

template<class T> Node<T> * LinkedList<T>::begin() const
{
    return head->next;
}

template<class T> Node<T> * LinkedList<T>::end() const
{
    return tail;
}

template<class T> void LinkedList<T>::print() const
{
    Node<T> * iter = head->next;
    while (iter != tail)
    {
        std::cout << (iter->data).e << " ";
        iter = iter->next;
    }
    std::cout << "\n";
}