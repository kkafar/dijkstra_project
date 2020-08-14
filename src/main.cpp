// K. Kafara

// #define QUEUE_TEST
// #define MYVEC_TEST
// #define LOG
#define SFML_TEST


////////////////////////////////////////////////////////////
// -------
////////////////////////////////////////////////////////////
// debug, testing
#include "./../lib/headers.hpp"
// #include <SFML/Graphics.hpp>
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
    myvec_logger.SetLevel(-1);
    queue_logger.SetLevel(-1);
    ////////////////////////////////////////////////////////////
#endif

#ifdef SFML_TEST
    TEST_BEG("Running SFML");
    {
        ////////////////////////////////////////////////////////////
        // Ustawienia okna
        ////////////////////////////////////////////////////////////
        constexpr size_t WINDOW_SIZE = 512;
        constexpr size_t TILE_NUMBER = 16;
        constexpr size_t TILE_SIZE = WINDOW_SIZE / TILE_NUMBER;
        const std::string WINDOW_NAME = "Visualising Dijkstra's Shortest Path Algorithm";
        ////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////
        // Utworzenie okna zgodnie z ustawieniami. 
        ////////////////////////////////////////////////////////////
        sf::RenderWindow window (sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), WINDOW_NAME);
        ////////////////////////////////////////////////////////////

        sf::RectangleShape rect;
        rect.setFillColor(sf::Color::Green);
        rect.setPosition(300, 300);


        // Graph graph(TILE_NUMBER * TILE_NUMBER);
        
        while (window.isOpen())
        {
            sf::Event event;

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) == true)
                    window.close();
                




                window.clear();
                window.draw(rect);
                window.display();
            }
        }       
    }
    TEST_END();
#endif
    return 0;
}