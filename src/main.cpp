// K. Kafara

// debug, testing
#include <iostream>
#include <string>
#include "./../lib/headers.hpp"

int main()
{
    LOG_MESSAGE();

    LinkedList<int> ll;

    for (int i = 0; i < 10; ++i)
    {
        ll.PushBack(i);
    }

    ll.print();

    ll.PushFront(11);

    ll.print();
    return 0;
}