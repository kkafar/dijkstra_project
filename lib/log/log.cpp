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
// int Log::global_level = 2;
////////////////////////////////////////////////////////////
Log::Log(const int level) : local_level(level)
{
    // std::cout << __FILE__ << ": " << __LINE__ << ": " << "Konstruktor klasy `Log`\n";
    Message(__FILE__, __LINE__, INFO, 2, "Konstruktor klasy `Log`");
}
////////////////////////////////////////////////////////////
Log::~Log()
{
    // std::cout << __FILE__ << ": " << __LINE__ << ": " << "Destruktor klasy `Log`\n";
    Message(__FILE__, __LINE__, INFO, 2, "Destruktor klasy `Log`");
}
////////////////////////////////////////////////////////////
/* void Log::SetLevel(const int level)
{
    local_level = level;
} */
////////////////////////////////////////////////////////////
/* void Log::SetMessage(const std::string & msg)
{
    message = msg;
} */
////////////////////////////////////////////////////////////
void Log::LogMessage(const std::string & msg, const int lvl, const std::string & FILE, const int & LINE) const
{
    if (lvl <= local_level)
    {
        std::cout << FILE << ": " << LINE << ": ";

        if (lvl == 0)
            std::cout << "INFO: ";

        else if (lvl == 1)
            std::cout << "WARN: ";

        else 
            std::cout << "ERROR: ";

        std::cout << msg << "\n";
    }
}
////////////////////////////////////////////////////////////
void TEST_BEG(const std::string& test_name)
{
    std::cout << "\n==================== " << test_name << " ====================\n";
}
////////////////////////////////////////////////////////////
void TEST_END()
{
    std::cout << "============================================================\n";
}
////////////////////////////////////////////////////////////