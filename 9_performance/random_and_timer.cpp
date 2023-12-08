#include <cstdio>
#include <cstdlib>
#include <vector>
#include <random>
#include <chrono>

class RandomGenerator {
public:
    RandomGenerator() : gen(rd()), dis(1, 100) {}
    int generate() {
        return dis(gen);
    }
private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;
};

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
int main(){
    std::vector<int> v;
    RandomGenerator rg;
    HighPrecisionClock hpc;
    for(int i = 0; i < 100000000; i++)
        v.push_back(rg.generate());
    printf("Time elapsed: %f\n", hpc.elapsed());
    return 0;
}