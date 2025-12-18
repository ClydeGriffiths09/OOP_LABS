#include <stdexcept> 

#include "observer.hpp"

// class FileObserver
FileObserver::FileObserver(const std::string& filename): file(filename, std::ios::app) {
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open log file: " + filename);
    }
}

void FileObserver::Notify(const std::string& message) {
    file << "[LOG] " << message << std::endl;
    file.flush();
}

FileObserver::~FileObserver() {
    if (file.is_open()) {
        file.close();
    }
}

// class ConsoleObserver
void ConsoleObserver::Notify(const std::string& message) {
    std::cout << "[CONSOLE] " << message << std::endl;
}