#include <fstream>
#include <iomanip>
#include <iostream>

const std::string DIR_NAME = "info";
const int SPACING = 15;

void writeToFile(std::string fileName, int hwAmount, int amount);

int main() {
    std::string fileName;
    int amount;
    int hwAmount;

    std::cout << "Įveskite failo, kurį norite sukurti, pavadinimą (pvz. "
                 "studentai.txt):\n>>";
    std::cin >> fileName;
    std::cout << "Įveskite studentų kiekį:\n>>";
    std::cin >> amount;
    std::cout << "Įveskite namų darbų kiekį:\n>>";
    std::cin >> hwAmount;

    writeToFile(fileName, hwAmount, amount);
}

void writeToFile(std::string fileName, int hwAmount, int amount) {
    srand(time(NULL));

    std::ofstream file("../" + DIR_NAME + "/" + fileName);

    file << std::left << std::setw(SPACING) << "Vardas" << std::setw(SPACING)
         << "Pavardė";
    for (int j = 1; j <= hwAmount; j++) {
        file << std::left << "ND" << std::setw(SPACING) << j;
    }
    file << "Egz.\n";

    for (int i = 1; i <= amount; i++) {
        file << std::left << "Vardas" << std::setw(SPACING) << i << "Pavardė"
             << std::setw(SPACING) << i;
        for (int j = 1; j <= hwAmount; j++) {
            file << std::left << std::setw(SPACING) << rand() % 10 + 1;
        }
        file << std::left << std::setw(SPACING) << rand() % 10 + 1 << "\n";
    }

    std::cout << "Failas sukurtas '" << DIR_NAME << "' kataloge.\n";
}