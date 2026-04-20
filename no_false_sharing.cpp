// no_false_sharing.cpp
#include <omp.h>
#include <iostream>
#include <chrono>

struct alignas(64) PaddedInt {
    int value;
    char padding[64 - sizeof(int)];
};

int main() {
    PaddedInt a[16]; // Each element is on a separate cache line
    for (int i = 0; i < 16; ++i) a[i].value = 0;

    auto start = std::chrono::high_resolution_clock::now();

    #pragma omp parallel for num_threads(16) schedule(static,1)
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 100000000; ++j)
            a[i].value += i;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dur = end - start;

    std::cout << "Without false sharing: " << dur.count() << " seconds\n";
    return 0;
}

