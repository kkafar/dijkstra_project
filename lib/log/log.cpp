#include "log.hpp"

////////////////////////////////////////////////////////////
void STAMP(const std::string & version)
{
    std::cout << "==================================================\n";
    std::cout << "NAME: Visualising Dijkstra's Shortest Path Algorithm\nAUTHOR: Kacper Kafara\nCOMPILATION TIME: " << __TIME__
     << "\nCOMPILATION DATE: "<< __DATE__ << "\nVERSION: " << version  << "\n==================================================\n";
}
////////////////////////////////////////////////////////////
void LOG_MESSAGE(const std::string & message, const std::string & FILE, const int & LINE)
{
    std::cout << FILE << ": " << LINE << ": " << message << "\n";
}
////////////////////////////////////////////////////////////
Log::Log(const int level) : level(level), info("info: "), warn("warning: "), error("error: ")
{
    std::cout << __FILE__ << ": " << __LINE__ << ": " << "Konstruktor klasy `Log`\n";
}
////////////////////////////////////////////////////////////
Log::~Log()
{
    std::cout << __FILE__ << ": " << __LINE__ << ": " << "Destruktor klasy `Log`\n";
}
////////////////////////////////////////////////////////////
void Log::SetLevel(const int level)
{
    Log::level = level;
}
////////////////////////////////////////////////////////////
void Log::SetMessage(const std::string & msg)
{
    message = msg;
}
////////////////////////////////////////////////////////////
void Log::LogMessage(const std::string & msg, const int lvl, const std::string & FILE, const int & LINE) const
{
    if (lvl <= level)
    {
        std::cout << FILE << ": " << LINE << ": ";

        if (lvl == 0)
            std::cout << info;

        else if (lvl == 1)
            std::cout << warn;

        else 
            std::cout << error;

        std::cout << msg << "\n";
    }
}
////////////////////////////////////////////////////////////