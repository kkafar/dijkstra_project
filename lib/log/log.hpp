#ifndef __LOG_HPP__
#define __LOG_HPP__
#include <iostream>

void STAMP(const std::string &);

void LOG_MESSAGE(const std::string & message, const std::string & FILE, const int & LINE);




class Log
{
private:
    ////////////////////////////////////////////////////////////
    // 0 - tylko info
    // 1 - info oraz warning
    // 2 - info, warning, error
    ////////////////////////////////////////////////////////////
    int level;
    const std::string info;
    const std::string warn;
    const std::string error;
    std::string message;

public:
    Log(const int level = 0);
    ~Log();

    ////////////////////////////////////////////////////////////
    /// Ustawia maksymalny `poziom` wyświetlanych wiadomości 
    ////////////////////////////////////////////////////////////
    inline void SetLevel(const int level);

    ////////////////////////////////////////////////////////////
    // 
    ////////////////////////////////////////////////////////////
    inline void SetMessage(const std::string & msg);
    ////////////////////////////////////////////////////////////
    void LogMessage(const std::string & msg, const int lvl, const std::string & FILE, const int & LINE) const;
};


#endif