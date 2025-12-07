# Student Grade Calculator

This project implements a student grade processing system with multiple versions (releases), progressively improving performance, structure, and container usage.

The application reads student data from files, calculates final grades, splits students into groups (“failed” and “passed”), sorts them, and writes the results back to files.  
Later versions explore memory efficiency, algorithmic optimization, and container performance (vector, list, deque).

---

# 📌 Releases Overview

## **v0.1 — Basic Student Calculator**
- Simple console program.
- Reads static input.
- Calculates final grade using homework and exam.
- Outputs results to console.
- No containers, no file operations, no separation into passed/failed.

---

## **v0.2 — Containers, File Handling, Timing, Exceptions**
Major improvements:
- Introduced `Person` class (name, surname, homework, exam, final grade).
- Added multiple `.h` and `.cpp` files (modular structure).
- Added file generation:
  - `students_1000.txt`
  - `students_10000.txt`
  - `students_100000.txt`
  - `students_1000000.txt`
  - `students_10000000.txt`
- Introduced separation:
  - `failed` (<5.0)
  - `passed` (>=5.0)
- Measured performance:
  - file reading
  - sorting
  - splitting
  - writing
- Implemented exception handling.
- Cleaned GitHub repository (no large data files stored).

This version served as a baseline for later optimization.

---

## **v0.25 — Performance Analysis with List and Deque**
Same functionality as v0.2, but implemented using different STL containers:

- `std::vector<Person>`
- `std::list<Person>`
- `std::deque<Person>`

Performance measured for each container:
- Reading
- Splitting
- Sorting
- Writing

Results allowed comparing:
- Sequential vs. linked structure behavior
- Sorting performance differences
- Memory access patterns

All large generated files (.txt, .exe) excluded from repository using `.gitignore`.

---

## **v1.0 — Optimized Algorithms and Strategies**
This final version introduces:
### ✔ Two splitting strategies

### **Strategy 1 (Copy)**
- Base container remains unchanged.
- Students are copied into:
  - `failed`
  - `passed`
- Uses additional memory.
- Includes:
  - `remove_copy_if`
  - `copy`
- Performance measured for all container types.

### **Strategy 2 (Move + Erase)**
- Only one new container is created (`failed`).
- Passed students remain in the base container.
- Students are removed using:
  - `stable_partition`
  - `erase`
- More memory-effective.
- Expensive for linked containers with frequent erase.

### ✔ Optimized Algorithms Used
- `std::find`
- `std::find_if`
- `std::search`
- `std::copy`
- `std::remove`
- `std::remove_if`
- `std::remove_copy`
- `std::remove_copy_if`
- `std::transform`
- `std::partition`
- `std::stable_partition`

### ✔ Build system added
- **Makefile** (Linux / macOS / MinGW)
- **CMakeLists.txt** (cross-platform)

### ✔ Performance comparison
Results (example summary):
- `vector` fastest for Strategy 2  
- `list` slowest for sorting  
- `deque` middle performance  
- Strategy 2 consistently faster due to fewer copies  
- Strategy 1 uses more memory  

---

# 🚀 How to Build and Run the Application

## **1. Build using Makefile**
Works on Linux, macOS, MinGW:

```bash
make
./students
