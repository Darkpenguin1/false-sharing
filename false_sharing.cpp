// false_sharing.cpp
#include <omp.h>
#include <iostream>
#include <chrono>

int main() {
    int a[16] = {0}; // All 16 ints (64 bytes) in the same cache line

    auto start = std::chrono::high_resolution_clock::now();

    #pragma omp parallel for num_threads(16) schedule(static,1)
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 100000000; ++j)
            a[i] += i;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dur = end - start;

    std::cout << "With false sharing: " << dur.count() << " seconds\n";
    return 0;
}

