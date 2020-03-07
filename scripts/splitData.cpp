#include <chrono>
#include <fstream>
#include <iostream>
#include "../src/Student.h"

const std::string DIR_NAME = "info";
const int SPACING = 15;

std::vector<Student> readFromFile(std::string fileName);
void split(std::vector<Student> &below5, std::vector<Student> &aboveOrEqual5,
           std::vector<Student> allStudents);
void writeToFile(std::string fileName, std::vector<Student> students);

int main() {
    srand(time(NULL));

    std::string fileName;

    std::cout << "Įveskite failo, kurį norite padalinti ir kuris yra '" +
                     DIR_NAME +
                     "' kataloge, pavadinimą (pvz. "
                     "stundentai.txt).\n>>";
    std::cin >> fileName;

    std::vector<Student> studentsBelow5;
    std::vector<Student> studentsAboverOrEqual5;

    std::chrono::steady_clock::time_point beginRead =
        std::chrono::steady_clock::now();

    std::vector<Student> students = readFromFile(fileName);

    std::chrono::steady_clock::time_point endRead =
        std::chrono::steady_clock::now();

    std::cout << "Skaitymo laikas: "
              << (double)std::chrono::duration_cast<std::chrono::milliseconds>(
                     endRead - beginRead)
                         .count() /
                     1000
              << "s" << std::endl;

    std::chrono::steady_clock::time_point beginSplit =
        std::chrono::steady_clock::now();

    split(studentsBelow5, studentsAboverOrEqual5, students);

    std::chrono::steady_clock::time_point endSplit =
        std::chrono::steady_clock::now();

    std::cout << "Rūšiavimo laikas: "
              << (double)std::chrono::duration_cast<std::chrono::milliseconds>(
                     endSplit - beginSplit)
                         .count() /
                     1000
              << "s" << std::endl;

    std::chrono::steady_clock::time_point beginWrite =
        std::chrono::steady_clock::now();

    writeToFile("nuskriaustukai.txt", studentsBelow5);
    writeToFile("kietekai.txt", studentsAboverOrEqual5);

    std::chrono::steady_clock::time_point endWrite =
        std::chrono::steady_clock::now();

    std::cout << "Rašymo laikas: "
              << (double)std::chrono::duration_cast<std::chrono::milliseconds>(
                     endWrite - beginWrite)
                         .count() /
                     1000
              << "s" << std::endl;

    std::cout << "Failai sukurti '" << DIR_NAME << "' kataloge.\n";

    return 0;
}

std::vector<Student> readFromFile(std::string fileName) {
    std::vector<Student> students;
    std::ifstream file;
    file.open("../" + DIR_NAME + "/" + fileName);

    if (!file) {
        std::cout << "Nepavyko nuskaityti failo \"" + fileName + "\".\n";
    } else {
        std::string input;
        int hwAmount = 0;
        file >> input;
        file >> input;
        file >> input;
        while (input[0] == 'N' && input[1] == 'D') {
            file >> input;
            hwAmount++;
        }

        while (!file.eof()) {
            std::string sName, fName;
            std::vector<int> hw;
            int exam;
            file >> sName;
            file >> fName;
            for (int i = 0; i < hwAmount; i++) {
                int result;
                file >> result;
                hw.push_back(result);
            }
            file >> exam;

            if (!file.eof()) {
                students.push_back(Student(sName, fName, hw, exam));
            }
        }
        file.close();
    }
    return students;
}

void split(std::vector<Student> &below5, std::vector<Student> &aboveOrEqual5,
           std::vector<Student> allStudents) {
    for (int i = 0; i < allStudents.size(); i++) {
        double finalScore = allStudents[i].getAverage();
        if (finalScore < 5) {
            below5.push_back(allStudents[i]);
        } else {
            aboveOrEqual5.push_back(allStudents[i]);
        }
    }
}

void writeToFile(std::string fileName, std::vector<Student> students) {
    std::ofstream file("../" + DIR_NAME + "/" + fileName);

    file << std::left << std::setw(SPACING) << "Vardas" << std::setw(SPACING)
         << "Pavardė";
    int hwAmount;

    hwAmount = students.size() > 0 ? students[0].getHw().size() : 0;

    for (int j = 1; j < hwAmount; j++) {
        file << std::left << "ND" << std::setw(SPACING) << j;
    }
    file << "Egz.\n";

    for (int i = 1; i < students.size(); i++) {
        file << std::left << std::setw(SPACING) << students[i].getFName()
             << std::setw(SPACING) << students[i].getSName();
        for (int j = 1; j < hwAmount; j++) {
            file << std::left << std::setw(SPACING) << students[i].getHw()[j];
        }
        file << std::left << students[i].getExam() << "\n";
    }
}