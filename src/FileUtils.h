#pragma once
#include <string>
#include <vector>
#include "Person.h"

void generateDataFile(const std::string& filename, std::size_t count);
std::vector<Person> readStudentsFromFile(const std::string& filename);
void writeStudentsToFile(const std::string& filename, const std::vector<Person>& students);
