#include <bits/stdc++.h>
#include <iomanip>
#include <iostream>

#define RANDOM "random"
#define STOP "stop"
#define AVG "vidurkis"
#define MEDIAN "mediana"

struct Student {
    std::string fname;
    std::string sname;
    double average;
    double median;
};

int userAmountInput();
char isHwAmountInput();
int hwAmountInput(char isHwAmount);
int *hwInput(char isHwAmount, int &hwAmount);
int examInput();
Student *inputStudents(int users);
std::string finalScoreTypeInput();
void reallocateArray(int size, int oldArr[]);
double finalAverage(int hw[], int hwAmount, int exam);
double finalMedian(int hw[], int hwAmount);
void printResults(Student students[], int users, std::string finalScoreType);

int main() {
    srand(time(NULL));

    int users = userAmountInput();

    Student *students = inputStudents(users);

    std::string finalScoreType = finalScoreTypeInput();

    printResults(students, users, finalScoreType);

    return 0;
}

Student *inputStudents(int users) {
    Student *students = new Student[users];

    for (int i = 0; i < users; i++) {
        users > 1 ? std::cout << i + 1 << " studento vardas:" << std::endl
                  : std::cout << "Vardas:" << std::endl;
        std::cout << ">> ";
        std::cin >> students[i].fname;

        users > 1 ? std::cout << i + 1 << " studento pavardė:" << std::endl
                  : std::cout << "Pavardė:" << std::endl;
        std::cout << ">> ";
        std::cin >> students[i].sname;

        char isHwAmount = isHwAmountInput();

        int hwAmount = hwAmountInput(isHwAmount);

        int *hw = hwInput(isHwAmount, hwAmount);

        int exam = examInput();

        students[i].average = finalAverage(hw, hwAmount, exam);
        students[i].median = finalMedian(hw, hwAmount);
    }
    return students;
}

int userAmountInput() {
    int users;
    std::cout << "Įveskite studentų kiekį:" << std::endl;
    std::cout << ">> ";
    std::cin >> users;
    while (std::cin.fail() || (users < 0 || users > INT_MAX)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Klaida: studentų kiekis turi būti nurodytas "
                     "skaičiumi nuo 1 iki 10.\nĮveskite iš "
                     "naujo:\n >> ";
        std::cin >> users;
    }
    return users;
}

char isHwAmountInput() {
    char isHwAmount;
    std::cout << "Ar norite įvesti namų darbų kiekį? (y/n)" << std::endl;
    std::cout << ">> ";
    std::cin >> isHwAmount;
    while (isHwAmount != 'y' && isHwAmount != 'n') {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Klaida: įrašykite vieną iš šių raidžių - y (taip) "
                     "arba n "
                     "(ne):"
                  << std::endl
                  << ">> ";
        std::cin >> isHwAmount;
    }
    return isHwAmount;
}

int hwAmountInput(char isHwAmount) {
    int hwAmount;
    if (isHwAmount == 'y') {
        std::cout << "Namų darbų kiekis:" << std::endl;
        std::cout << ">> ";
        std::cin >> hwAmount;
        while (std::cin.fail() || (hwAmount < 0 || hwAmount > INT_MAX)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Klaida: namų darbų kiekis turi būti nurodytas "
                         "skaičiumi "
                         "didesniu nei 0.\nĮveskite iš naujo:\n >>";
            std::cin >> hwAmount;
        }
        return hwAmount;
    }
    return 0;
}

int *hwInput(char isHwAmount, int &hwAmount) {
    int *hw = new int[hwAmount];

    if (isHwAmount == 'y') {
        for (int i = 0; i < hwAmount; i++) {
            bool invalid = false;
            std::string hwInput;
            do {
                if (invalid) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                    '\n');
                    std::cout << "Klaida: rezultatas turi būti nurodytas "
                                 "skaičiumi nuo 1 iki 10"
                              << std::endl;
                }
                std::cout << "Jei norite sugeneruoti atsitiktinį "
                             "skaičių, "
                             "rašykite '" RANDOM
                          << "'.\n";
                std::cout << i + 1 << " namų darbo rezultatas:" << std::endl;
                std::cout << ">> ";
                std::cin >> hwInput;
                if (hwInput == RANDOM) {
                    hw[i] = rand() % 10 + 1;
                    std::cout << "Sugeneruotas skaičius: " << hw[i]
                              << std::endl;
                    invalid = false;
                } else {
                    try {
                        hw[i] = stoi(hwInput);
                        invalid = hw[i] <= 0 || hw[i] > 10 ? true : false;
                    } catch (const std::invalid_argument &e) {
                        invalid = true;
                    } catch (const std::out_of_range &e) {
                        invalid = true;
                    }
                }
            } while (hw[i] <= 0 || hw[i] > 10);
        }
    } else {
        std::string hwInput;
        bool stop = false;
        while (!stop) {
            bool invalid = false;
            do {
                if (invalid) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                    '\n');
                    std::cout << "Klaida: rezultatas turi būti nurodytas  "
                                 "skaičiumi "
                                 "nuo "
                                 "1 "
                                 "iki "
                                 "10\n";
                }
                std::cout
                    << "Jei įvedėte visus namų darbų rezultatus, rašykite "
                       "'"
                    << STOP
                    << "'. Jei norite sugeneruoti atsitiktinį "
                       "skaičių, "
                       "rašykite '"
                    << RANDOM << "'." << std::endl;
                std::cout << hwAmount + 1
                          << " namų darbo rezultatas:" << std::endl;
                std::cout << ">> ";
                std::cin >> hwInput;

                if (hwInput == STOP) {
                    stop = true;
                    break;
                }

                reallocateArray(hwAmount, hw);

                if (hwInput == RANDOM) {
                    hw[hwAmount] = rand() % 10 + 1;
                    std::cout << "Suegeneruotas skaičius: " << hw[hwAmount]
                              << std::endl;
                    invalid = false;
                } else {
                    try {
                        hw[hwAmount] = stoi(hwInput);
                        invalid = hw[hwAmount] <= 0 || hw[hwAmount] > 10
                                      ? true
                                      : false;
                    } catch (const std::invalid_argument &e) {
                        invalid = true;
                    } catch (const std::out_of_range &e) {
                        invalid = true;
                    }
                }
            } while (hw[hwAmount] <= 0 || hw[hwAmount] > 10 || invalid);
            if (!stop) hwAmount++;
        }
    }
    return hw;
}

int examInput() {
    int exam = 0;
    std::string examInput;
    bool invalid = false;
    do {
        if (invalid) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Klaida: rezultatas turi būti nurodytas  skaičiumi "
                         "nuo "
                         "1 "
                         "iki "
                         "10\n";
        }
        std::cout << "Jei norite sugeneruoti atsitiktinį skaičių, rašykite "
                     "'"
                  << RANDOM << "'.\nEgzamino rezultatas:" << std::endl;
        std::cout << ">> ";
        std::cin >> examInput;
        if (examInput == RANDOM) {
            exam = rand() % 10 + 1;
            std::cout << "Suegeneruotas skaičius: " << exam << std::endl;
            invalid = false;
        } else {
            try {
                exam = stoi(examInput);
                invalid = exam <= 0 || exam > 10 ? true : false;
            } catch (const std::invalid_argument &e) {
                invalid = true;
            } catch (const std::out_of_range &e) {
                invalid = true;
            }
        }
    } while (exam <= 0 || exam > 10 || invalid);

    return exam;
}

std::string finalScoreTypeInput() {
    std::string finalScoreType;
    std::cout << "Kaip atvaizduoti galutinį rezultatą? (" << AVG << '/'
              << MEDIAN << ")" << std::endl;
    std::cout << ">> ";
    std::cin >> finalScoreType;
    while (finalScoreType != AVG && finalScoreType != MEDIAN) {
        std::cout << "Klaida: įveskite vieną iš šių žodžių - " AVG << '/'
                  << MEDIAN << std::endl;
        std::cout << ">> ";
        std::cin >> finalScoreType;
    }
    return finalScoreType;
}

void reallocateArray(int size, int oldArr[]) {
    int *newArr = new int[size + 1];
    for (int i = 0; i < size; i++) newArr[i] = oldArr[i];
    delete[] oldArr;
    oldArr = newArr;
}

double finalAverage(int hw[], int hwAmount, int exam) {
    int sum = 0;
    for (int i = 0; i < hwAmount; i++) sum += hw[i];
    double hwAverage;
    if (hwAmount > 0) hwAverage = (double)sum / hwAmount;

    return 0.4 * hwAverage + 0.6 * exam;
}

double finalMedian(int hw[], int hwAmount) {
    std::sort(hw, hw + hwAmount);
    if (hwAmount % 2 == 0)
        return (double)(hw[hwAmount / 2 - 1] + hw[hwAmount / 2]) / 2;
    else
        return (double)hw[hwAmount / 2];
}

void printResults(Student students[], int users, std::string finalScoreType) {
    int spacing = 25;
    std::string type = finalScoreType == AVG ? "Vid." : "Med.";
    std::cout << std::left << std::setw(spacing) << "Pavardė"
              << std::setw(spacing) << "Vardas"
              << "Galutinis (" << type << ')' << std::endl;
    std::cout
        << "-----------------------------------------------------------------"
        << std::endl;
    for (int i = 0; i < users; i++) {
        double score =
            finalScoreType == AVG ? students[i].average : students[i].median;
        std::cout << std::left << std::setw(spacing) << students[i].sname
                  << std::setw(spacing) << students[i].fname << std::fixed
                  << std::setprecision(1) << score << std::endl;
    }
}
