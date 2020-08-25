// K. Kafara

// #define QUEUE_TEST
// #define MYVEC_TEST
#define LOG
#define SFML_TEST


////////////////////////////////////////////////////////////
// -------
////////////////////////////////////////////////////////////
#include "./../lib/headers.hpp"
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// Napis informujący o wersji programu.
////////////////////////////////////////////////////////////
const std::string VERSION = "v0.8 Improving algos & visual.";
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
    Log main_logger;
    main_logger.SetLevel(3);
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
        // Flagi do sterowania pracą programu
        ////////////////////////////////////////////////////////////
        bool is_makestep_finished = false;
        bool display_main_screen = false;
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

        main_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 0, "Czas tworzenia grafu: ", timer.GetElapsedTime());

        graph.Print();

        // Algorytm Dijkstry
        timer.Start();
        graph.Dijkstra(settings::START, settings::END, log);
        timer.Stop();

        main_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 2, "Zakonczono prace algorytmu, czas: ", timer.GetElapsedTime());
        ////////////////////////////////////////////////////////////


        ////////////////////////////////////////////////////////////
        // Utworzenie okna zgodnie z ustawieniami. 
        ////////////////////////////////////////////////////////////
        sf::RenderWindow window(sf::VideoMode(settings::window::WIDTH, settings::window::HEIGHT), settings::window::NAME);
        window.setFramerateLimit(settings::window::MAX_FRAMERATE);

        main_logger.Message(__FILE__, __LINE__, Log::MessageType::INFO, 2, "Utworzono okno programu");
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

                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Space)
                        display_main_screen = true;
                }


            }



            std::this_thread::sleep_for(std::chrono::milliseconds(settings::FRAME_WAIT_TIME));



            window.clear();

            if (display_main_screen)
            {
                graph.DrawTo(window);
            }

            else
            {
                // 
            }
            

            window.display();

            if (display_main_screen && !is_makestep_finished)
            {
                is_makestep_finished = graph.MakeStep(log);
            }
        }       
        ////////////////////////////////////////////////////////////
    }
    TEST_END();
#endif
    return 0;
}