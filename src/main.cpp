// K. Kafara

// #define QUEUE_TEST
// #define MYVEC_TEST
// #define LOG
#define SFML_TEST


////////////////////////////////////////////////////////////
// -------
////////////////////////////////////////////////////////////
// debug, testing
#include <iostream>
#include <string>
#include "./../lib/headers.hpp"
#include <SFML/Graphics.hpp>
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// Napis informujący o wersji programu.
////////////////////////////////////////////////////////////
const std::string VERSION = "v0.6 Running SFML";
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
    myvec_logger.SetLevel(2);
    queue_logger.SetLevel(2);
    ////////////////////////////////////////////////////////////
#endif


#ifdef MYVEC_TEST
    ////////////////////////////////////////////////////////////
    // Test MyVec
    ////////////////////////////////////////////////////////////
    TEST_BEG("MyVec");
    {
        const size_t size = 5;
        MyVec<QueueNode<int>> vec;

        for (int i = 0; i < size; ++i)
            vec.PushBack(QueueNode<int>(i, i));

        for (int i = 0; i < size; ++i)
        {
            std::cout << &vec[i] << ":  (" << vec[i].object << ", " << vec[i].prior << ")\n";
        }
        
        std::cout << "\n";

        vec[2] = QueueNode<int>(50, 10);

        for (int i = 0; i < size; ++i)
        {
            std::cout << &vec[i] << ":  (" << vec[i].object << ", " << vec[i].prior << ")\n";
        }

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

        // queue_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 0, "Adres obiektu `queue`: ", &queue);

        for (int i = 0; i < size; ++i)
            queue.Push(i, i);

        // queue_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 0, "Wypisuje zawartosc wektora: ");
        for (int i = 0; i < queue.vec.GetSize(); ++i)
            std::cout << queue.vec[i].object << " ";

        std::cout << "\n" << queue.vec.GetSize() << NL;

        for (int i = 0; i < size; ++i)
        {
            std::cout << queue.Front() << "\n";
            queue.Pop(); 
        }
        std::cout << NL;

        if (queue.IsEmpty()) std::cout << "Kolejka jest pusta" << NL;
    }
    TEST_END();
    ////////////////////////////////////////////////////////////
#endif

#ifdef SFML_TEST
    TEST_BEG("Running SFML");
    {
        sf::RenderWindow window (sf::VideoMode(800, 600), "TITLE BAR");
        sf::CircleShape circle(200.f);

        circle.setFillColor(sf::Color::Green);

        while (window.isOpen())
        {
            sf::Event event;

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }

                window.clear();
                window.draw(circle);
                window.display();
            }
        }       
    }
    TEST_END();
#endif
    return 0;
}