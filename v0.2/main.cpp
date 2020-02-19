#include <bits/stdc++.h>
#include <fstream>
#include <iomanip>
#include <iostream>

const std::string RANDOM = "random";
const std::string STOP = "stop";
const std::string AVG = "vidurkis";
const std::string MEDIAN = "mediana";
const std::string FILE_NAME = "kursiokai.txt";
const int SPACING = 25;

struct Student {
   private:
    std::string fname;
    std::string sname;
    std::vector<int> hw;
    int exam;

   public:
    Student(std::string sname, std::string fname, std::vector<int> hw,
            int exam) {
        this->fname = fname;
        this->sname = sname;
        this->hw = hw;
        this->exam = exam;
    }

    std::string getFName() { return fname; }

    std::string getSName() { return sname; }

    double getAverage() {
        int sum = 0;
        for (int i = 0; i < hw.size(); i++) sum += hw[i];
        double hwAverage;
        if (hw.size() > 0) hwAverage = (double)sum / hw.size();

        return 0.4 * hwAverage + 0.6 * exam;
    }

    double getMedian() {
        std::sort(hw.begin(), hw.end());
        if (hw.size() % 2 == 0) {
            return (double)(hw[(hw.size() - 1) / 2 + 1] +
                            hw[(hw.size() - 1) / 2]) /
                   2;
        } else
            return (double)hw[(hw.size() - 1) / 2];
    }
};

std::vector<Student> getStudents();
bool compareStudentsSNames(Student s1, Student s2);
std::vector<Student> getStudentsFromFile();
int studentAmountInput();
char isHwAmountInput();
int hwAmountInput(char isHwAmount);
std::vector<int> hwInput(char isHwAmount, int hwAmount);
int hwElementInput(int iterator, char isHwAmount);
int examInput();
std::vector<Student> studentsInput(int studentsAmount);
std::string finalScoreTypeInput();
void printResults(std::vector<Student> students);

int main() {
    printResults(getStudents());

    return 0;
}

std::vector<Student> getStudents() {
    std::vector<Student> students = getStudentsFromFile();

    if (!(students.size() > 0)) {
        std::cout << "Nepavyko nuskaityti duomenų iš failo \"" + FILE_NAME +
                         "\".\nĮveskite duomenis.\n";

        int studentsAmount = studentAmountInput();
        students = studentsInput(studentsAmount);
    }

    std::sort(students.begin(), students.end(), compareStudentsSNames);

    return students;
}

bool compareStudentsSNames(Student s1, Student s2) {
    return s1.getSName() < s2.getSName();
}

std::vector<Student> getStudentsFromFile() {
    std::vector<Student> students;
    std::ifstream file;
    file.open(FILE_NAME);
    if (!file) {
        return students;
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

        return students;
    }
}

int studentAmountInput() {
    int studentsAmount;
    std::cout << "Įveskite studentų kiekį:\n";
    std::cout << ">> ";
    std::cin >> studentsAmount;
    while (std::cin.fail() ||
           (studentsAmount < 0 || studentsAmount > INT_MAX)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Klaida: studentų kiekis turi būti nurodytas "
                     "skaičiumi nuo 1 iki 10.\nĮveskite iš "
                     "naujo:\n >> ";
        std::cin >> studentsAmount;
    }
    return studentsAmount;
}

char isHwAmountInput() {
    char isHwAmount;
    std::cout << "Ar norite įvesti namų darbų kiekį? (y/n)\n";
    std::cout << ">> ";
    std::cin >> isHwAmount;
    while (isHwAmount != 'y' && isHwAmount != 'n') {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Klaida: įrašykite vieną iš šių raidžių - y (taip) "
                     "arba n (ne):\n";
        std::cout << ">> ";
        std::cin >> isHwAmount;
    }
    return isHwAmount;
}

std::vector<Student> studentsInput(int studentsAmount) {
    std::vector<Student> students;

    for (int i = 0; i < studentsAmount; i++) {
        std::string fname, sname;
        std::vector<int> hw;
        int exam;

        studentsAmount > 1 ? std::cout << i + 1 << " studento vardas:\n"
                           : std::cout << "Vardas:\n";
        std::cout << ">> ";
        std::cin >> fname;

        studentsAmount > 1 ? std::cout << i + 1 << " studento pavardė:\n"
                           : std::cout << "Pavardė:\n";
        std::cout << ">> ";
        std::cin >> sname;

        char isHwAmount = isHwAmountInput();

        int hwAmount = hwAmountInput(isHwAmount);

        hw = hwInput(isHwAmount, hwAmount);
        exam = examInput();

        students.push_back(Student(fname, sname, hw, exam));
    }
    return students;
}

int hwAmountInput(char isHwAmount) {
    int hwAmount;
    if (isHwAmount == 'y') {
        std::cout << "Namų darbų kiekis:\n";
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

std::vector<int> hwInput(char isHwAmount, int hwAmount) {
    std::vector<int> hw;

    if (isHwAmount == 'y') {
        for (int i = 0; i < hwAmount; i++) {
            hw.push_back(hwElementInput(i, isHwAmount));
        }
    } else if (isHwAmount == 'n') {
        std::string hwInput;
        int i = 0;
        while (true) {
            int elem = hwElementInput(i, isHwAmount);
            if (elem > 0) {
                hw.push_back(elem);
                i++;
            } else
                break;
        }
    }
    return hw;
}

int hwElementInput(int iterator, char isHwAmount) {
    srand(time(NULL));

    int elem;

    bool invalid = false;
    std::string hwInput;
    do {
        if (invalid) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Klaida: rezultatas turi būti nurodytas "
                         "skaičiumi nuo 1 iki 10\n";
        }
        if (isHwAmount == 'n')
            std::cout << "Jei įvedėte visus rezultatus, rašykite '" << STOP
                      << "'. ";
        std::cout << "Jei norite sugeneruoti atsitiktinį skaičių, rašykite '"
                  << RANDOM << "'.\n";
        std::cout << iterator + 1 << " namų darbo rezultatas:\n";
        std::cout << ">> ";
        std::cin >> hwInput;

        if (isHwAmount == 'n') {
            if (hwInput == STOP) {
                elem = -1;
                return elem;
            }
        }

        if (hwInput == RANDOM) {
            elem = rand() % 10 + 1;
            std::cout << "Sugeneruotas skaičius: " << elem << '\n';
            invalid = false;
        } else {
            try {
                elem = stoi(hwInput);
                invalid = elem <= 0 || elem > 10 ? true : false;
            } catch (const std::invalid_argument &e) {
                invalid = true;
            } catch (const std::out_of_range &e) {
                invalid = true;
            }
        }
    } while (elem <= 0 || elem > 10);

    return elem;
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
                         "nuo 1 iki 10\n";
        }
        std::cout << "Jei norite sugeneruoti atsitiktinį skaičių, rašykite '"
                  << RANDOM << "'.\nEgzamino rezultatas:\n";
        std::cout << ">> ";
        std::cin >> examInput;
        if (examInput == RANDOM) {
            exam = rand() % 10 + 1;
            std::cout << "Suegeneruotas skaičius: " << exam << '\n';
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
              << MEDIAN << ")\n";
    std::cout << ">> ";
    std::cin >> finalScoreType;
    while (finalScoreType != AVG && finalScoreType != MEDIAN) {
        std::cout << "Klaida: įveskite vieną iš šių žodžių - " << AVG << '/'
                  << MEDIAN << '\n';
        std::cout << ">> ";
        std::cin >> finalScoreType;
    }
    return finalScoreType;
}

void printResults(std::vector<Student> students) {
    std::string finalScoreType = finalScoreTypeInput();

    std::cout << "---------------------------------------------------------"
                 "--------\n";
    std::string type = finalScoreType == AVG ? "Vid." : "Med.";
    std::cout << std::left << std::setw(SPACING) << "Pavardė"
              << std::setw(SPACING) << "Vardas"
              << "Galutinis (" << type << ")\n";
    std::cout << "---------------------------------------------------------"
                 "--------\n";
    for (int i = 0; i < students.size(); i++) {
        double score = finalScoreType == AVG ? students[i].getAverage()
                                             : students[i].getMedian();
        std::cout << std::left << std::setw(SPACING) << students[i].getSName()
                  << std::setw(SPACING) << students[i].getFName() << std::fixed
                  << std::setprecision(1) << score << '\n';
    }
}
