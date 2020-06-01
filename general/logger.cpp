#include "logger.h"

#include <chrono>

using namespace NGeneral;

TLogger::TLogger(){}

TLogger::TLogger(std::ostream& _stream) {
    stream = &_stream;
}

void TLogger::Open(std::ostream& os) {
    stream = &os;
}

std::string TLogger::GetTime(const char delim) {
    auto now = std::chrono::high_resolution_clock::now();

    return std::string("<") + 
           std::to_string(std::chrono::duration_cast<std::chrono::hours>(now.time_since_epoch()).count() % 24) +
           delim +
           std::to_string(std::chrono::duration_cast<std::chrono::minutes>(now.time_since_epoch()).count() % 60) +
           delim +
           std::to_string(std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count() % 60) +
           delim +
           std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000) +
           delim +
           std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count() % 1000) +
           ">";
}

void TLogger::Print(const std::string& message) {
    (*stream) << GetTime() << message << std::endl;
}

void TLogger::Error(const std::string& message) {
    Print(std::string(" [ERROR] ") + message);
}

void TLogger::Debug(const std::string& message) {
    Print(std::string(" [DEBUG] ") + message);
}

void TLogger::Inforamtion(const std::string& message) {
    Print(std::string(" [INFO] ") + message);
}