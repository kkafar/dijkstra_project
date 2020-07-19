// K. Kafara

#define QUEUE_TEST
// #defines MYVEC_TEST
#define LOG


////////////////////////////////////////////////////////////
// -------
////////////////////////////////////////////////////////////
// debug, testing
#include <iostream>
#include <string>
#include "./../lib/headers.hpp"
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// Napis informujący o wersji programu.
////////////////////////////////////////////////////////////
const std::string VERSION = "v0.4 myvec-log";
////////////////////////////////////////////////////////////



int main()
{
    ////////////////////////////////////////////////////////////
    // Wyświetlanie informacji o programie.
    ////////////////////////////////////////////////////////////
    STAMP(VERSION);
    ////////////////////////////////////////////////////////////

#ifdef LOG
    ////////////////////////////////////////////////////////////
    // Ustawienia poszeczególnych loggerów.
    ////////////////////////////////////////////////////////////
    myvec_logger.SetLevel(3);
    queue_logger.SetLevel(3);
    ////////////////////////////////////////////////////////////
#endif


#ifdef MYVEC_TEST
    ////////////////////////////////////////////////////////////
    // Test MyVec
    ////////////////////////////////////////////////////////////
    TEST_BEG("MyVec");
    {
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
    }
    TEST_END();
    ////////////////////////////////////////////////////////////
#endif

#ifdef QUEUE_TEST
    ////////////////////////////////////////////////////////////
    // Test MinPriorQueue
    ////////////////////////////////////////////////////////////
    TEST_BEG("Queue");
    {
        const int size = 5;
        MinPriorQueue<int> queue;

        for (int i = 0; i < size; ++i)
            queue.Push(i, i);

        queue_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 0, "Wypisuje zawartosc wektora: ");
        for (int i = 0; i < queue.vec.GetSize(); ++i)
            std::cout << queue.vec[i].object << " ";

        std::cout << "\n" << queue.vec.GetSize() << NL;

        for (int i = 0; i < size; ++i)
        {
            std::cout << queue.Front() << " ";
            queue.Pop();
        }
        std::cout << NL;

        if (queue.IsEmpty()) std::cout << "Kolejka jest pusta" << NL;
    }
    TEST_END();
    ////////////////////////////////////////////////////////////
#endif
    return 0;
}