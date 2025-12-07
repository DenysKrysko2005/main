#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include "Person.h"
#include "FileUtils.h"
#include "Timer.h"

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

        for (std::size_t size : sizes) {
            std::string filename = "students_" + std::to_string(size) + ".txt";
            std::cout << std::endl;
            std::cout << "Processing file: " << filename << std::endl;

            Timer tRead;
            std::vector<Person> students = readStudentsFromFile(filename);
            double readTime = tRead.elapsedSeconds();

            Timer tCalc;
            for (auto& s : students) {
                s.calculateFinalGrade();
            }
            double calcTime = tCalc.elapsedSeconds();

            Timer tSplit;
            std::vector<Person> failed;
            std::vector<Person> passed;
            for (const auto& s : students) {
                if (s.getFinalGrade() < 5.0) {
                    failed.push_back(s);
                } else {
                    passed.push_back(s);
                }
            }
            double splitTime = tSplit.elapsedSeconds();

            Timer tSort;
            auto cmp = [](const Person& a, const Person& b) {
                if (a.getSurname() == b.getSurname()) {
                    return a.getName() < b.getName();
                }
                return a.getSurname() < b.getSurname();
            };
            std::sort(failed.begin(), failed.end(), cmp);
            std::sort(passed.begin(), passed.end(), cmp);
            double sortTime = tSort.elapsedSeconds();

            Timer tWrite;
            std::string failedFile = "students_failed_" + std::to_string(size) + ".txt";
            std::string passedFile = "students_passed_" + std::to_string(size) + ".txt";
            writeStudentsToFile(failedFile, failed);
            writeStudentsToFile(passedFile, passed);
            double writeTime = tWrite.elapsedSeconds();

            std::cout << std::fixed << std::setprecision(3);
            std::cout << "Read time:   " << readTime << " s" << std::endl;
            std::cout << "Calc time:   " << calcTime << " s" << std::endl;
            std::cout << "Split time:  " << splitTime << " s" << std::endl;
            std::cout << "Sort time:   " << sortTime << " s" << std::endl;
            std::cout << "Write time:  " << writeTime << " s" << std::endl;
        }
    } catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Unknown error" << std::endl;
        return 1;
    }
    return 0;
}
