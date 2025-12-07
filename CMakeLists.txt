cmake_minimum_required(VERSION 3.10)
project(StudentGrades)

set(CMAKE_CXX_STANDARD 17)

add_executable(students
    src/main.cpp
    src/Person.cpp
    src/FileUtils.cpp
)
