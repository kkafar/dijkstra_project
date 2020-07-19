// K. Kafara

#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

#include "../MyVec/MyVec.hpp"
#include "../log/log.hpp"
#include <stdlib.h>
// testy
#include <iostream>

////////////////////////////////////////////////////////////
// Element kolejki. Stowarzyszamy obiekt wstawiany do kolejki z piorytetem.
////////////////////////////////////////////////////////////
template<class Type> struct QueueNode
{
    ////////////////////////////////////////////////////////////
    Type object;
    int prior;
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    // @brief Konstruktor klasy QueueNode<Type> (PARAM)
    // @param object - referencja do obiektu dodawanego do kolejki
    ////////////////////////////////////////////////////////////
    QueueNode(Type object, int prior);
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    // @brief Konstruktor klasy QueueNode<Type> (NO_PARAM)
    ////////////////////////////////////////////////////////////
    QueueNode();
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    // @brief Konstruktor kopiujący klasy QueueNode<Type> (PARAM)
    ////////////////////////////////////////////////////////////
    QueueNode(const QueueNode<Type>&);
    ////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////
    // @brief Destruktor klasy QueueNode<Type>
    ////////////////////////////////////////////////////////////
    ~QueueNode();
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    // @brief Operator przypisania
    ////////////////////////////////////////////////////////////
    QueueNode<Type>& operator = (const QueueNode<Type> &);
    ////////////////////////////////////////////////////////////
};
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Szablon klasy kolejki priorytetowej typu minimum. 
// Implementowana przez kopiec minimum. Złożoność operacji 
// wstawiania/ściągania z kolejki jest logarytmiczna. 
////////////////////////////////////////////////////////////
template<class Type> class MinPriorQueue
{
private:
public:
    ////////////////////////////////////////////////////////////
    MyVec<QueueNode<Type>> vec;
    ////////////////////////////////////////////////////////////

public:
    ////////////////////////////////////////////////////////////
    // @brief Konstruktor
    ////////////////////////////////////////////////////////////
    MinPriorQueue();
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    // @brief Destruktor
    ////////////////////////////////////////////////////////////
    ~MinPriorQueue();
    ////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////
    // @brief Zwraca indeks rodzica "wierzchołka" @param index
    // @attr nodiscard
    ////////////////////////////////////////////////////////////    
    [[nodiscard]] int Parent(const int index) const;
    ////////////////////////////////////////////////////////////    
    
    ////////////////////////////////////////////////////////////
    // @brief Zwraca indeks prawego dziecka "wierzchołka" @param index
    // @attr nodiscard
    ////////////////////////////////////////////////////////////    
    [[nodiscard]] int Right(const int index) const;
    ////////////////////////////////////////////////////////////    
    
    ////////////////////////////////////////////////////////////
    // @brief Zwraca indeks lewego dziecka "wierzchołka" @param index
    // @attr nodiscard
    ////////////////////////////////////////////////////////////    
    [[nodiscard]] int Left(const int index) const;
    ////////////////////////////////////////////////////////////    
    
    
    ////////////////////////////////////////////////////////////
    // @brief Przywraca własność kopca minimum
    ////////////////////////////////////////////////////////////
    void Heapify(int index);
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    // @brief Dodaje @param obj do kolejki z priorytetem @param priority
    ////////////////////////////////////////////////////////////
    void Push(Type obj, const int priority);
    ////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////
    // @brief Zwraca (referencja) pierwszy element w kolejce (o najniższym priorytecie)
    // @attr nodiscard
    ////////////////////////////////////////////////////////////
    [[nodiscard]] Type& Front() const;
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    // @brief Usuwa z kolejki element o najmniejszym priorytecie
    ////////////////////////////////////////////////////////////
    void Pop();
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    // @brief Zwraca true jeżeli kolejka jest pusta, wpp - false
    ////////////////////////////////////////////////////////////
    [[nodiscard]] bool IsEmpty() const;
    ////////////////////////////////////////////////////////////
    
};
////////////////////////////////////////////////////////////

#include "queue.tpp"



#endif

