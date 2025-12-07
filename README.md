# Student Grade Processing System

This project implements a multi-stage student grade processing system developed across several releases.  
Each release improves structure, performance, and algorithmic efficiency while introducing new features and container types.

The program reads student data, calculates final grades, splits students based on performance, sorts results, and writes them to output files.  
It also includes performance comparisons between different STL containers and data-splitting strategies.

---

# 📌 Project Overview

The system evolves through multiple versions:

### ✔ v0.1 — Basic calculator
Simple console program:
- Reads student input
- Calculates final grade (average/median)
- Prints formatted table

### ✔ v0.2 — File processing & exceptions
Adds:
- `Person` class
- Reading from files
- Sorting and splitting students
- Generating large datasets (1k–10M)
- Execution time measurement
- Exception handling

### ✔ v0.25 — Container performance comparison
Implements:
- `vector`
- `list`
- `deque`
- Timing of read/split/sort/write operations

### ✔ v1.0 — Final optimized version
Adds:
- Two data-splitting strategies:
  - Strategy 1 (copy)
  - Strategy 2 (move + erase)
- Performance optimization using `<algorithm>`:
  `copy`, `remove_if`, `stable_partition`, `find`, etc.
- Makefile and CMake build support

Each version has its own branch and README.

---

# 🧱 Project Structure

