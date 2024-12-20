#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class Observer {
public:
    virtual ~Observer(){}
    virtual void onEvent(const std::string& msg) = 0;
};

class ConsoleObserver : public Observer {
public:
    void onEvent(const std::string& msg) override {
        std::cout << "EVENT: " << msg << std::endl;
    }
};

class FileObserver : public Observer {
    std::string filename;
public:
    FileObserver(const std::string& fname) : filename(fname) {}
    void onEvent(const std::string& msg) override {
        std::ofstream out(filename, std::ios::app);
        out << msg << "\n";
    }
};

class Subject {
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* o) {
        observers.push_back(o);
    }
    void notify(const std::string& msg) {
        for (auto* o : observers) {
            o->onEvent(msg);
        }
    }
};