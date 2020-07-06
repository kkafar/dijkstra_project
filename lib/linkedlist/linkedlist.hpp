// K. Kafara

#ifndef __LINKEDLIST_HPP__
#define __LINKEDLIST_HPP__

/**
 * Struktura danych mająca zastąpić std::vector.
 * Realizowana poprzez listę odsyłaczową.  
 */
template<class T> class LinkedList
{
private:
    Node * head, * tail;

public:
    struct Node
    {
        T data;
        Node * next, * prev;
    };
    

    LinkedList();
    
    ~LinkedList();

    void PushBack(const T data);

    Node * NewNode(const T data, const Node * next, const Node * prev) const;



};

#endif