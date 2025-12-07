#pragma once
#include <chrono>

class Timer {
public:
    Timer() {
        reset();
    }
    void reset() {
        start = std::chrono::high_resolution_clock::now();
    }
    double elapsedSeconds() const {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        return diff.count();
    }
private:
    std::chrono::high_resolution_clock::time_point start;
};
