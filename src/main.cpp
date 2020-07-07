// K. Kafara

// debug, testing
#include <iostream>
#include <string>
#include "./../lib/headers.hpp"

const std::string VERSION = "v0.2_MYVEC_TEST";


int main()
{
    STAMP(VERSION);

    MyVec<int> vec(2);

    for (int i = 0; i < 300; ++i)
        vec.PushBack(i);

    for (int i = 0; i < 10; ++i)
        std::cout << vec[i] << " ";
    
    std::cout << "\n";

    vec[2] = 50;

    for (int i = 0; i < 10; ++i)
        std::cout << vec[i] << " ";

    std::cout << "\n";

    
    return 0;
}