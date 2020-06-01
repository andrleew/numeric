#pragma once

#include <iostream>

namespace NGeneral {

    class TLogger {
    public:
        TLogger();
        TLogger(std::ostream&);

        void Open(std::ostream&);
        void Error(const std::string& message);
        void Inforamtion(const std::string& message);
        void Debug(const std::string& message);

    private:
        std::string GetTime(const char delim = ':');
        void Print(const std::string& message);

    private:
        std::ostream* stream;
    };
    
} // namespace NGeneral
