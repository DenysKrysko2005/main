#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iterator>
#include <string>
#include "Person.h"
#include "FileUtils.h"
#include "Timer.h"

bool isFailed(const Person& p) {
    return p.getFinalGrade() < 5.0;
}

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
void sortStudents(Container& c) {
    std::sort(c.begin(), c.end(), personLess);
}

void sortStudents(std::list<Person>& c) {
    c.sort(personLess);
}

template<typename Container>
void strategy1(const std::string& containerName, const std::vector<std::size_t>& sizes) {
    std::cout << std::endl;
    std::cout << "Strategy 1 - container: " << containerName << std::endl;
    for (std::size_t size : sizes) {
        std::string filename = "students_" + std::to_string(size) + ".txt";
        std::cout << "File: " << filename << std::endl;

        Timer tRead;
        Container students = readStudents<Container>(filename);
        double readTime = tRead.elapsedSeconds();

        Timer tSplit;
        Container failed;
        Container passed;
        std::remove_copy_if(students.begin(), students.end(), std::back_inserter(passed), isFailed);
        std::remove_copy_if(students.begin(), students.end(), std::back_inserter(failed),
                            [](const Person& p) { return !isFailed(p); });
        double splitTime = tSplit.elapsedSeconds();

        Timer tSort;
        sortStudents(failed);
        sortStudents(passed);
        double sortTime = tSort.elapsedSeconds();

        Timer tWrite;
        std::string failedFile = "students_failed_S1_" + containerName + "_" + std::to_string(size) + ".txt";
        std::string passedFile = "students_passed_S1_" + containerName + "_" + std::to_string(size) + ".txt";
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

template<typename Container>
void strategy2(const std::string& containerName, const std::vector<std::size_t>& sizes) {
    std::cout << std::endl;
    std::cout << "Strategy 2 - container: " << containerName << std::endl;
    for (std::size_t size : sizes) {
        std::string filename = "students_" + std::to_string(size) + ".txt";
        std::cout << "File: " << filename << std::endl;

        Timer tRead;
        Container students = readStudents<Container>(filename);
        double readTime = tRead.elapsedSeconds();

        Timer tSplit;
        auto boundary = std::stable_partition(students.begin(), students.end(),
                                              [](const Person& p) { return !isFailed(p); });
        Container failed(boundary, students.end());
        students.erase(boundary, students.end());
        double splitTime = tSplit.elapsedSeconds();

        Timer tSort;
        sortStudents(failed);
        sortStudents(students);
        double sortTime = tSort.elapsedSeconds();

        Timer tWrite;
        std::string failedFile = "students_failed_S2_" + containerName + "_" + std::to_string(size) + ".txt";
        std::string passedFile = "students_passed_S2_" + containerName + "_" + std::to_string(size) + ".txt";
        writeStudents(failedFile, failed);
        writeStudents(passedFile, students);
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

        std::cout << "Generate data files? (1 - yes, 0 - no): ";
        int genChoice = 0;
        std::cin >> genChoice;
        if (!std::cin) {
            throw std::runtime_error("Invalid input");
        }
        if (genChoice == 1) {
            for (std::size_t size : sizes) {
                std::string filename = "students_" + std::to_string(size) + ".txt";
                std::cout << "Generating " << filename << " with " << size << " records..." << std::endl;
                Timer t;
                generateDataFile(filename, size);
                std::cout << "Generation time: " << t.elapsedSeconds() << " s" << std::endl;
            }
        }

        strategy1<std::vector<Person>>("vector", sizes);
        strategy1<std::list<Person>>("list", sizes);
        strategy1<std::deque<Person>>("deque", sizes);

        strategy2<std::vector<Person>>("vector", sizes);
        strategy2<std::list<Person>>("list", sizes);
        strategy2<std::deque<Person>>("deque", sizes);
    } catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Unknown error" << std::endl;
        return 1;
    }
    return 0;
}
