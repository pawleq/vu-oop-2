#include <bits/stdc++.h>
#include <iomanip>
#include <iostream>

#define RANDOM "random"
#define STOP "stop"
#define AVG "vidurkis"
#define MEDIAN "mediana"

struct Student {
   private:
    std::string fname;
    std::string sname;
    std::vector<int> hw;
    int exam;

   public:
    Student(std::string fname, std::string sname, std::vector<int> hw,
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
        if (hw.size() % 2 == 0)
            return (double)(hw[hw.size() / 2 - 1] + hw[hw.size() / 2]) / 2;
        else
            return (double)hw[hw.size() / 2];
    }
};

int userAmountInput();
char isHwAmountInput();
int hwAmountInput(char isHwAmount);
std::vector<int> hwInput(char isHwAmount, int hwAmount);
int hwElementInput(int iterator, char isUndefined);
int examInput();
std::vector<Student> inputStudents(int users);
std::string finalScoreTypeInput();
void reallocateArray(int size, int oldArr[]);
double finalAverage(std::vector<int>, int hwAmount, int exam);
double finalMedian(std::vector<int>, int hwAmount);
void printResults(std::vector<Student> students, int users,
                  std::string finalScoreType);

int main() {
    srand(time(NULL));

    int users = userAmountInput();

    std::vector<Student> students = inputStudents(users);

    std::string finalScoreType = finalScoreTypeInput();

    printResults(students, users, finalScoreType);

    return 0;
}

std::vector<Student> inputStudents(int users) {
    std::vector<Student> students;

    for (int i = 0; i < users; i++) {
        std::string fname, sname;
        std::vector<int> hw;
        int exam;

        users > 1 ? std::cout << i + 1 << " studento vardas:" << std::endl
                  : std::cout << "Vardas:" << std::endl;
        std::cout << ">> ";
        std::cin >> fname;

        users > 1 ? std::cout << i + 1 << " studento pavardė:" << std::endl
                  : std::cout << "Pavardė:" << std::endl;
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
        std::cout
            << "Klaida: įrašykite vieną iš šių raidžių - y (taip) arba n (ne):"
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

int hwElementInput(int iterator, char isUndefined) {
    int elem;

    bool invalid = false;
    std::string hwInput;
    do {
        if (invalid) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Klaida: rezultatas turi būti nurodytas "
                         "skaičiumi nuo 1 iki 10"
                      << std::endl;
        }
        if (isUndefined)
            std::cout << "Jei įvedėte visus rezultatus, rašykite '" << STOP
                      << "'. ";
        std::cout
            << "Jei norite sugeneruoti atsitiktinį skaičių, rašykite '" RANDOM
            << "'.\n";
        std::cout << iterator + 1 << " namų darbo rezultatas:" << std::endl;
        std::cout << ">> ";
        std::cin >> hwInput;

        if (iterator >= 0) {
            if (hwInput == STOP) {
                elem = -1;
                return elem;
            }
        }

        if (hwInput == RANDOM) {
            elem = rand() % 10 + 1;
            std::cout << "Sugeneruotas skaičius: " << elem << std::endl;
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

void printResults(std::vector<Student> students, int users,
                  std::string finalScoreType) {
    int spacing = 25;
    std::cout
        << "-----------------------------------------------------------------"
        << std::endl;
    std::string type = finalScoreType == AVG ? "Vid." : "Med.";
    std::cout << std::left << std::setw(spacing) << "Pavardė"
              << std::setw(spacing) << "Vardas"
              << "Galutinis (" << type << ')' << std::endl;
    std::cout
        << "-----------------------------------------------------------------"
        << std::endl;
    for (int i = 0; i < users; i++) {
        double score = finalScoreType == AVG ? students[i].getAverage()
                                             : students[i].getMedian();
        std::cout << std::left << std::setw(spacing) << students[i].getSName()
                  << std::setw(spacing) << students[i].getFName() << std::fixed
                  << std::setprecision(1) << score << std::endl;
    }
}
