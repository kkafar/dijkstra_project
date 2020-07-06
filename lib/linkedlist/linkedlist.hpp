// K. Kafara

#ifndef __LINKEDLIST_HPP__
#define __LINKEDLIST_HPP__
#include <iostream>
/**
 * Struktura danych mająca zastąpić std::vector.
 * Realizowana poprzez listę odsyłaczową.  
 */

    /* Struktura reprezentująca węzeł */

template<class T> struct Node
{
    T data;
    Node * next, * prev;
};


template<class T> class LinkedList
{
private:
    Node<T> * head, * tail;

public:
    LinkedList();
    
    ~LinkedList();

    /**
     * Dodaje element @param data na początek listy.
     */
    void PushFront(const T data);

    /**
     * Dodaje element @param data na koniec listy. 
     */
    void PushBack(const T data);

    Node<T> * NewNode(const T data, Node<T> * next, Node<T> * prev) const;
    Node<T> * NewNode() const;

    /**
     * Zwraca adres pierwszego elementu na liście lub jeżeli lista jest pusta adres wartownika końcowego
     */
    Node<T> * begin() const;
    /**
     * Zwraca adres wartownika końcowego.
     */
    Node<T> * end() const;

    /**
     * Wypisuje zawartość listy
     */
    void print() const;
};

#include "linkedlist.tpp"


typedef LinkedList<int> INT_LL;


#endif