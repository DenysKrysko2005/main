#pragma once
#include <string>
#include <vector>
#include <iostream>

class Person {
public:
    Person();
    Person(const std::string& name, const std::string& surname, const std::vector<int>& hw, int exam);
    Person(const Person& other);
    Person& operator=(const Person& other);
    ~Person();

    const std::string& getName() const;
    const std::string& getSurname() const;
    double getFinalGrade() const;

    void calculateFinalGrade();
    static double computeFinalGrade(const std::vector<int>& hw, int exam);

    friend std::ostream& operator<<(std::ostream& os, const Person& p);

private:
    std::string name;
    std::string surname;
    std::vector<int> homeworks;
    int exam;
    double finalGrade;
};
