#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <thread>
#include <omp.h>

class FractalMemoryEngine {
private:
    const float k = 43.0f;
    const float PI = 3.14159265359f;
    const float phaseShift = -1.57079632679f;

public:
    float getProceduralValue(long i) {
        float theta = (float)i * (2.0f * PI / k);
        return (static_cast<float>(i) / k) * cosf(theta + phaseShift);
    }
};

int main() {
    FractalMemoryEngine fEngine;
    long data_per_thread = 5000000; 

    int available_threads = omp_get_max_threads();
    
    std::cout << "Pezles: " << available_threads << " szal." << std::endl;

    std::vector<float> integrity_check(available_threads, 0.0f);

    #pragma omp parallel num_threads(available_threads)
    {
        int thread_id = omp_get_thread_num();
        
        std::this_thread::sleep_for(std::chrono::seconds(thread_id * 1));
        
        #pragma omp critical
        {
            std::cout << "Szal #" << thread_id << " fuggveny-atvitel..." << std::endl;
        }

        volatile float local_accumulator = 0.0f;
        for (long i = 0; i < data_per_thread; ++i) {
            local_accumulator = local_accumulator + fEngine.getProceduralValue(i);
        }
        integrity_check[thread_id] = const_cast<float&>(local_accumulator);

        #pragma omp critical
        {
            std::cout << "Szal #" << thread_id << " kesz." << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    std::cout << "Jo munkat kivanunk!" << std::endl;

    return 0;
}
// FORDÍTÁS: C:\mingw64\bin\g++.exe -O3 -fopenmp -static -static-libgcc -static-libstdc++ C:\Users\YOUCODE.cpp -o C:\Users\YOUCODE.exe
