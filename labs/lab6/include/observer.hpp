#pragma once

#include <string>
#include <fstream>
#include <iostream>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void Notify(const std::string& message) = 0;
};

class FileObserver: public Observer {
private:
    std::ofstream file;

public:
    FileObserver(const std::string& filename = "log.txt");
    void Notify(const std::string& message) override;
    ~FileObserver();
};

class ConsoleObserver: public Observer {
public:
    void Notify(const std::string& message) override;
};