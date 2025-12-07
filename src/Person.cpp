#include "Person.h"
#include <numeric>

Person::Person() : exam(0), finalGrade(0.0) {}

Person::Person(const std::string& n, const std::string& s, const std::vector<int>& hw, int ex)
    : name(n), surname(s), homeworks(hw), exam(ex), finalGrade(0.0) {}

Person::Person(const Person& other)
    : name(other.name),
      surname(other.surname),
      homeworks(other.homeworks),
      exam(other.exam),
      finalGrade(other.finalGrade) {}

Person& Person::operator=(const Person& other) {
    if (this != &other) {
        name = other.name;
        surname = other.surname;
        homeworks = other.homeworks;
        exam = other.exam;
        finalGrade = other.finalGrade;
    }
    return *this;
}

Person::~Person() {}

const std::string& Person::getName() const {
    return name;
}

const std::string& Person::getSurname() const {
    return surname;
}

double Person::getFinalGrade() const {
    return finalGrade;
}

double Person::computeFinalGrade(const std::vector<int>& hw, int exam) {
    if (hw.empty()) {
        return 0.6 * exam;
    }
    double sum = 0.0;
    for (int h : hw) sum += h;
    double avg = sum / hw.size();
    return 0.4 * avg + 0.6 * exam;
}

void Person::calculateFinalGrade() {
    finalGrade = computeFinalGrade(homeworks, exam);
}

std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << p.getName() << ' ' << p.getSurname() << ' ' << p.getFinalGrade();
    return os;
}
