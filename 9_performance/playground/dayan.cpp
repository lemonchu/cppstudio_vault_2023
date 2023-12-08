#include <iostream>
#include <vector>
#include <random>
#include <chrono>

#define SAMPLE 20000000
std::random_device rd;
std::mt19937 gen(rd());
std::normal_distribution<double> distribution(0.5, 0.1);

class HighPrecisionClock {
public:
    HighPrecisionClock() : start_time(std::chrono::high_resolution_clock::now()) {}

    void reset() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    double elapsed() {
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end_time - start_time;
        return elapsed.count();
    }

private:
    std::chrono::high_resolution_clock::time_point start_time;
};

int dayan() {
    int total = 49;
    for (int i = 0; i < 3; i++) {
        int a = (double) total * distribution(gen);
        while (a <= 0 || a >= total)
            a = (double) total * distribution(gen);
        int b = total - a;
        b--;
        a -= ((a & 3) == 0) ? 4 : a & 3;
        b -= ((b & 3) == 0) ? 4 : b & 3;
        total = a + b;
    }
    return total >> 2;
}

int main() {
    HighPrecisionClock hpc;
    int a[10] = {0};
    for (int i = 1; i < SAMPLE; i++) {
        a[dayan()]++;
    }
    for (int i = 5; i < 10; i++) {
        printf("%d : %d %0.4lf\n", i, a[i], 100 * a[i] / (double) SAMPLE);
    }
    printf("Time elapsed: %f\n", hpc.elapsed());
    return 0;
}