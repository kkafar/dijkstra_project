#ifndef __LOG_HPP__
#define __LOG_HPP__

#include <iostream>

////////////////////////////////////////////////////////////
// Wyświetla informacje o nazwie, autorze, czasie ostatniej kompilacji, wersji. 
////////////////////////////////////////////////////////////
void STAMP(const std::string &);
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Wyświetla @param message wraz z informacjami nt. miejsca wywołania funkcji
////////////////////////////////////////////////////////////
void LOG_MESSAGE(const std::string & message, const std::string & FILE, const int & LINE);
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// @brief Wyświetla ramkę testową (1/2)
// @param test_name - nazwa testowanej funkcjonalności (wyświetlana w konsoli)
////////////////////////////////////////////////////////////
void TEST_BEG(const std::string& test_name = "Unknown");
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// @brief Wyświetla ramkę testową (2/2)
////////////////////////////////////////////////////////////
void TEST_END();
////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////
// Wyświetla podane w parametrach informacje (wraz z miejscem wywołania tej funkcji)
////////////////////////////////////////////////////////////
template<class... Args> void LogMessage(const std::string & FILE, const int LINE, Args... args)
{
    std::cout << FILE << ": " << LINE << ": ";
    (std::cout << ... << args);
    std::cout << "\n";
}
////////////////////////////////////////////////////////////

class Log
{
private:
    ////////////////////////////////////////////////////////////
    // 0 - tylko info
    // 1 - info oraz warning
    // 2 - info, warning, error
    ////////////////////////////////////////////////////////////
    
    int local_level;
    // bool active;
    // const std::string info;
    // const std::string warn;
    // const std::string error;
    // std::string message;
public:
    inline static int global_level = 2;
    enum MessageType {INFO = 0, WARNING = 1, ERROR = 2, OTHER = 3};
    Log(const int level = 0);
    ~Log();

    ////////////////////////////////////////////////////////////
    // @brief Ustawia maksymalny `poziom` wyświetlanych wiadomości 
    // Nadaj wyższy poziom jeżeli nie chcesz danej wiadomośći. 
    ////////////////////////////////////////////////////////////
    inline void SetLevel(const int level)
    {
        local_level = level;
    }
    ////////////////////////////////////////////////////////////



    ////////////////////////////////////////////////////////////
    // inline void SetMessage(const std::string & msg);
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    // @brief TODO
    ////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////
    void LogMessage(const std::string & msg, const int lvl, const std::string & FILE, const int & LINE) const;



    ////////////////////////////////////////////////////////////
    // Wyświetla podane w parametrach informacje (wraz z miejscem wywołania tej funkcji)
    ////////////////////////////////////////////////////////////
    template<class... Args> static void GlobalMessage(const std::string & FILE, const int LINE, MessageType type, const int lvl, Args... args)
    {
        if (lvl <= global_level)
        {
            std::cout << FILE << ": " << LINE << ": ";
            switch (type)
            {
                case INFO:
                    std::cout << "INFO: ";
                    break;

                case WARNING:
                    std::cout << "WARN: ";
                    break;

                case ERROR: 
                    std::cout << "ERROR: ";
                    break;
                
                case OTHER:
                default:
                    break;
            }
            (std::cout << ... << args);
            std::cout << "\n";
        }
    }
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    // Wyświetla podane w parametrach informacje (wraz z miejscem wywołania tej funkcji)
    ////////////////////////////////////////////////////////////
    template<class... Args> void Message(const std::string & FILE, const int LINE, MessageType type, const int lvl, Args... args)
    {
        if (lvl <= local_level)
        {
            std::cout << FILE << ": " << LINE << ": ";
            switch (type)
            {
                case INFO:
                    std::cout << "INFO: ";
                    break;

                case WARNING:
                    std::cout << "WARN: ";
                    break;

                case ERROR: 
                    std::cout << "ERROR: ";
                    break;
                
                case OTHER:
                default:
                    break;
            }
            (std::cout << ... << args);
            std::cout << "\n";
        }
    }
    ////////////////////////////////////////////////////////////
};



////////////////////////////////////////////////////////////
// NOWY SYSTEM (ZMIENNA ILOŚĆ ARGUMENTÓW)
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////










#endif