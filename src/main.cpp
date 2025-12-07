#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Person.h"
#include "Timer.h"

bool personLess(const Person& a, const Person& b) {
    if (a.getSurname() == b.getSurname()) {
        return a.getName() < b.getName();
    }
    return a.getSurname() < b.getSurname();
}

template<typename Container>
Container readStudents(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        throw std::runtime_error("Cannot open file for reading: " + filename);
    }
    Container result;
    std::string line;
    if (!std::getline(in, line)) {
        return result;
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
        result.emplace_back(name, surname, hw, exam);
        result.back().calculateFinalGrade();
    }
    return result;
}

template<typename Container>
void writeStudents(const std::string& filename, const Container& students) {
    std::ofstream out(filename);
    if (!out) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }
    out << "Name Surname Final\n";
    for (const auto& s : students) {
        out << s.getName() << ' ' << s.getSurname() << ' ' << s.getFinalGrade() << '\n';
    }
}

template<typename Container>
void splitStudents(const Container& all, Container& failed, Container& passed) {
    for (const auto& s : all) {
        if (s.getFinalGrade() < 5.0) {
            failed.push_back(s);
        } else {
            passed.push_back(s);
        }
    }
}

template<typename Container>
void sortStudents(Container& c) {
    std::sort(c.begin(), c.end(), personLess);
}

void sortStudents(std::list<Person>& c) {
    c.sort(personLess);
}

template<typename Container>
void processContainer(const std::string& containerName, const std::vector<std::size_t>& sizes) {
    std::cout << std::endl;
    std::cout << "Container: " << containerName << std::endl;
    for (std::size_t size : sizes) {
        std::string filename = "students_" + std::to_string(size) + ".txt";
        std::cout << "File: " << filename << std::endl;

        Timer tRead;
        Container students = readStudents<Container>(filename);
        double readTime = tRead.elapsedSeconds();

        Timer tSplit;
        Container failed;
        Container passed;
        splitStudents(students, failed, passed);
        double splitTime = tSplit.elapsedSeconds();

        Timer tSort;
        sortStudents(failed);
        sortStudents(passed);
        double sortTime = tSort.elapsedSeconds();

        Timer tWrite;
        std::string failedFile = "students_failed_" + containerName + "_" + std::to_string(size) + ".txt";
        std::string passedFile = "students_passed_" + containerName + "_" + std::to_string(size) + ".txt";
        writeStudents(failedFile, failed);
        writeStudents(passedFile, passed);
        double writeTime = tWrite.elapsedSeconds();

        std::cout << std::fixed << std::setprecision(3);
        std::cout << "Read:  " << readTime << " s" << std::endl;
        std::cout << "Split: " << splitTime << " s" << std::endl;
        std::cout << "Sort:  " << sortTime << " s" << std::endl;
        std::cout << "Write: " << writeTime << " s" << std::endl;
    }
}

int main() {
    try {
        std::vector<std::size_t> sizes = {1000, 10000, 100000, 1000000, 10000000};
        processContainer<std::list<Person>>("list", sizes);
        processContainer<std::deque<Person>>("deque", sizes);
    } catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Unknown error" << std::endl;
        return 1;
    }
    return 0;
}
