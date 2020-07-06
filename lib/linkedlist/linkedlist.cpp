// K. Kafara

#include "linkedlist.hpp"

template<class T> LinkedList<T>::Node * LinkedList<T>::NewNode(const T data, const Node * next, const Node * prev) const
{
    Node * node = new Node;
    node->data = data;
    node->next = next;
    node->prev = prev;
    return Node;
}


template<class T> LinkedList<T>::LinkedList()
{
    tail = NewNode((T)(0), nullptr, nullptr);
    head = NewNode((T)(0), tail, nullptr);
}

template<class T> LinkedList<T>::~LinkedList()
{
    Node * tmp = head->next;

    delete head;

    while (tmp != nullptr)
    {
        head = tmp;
        tmp = tmp->next;

        delete head;
    }
}