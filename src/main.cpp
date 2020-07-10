// K. Kafara

// debug, testing
#include <iostream>
#include <string>
#include "./../lib/headers.hpp"

const std::string VERSION = "v0.3 queue-dev";


int main()
{
    STAMP(VERSION);

    MyVec<int> vec(2);

    for (int i = 0; i < 5; ++i)
        vec.PushBack(i);

    for (int i = 0; i < 5; ++i)
        std::cout << vec[i] << " ";
    
    std::cout << "\n";

    vec[2] = 50;

    for (int i = 0; i < 5; ++i)
        std::cout << vec[i] << " ";

    std::cout << "\n" << vec.GetSize() << "\n";
    // vec.GetSize();

/* 
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++\n";
    MinPriorQueue<int> queue;

    for (int i = 0; i < 10; ++i)
        queue.Push(i, 10 - i);

    for (int i = 0; i < 10; ++i)
    {
        std::cout << queue.Front() << " ";
        queue.Pop();
    }

    std::cout << "\n++++++++++++++++++++++++++++++++++++++++++++\n"; */
    return 0;
}