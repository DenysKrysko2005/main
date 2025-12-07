#include "FileUtils.h"
#include <fstream>
#include <random>
#include <stdexcept>
#include <sstream>

void generateDataFile(const std::string& filename, std::size_t count) {
    std::ofstream out(filename);
    if (!out) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }
    out << "Name Surname HW1 HW2 HW3 HW4 HW5 Exam\n";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> gradeDist(0, 10);
    for (std::size_t i = 0; i < count; ++i) {
        out << "Name" << (i + 1) << ' '
            << "Surname" << (i + 1);
        for (int j = 0; j < 5; ++j) {
            out << ' ' << gradeDist(gen);
        }
        out << ' ' << gradeDist(gen) << '\n';
    }
}

std::vector<Person> readStudentsFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        throw std::runtime_error("Cannot open file for reading: " + filename);
    }
    std::vector<Person> students;
    std::string line;
    if (!std::getline(in, line)) {
        return students;
    }
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string name;
        std::string surname;
        iss >> name >> surname;
        if (!iss) {
            throw std::runtime_error("Invalid data line in file: " + filename);
        }
        std::vector<int> hw;
        int value;
        for (int i = 0; i < 5; ++i) {
            if (!(iss >> value)) {
                throw std::runtime_error("Not enough homework grades in file: " + filename);
            }
            hw.push_back(value);
        }
        int exam;
        if (!(iss >> exam)) {
            throw std::runtime_error("Missing exam grade in file: " + filename);
        }
        Person p(name, surname, hw, exam);
        p.calculateFinalGrade();
        students.push_back(p);
    }
    return students;
}

void writeStudentsToFile(const std::string& filename, const std::vector<Person>& students) {
    std::ofstream out(filename);
    if (!out) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }
    out << "Name Surname Final\n";
    for (const auto& s : students) {
        out << s.getName() << ' ' << s.getSurname() << ' ' << s.getFinalGrade() << '\n';
    }
}
