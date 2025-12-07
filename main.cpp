#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <random>

class Person {
    std::string name;
    std::string surname;
    std::vector<int> homeworks;
    int exam;
    double finalAvg;
    double finalMed;

public:
    Person() : exam(0), finalAvg(0.0), finalMed(0.0) {}

    Person(const std::string& n, const std::string& s, const std::vector<int>& hw, int ex)
        : name(n), surname(s), homeworks(hw), exam(ex), finalAvg(0.0), finalMed(0.0) {}

    Person(const Person& other)
        : name(other.name),
          surname(other.surname),
          homeworks(other.homeworks),
          exam(other.exam),
          finalAvg(other.finalAvg),
          finalMed(other.finalMed) {}

    Person& operator=(const Person& other) {
        if (this != &other) {
            name = other.name;
            surname = other.surname;
            homeworks = other.homeworks;
            exam = other.exam;
            finalAvg = other.finalAvg;
            finalMed = other.finalMed;
        }
        return *this;
    }

    ~Person() {}

    const std::string& getName() const {
        return name;
    }

    const std::string& getSurname() const {
        return surname;
    }

    double getFinalAvg() const {
        return finalAvg;
    }

    double getFinalMed() const {
        return finalMed;
    }

    void calculateFinalUsingAverage() {
        if (homeworks.empty()) {
            finalAvg = 0.6 * exam;
            return;
        }
        double sum = 0.0;
        for (int x : homeworks) sum += x;
        double avg = sum / homeworks.size();
        finalAvg = 0.4 * avg + 0.6 * exam;
    }

    void calculateFinalUsingMedian() {
        if (homeworks.empty()) {
            finalMed = 0.6 * exam;
            return;
        }
        std::vector<int> temp = homeworks;
        std::sort(temp.begin(), temp.end());
        double med;
        std::size_t n = temp.size();
        if (n % 2 == 1) med = temp[n / 2];
        else med = (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
        finalMed = 0.4 * med + 0.6 * exam;
    }

    void calculateFinal() {
        calculateFinalUsingAverage();
        calculateFinalUsingMedian();
    }

    friend std::istream& operator>>(std::istream& is, Person& p) {
        std::cout << "Enter name: ";
        is >> p.name;
        std::cout << "Enter surname: ";
        is >> p.surname;

        p.homeworks.clear();
        std::cout << "Enter homework grades (end with -1): ";
        while (true) {
            int grade;
            if (!(is >> grade)) {
                is.clear();
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            if (grade == -1) break;
            if (grade >= 0 && grade <= 10) p.homeworks.push_back(grade);
        }

        std::cout << "Enter exam grade: ";
        is >> p.exam;
        p.calculateFinal();
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << std::left << std::setw(12) << p.name
           << std::left << std::setw(12) << p.surname
           << std::right << std::setw(12) << std::fixed << std::setprecision(2) << p.finalAvg
           << " | "
           << std::right << std::setw(12) << std::fixed << std::setprecision(2) << p.finalMed;
        return os;
    }
};

std::vector<Person> generateRandomStudents(int count) {
    std::vector<Person> students;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> hwCountDist(3, 10);
    std::uniform_int_distribution<int> gradeDist(0, 10);

    for (int i = 0; i < count; ++i) {
        std::string name = "Name" + std::to_string(i + 1);
        std::string surname = "Surname" + std::to_string(i + 1);
        int hwCount = hwCountDist(gen);
        std::vector<int> hw;
        for (int j = 0; j < hwCount; ++j) {
            hw.push_back(gradeDist(gen));
        }
        int exam = gradeDist(gen);
        Person p(name, surname, hw, exam);
        p.calculateFinal();
        students.push_back(p);
    }
    return students;
}

std::vector<Person> readFromFile(const std::string& filename) {
    std::vector<Person> students;
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return students;
    }

    std::string line;
    if (!std::getline(in, line)) return students;

    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string name, surname;
        iss >> name >> surname;
        std::vector<int> grades;
        int value;
        while (iss >> value) grades.push_back(value);
        if (grades.empty()) continue;
        int exam = grades.back();
        grades.pop_back();
        Person p(name, surname, grades, exam);
        p.calculateFinal();
        students.push_back(p);
    }

    return students;
}

void printHeader() {
    std::cout << std::left << std::setw(12) << "Name"
              << std::left << std::setw(12) << "Surname"
              << std::right << std::setw(16) << "Final (Avg.)"
              << " | "
              << std::right << std::setw(12) << "Final (Med.)"
              << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;
}

int main() {
    std::vector<Person> students;

    std::cout << "Choose mode:" << std::endl;
    std::cout << "1 - Manual input" << std::endl;
    std::cout << "2 - Randomly generated students" << std::endl;
    std::cout << "3 - Read from Students.txt" << std::endl;
    int mode;
    std::cin >> mode;

    if (mode == 1) {
        int n;
        std::cout << "Enter number of students: ";
        std::cin >> n;
        for (int i = 0; i < n; ++i) {
            Person p;
            std::cin >> p;
            students.push_back(p);
        }
    } else if (mode == 2) {
        int n;
        std::cout << "Enter number of random students: ";
        std::cin >> n;
        students = generateRandomStudents(n);
    } else if (mode == 3) {
        students = readFromFile("Students.txt");
    } else {
        std::cout << "Wrong mode" << std::endl;
        return 0;
    }

    std::sort(students.begin(), students.end(),
              [](const Person& a, const Person& b) {
                  if (a.getSurname() == b.getSurname()) return a.getName() < b.getName();
                  return a.getSurname() < b.getSurname();
              });

    printHeader();
    for (const auto& s : students) {
        std::cout << s << std::endl;
    }

    return 0;
}
