#include "log.hpp"

void STAMP(const std::string & version)
{
    std::cout << "==================================================\n";
    std::cout << "NAME: Visualising Dijkstra's Shortest Path Algorithm\nAUTHOR: Kacper Kafara\nCOMPILATION TIME: " << __TIME__
     << "\nCOMPILATION DATE: "<< __DATE__ << "\nVERSION: " << version  << "\n==================================================\n";
}

void LOG_MESSAGE(const std::string & message, const std::string & FILE, const int & LINE)
{
    std::cout << FILE << ": " << LINE << ": " << message << "\n";
}
