#pragma once

#include <fstream>

#include "observer.hpp"

class FileObserver: public Observer {
private:
    std::ofstream file;

public:
    FileObserver(const std::string& filename = "log.txt");
    void Notify(const std::string& message) override;
    ~FileObserver();
};