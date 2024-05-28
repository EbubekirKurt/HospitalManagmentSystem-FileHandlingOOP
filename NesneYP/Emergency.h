#ifndef EMERGENCY_H
#define EMERGENCY_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <algorithm>
using namespace std;

class EmergencyRoom {
public:
    EmergencyRoom();
    static void createERentry(const string& id, const string& name);
    void createERentry();

    friend void loadNurses();
    friend void loadDoctors();

private:
    static vector<string> diseases;
    static vector<string> nurses;
    static vector<string> doctors;

    static string getRandomNurse();
    static string getRandomDoctor();
};



#endif