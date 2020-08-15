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
const std::string VERSION = "v0.7 Printing graph";
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
        // Timer
        ////////////////////////////////////////////////////////////
        Timer timer;
        ////////////////////////////////////////////////////////////


        ////////////////////////////////////////////////////////////
        // Do zbierania danych o koljenych posunięciach algorytmu
        ////////////////////////////////////////////////////////////
        MyVec<AlgLog> log;
        ////////////////////////////////////////////////////////////


        ////////////////////////////////////////////////////////////
        // Tworzenie grafu.  
        ////////////////////////////////////////////////////////////
        timer.Start();
        Graph graph(settings::tiles::TILES_IN_COL * settings::tiles::TILES_IN_ROW);
        timer.Stop();
        std::cout << "Czas alokacji grafu: " << timer.GetElapsedTime() << "\n";
        graph.Dijkstra(settings::START, settings::END, log);
        ////////////////////////////////////////////////////////////


        ////////////////////////////////////////////////////////////
        // Utworzenie okna zgodnie z ustawieniami. 
        ////////////////////////////////////////////////////////////
        sf::RenderWindow window(sf::VideoMode(settings::window::WIDTH, settings::window::HEIGHT), settings::window::NAME);
        window.setFramerateLimit(settings::window::MAX_FRAMERATE);
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
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(settings::FRAME_WAIT_TIME));
            window.clear();
            graph.DrawTo(window);
            window.display();
            graph.MakeStep(log);
        }       
        ////////////////////////////////////////////////////////////
    }
    TEST_END();
#endif
    return 0;
}