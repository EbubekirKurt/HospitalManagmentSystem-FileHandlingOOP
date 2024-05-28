#include "Emergency.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

vector<string> EmergencyRoom::diseases = {
    "Heart Attack", "Stroke", "Severe Asthma Attack", "Traumatic Injury",
    "Unconsciousness", "Severe Burn", "Severe Allergic Reaction",
    "Poisoning", "Severe Bleeding", "Severe Abdominal Pain",
    "Severe Chest Pain", "Severe Head Injury", "Severe Infection",
    "Severe Dehydration", "Severe Difficulty Breathing"
};

vector<string> EmergencyRoom::nurses;
vector<string> EmergencyRoom::doctors;

EmergencyRoom::EmergencyRoom() {}

void loadNurses() {
    ifstream inFile("Nurses.txt");
    string line;
    string nurseName;
    while (getline(inFile, line)) {
        if (line.find("Name: ") == 0) {
            nurseName = line.substr(6);
            EmergencyRoom::nurses.push_back(nurseName);
        }
        for (int i = 0; i < 3; ++i) {
            getline(inFile, line);
        }
    }
    if (inFile.fail() && !inFile.eof()) {
        cerr << "Error reading Nurses.txt file.\n";
    }
    inFile.close();
}

void loadDoctors() {
    ifstream inFile("Doctors.txt");
    string line;
    string doctorName;
    while (getline(inFile, line)) {
        if (line.find("Name: ") == 0) {
            doctorName = line.substr(6); // Extract the name after "Name: "
            EmergencyRoom::doctors.push_back(doctorName);
        }
        // Skip the next 3 lines
        for (int i = 0; i < 3; ++i) {
            getline(inFile, line);
        }
    }
    if (inFile.fail() && !inFile.eof()) {
        cerr << "Error reading Doctors.txt file.\n";
    }
    inFile.close();
}

string EmergencyRoom::getRandomNurse() {
    if (nurses.empty()) {
        loadNurses();
    }
    srand(time(0));
    int index = rand() % nurses.size();
    return nurses[index];
}

string EmergencyRoom::getRandomDoctor() {
    if (doctors.empty()) {
        loadDoctors();
    }
    srand(time(0));
    int index = rand() % doctors.size();
    return doctors[index];
}

void EmergencyRoom::createERentry() {
    string id, name, disease;

    cout << "Enter your ID (11 digits): ";
    cin >> id;
    while (id.length() != 11 || !all_of(id.begin(), id.end(), ::isdigit)) {
        cout << "Invalid ID. Please enter a 11-digit number: ";
        cin >> id;
    }

    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Select a disease from the following list by entering the corresponding number:\n";
    for (size_t i = 0; i < diseases.size(); ++i) {
        cout << i + 1 << ". " << diseases[i] << endl;
    }

    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    while (choice < 1 || choice > 15) {
        cout << "Invalid choice. Please enter a number between 1 and 15: ";
        cin >> choice;
    }

    disease = diseases[choice - 1];

    string assignedNurse = getRandomNurse();
    string assignedDoctor = getRandomDoctor();

    ofstream outFile("emergencyroom.txt", ios::app);
    if (outFile.is_open()) {
        outFile << "ID: " << id << ", Name: " << name << ", Disease: " << disease
            << ", Nurse: " << assignedNurse << ", Doctor: " << assignedDoctor << endl;
        outFile.close();
        cout << "Entry recorded successfully.\n";
        this_thread::sleep_for(chrono::seconds(10));
    }
    else {
        cerr << "Error opening file.\n";
    }
}

void EmergencyRoom::createERentry(const string& id, const string& name) {
    string disease;

    cout << "Select a disease from the following list by entering the corresponding number:\n";
    for (size_t i = 0; i < diseases.size(); ++i) {
        cout << i + 1 << ". " << diseases[i] << endl;
    }

    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    while (choice < 1 || choice > 15) {
        cout << "Invalid choice. Please enter a number between 1 and 15: ";
        cin >> choice;
    }

    disease = diseases[choice - 1];

    string assignedNurse = getRandomNurse();
    string assignedDoctor = getRandomDoctor();

    ofstream outFile("emergencyroom.txt", ios::app);
    if (outFile.is_open()) {
        outFile << "ID: " << id << ", Name: " << name << ", Disease: " << disease
            << ", Nurse: " << assignedNurse << ", Doctor: " << assignedDoctor << endl;
        outFile.close();
        cout << "Entry recorded successfully.\n";
        this_thread::sleep_for(chrono::seconds(10));
    }
    else {
        cerr << "Error opening file.\n";
    }
}