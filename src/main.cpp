// K. Kafara

// #define QUEUE_TEST
// #define MYVEC_TEST
// #define LOG
#define SFML_TEST


////////////////////////////////////////////////////////////
// -------
////////////////////////////////////////////////////////////
#include "./../lib/headers.hpp"
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
    // myvec_logger.SetLevel(-1);
    // queue_logger.SetLevel(-1);
    ////////////////////////////////////////////////////////////
#endif

#ifdef SFML_TEST
    TEST_BEG("Running SFML");
    {


        ////////////////////////////////////////////////////////////
        // Utworzenie okna zgodnie z ustawieniami. 
        ////////////////////////////////////////////////////////////
        sf::RenderWindow window(sf::VideoMode(settings::window::WIDTH, settings::window::HEIGHT), settings::window::NAME);
        ////////////////////////////////////////////////////////////


        ////////////////////////////////////////////////////////////
        // Do zbierania danych o koljenych posunięciach algorytmu
        ////////////////////////////////////////////////////////////
        MyVec<AlgLog> log;
        ////////////////////////////////////////////////////////////


        ////////////////////////////////////////////////////////////
        // Tworzenie grafu.  
        ////////////////////////////////////////////////////////////
        Graph graph(settings::tiles::TILES_IN_COL * settings::tiles::TILES_IN_ROW);
        ////////////////////////////////////////////////////////////



        ////////////////////////////////////////////////////////////
        // Główna pętla programu
        ////////////////////////////////////////////////////////////
        while (window.isOpen())
        {
            sf::Event event;

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) == true)
                    window.close();
                
                window.clear();
                // window.draw(rect);
                graph.DrawTo(window);
                window.display();
            }
        }       
        ////////////////////////////////////////////////////////////
    }
    TEST_END();
#endif
    return 0;
}