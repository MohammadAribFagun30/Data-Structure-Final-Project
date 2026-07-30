#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <cstdint>
#include "sorting_algorithms.hpp"


class RadixSort64 {
private:
    static void countingSortByByte(std::vector<uint64_t>& arr, int byte) {
        int n = arr.size();
        std::vector<uint64_t> output(n);
        std::vector<int> count(256, 0);
        
        // Count occurrences of each byte value
        for (int i = 0; i < n; i++) {
            int digit = (arr[i] >> (byte * 8)) & 0xFF;
            count[digit]++;
        }
        
       
        for (int i = 1; i < 256; i++) {
            count[i] += count[i - 1];
        }
        
        
        for (int i = n - 1; i >= 0; i--) {
            int digit = (arr[i] >> (byte * 8)) & 0xFF;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }
        
      
        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }
    }
    
public:
    static void radixSort64(std::vector<uint64_t>& arr) {
        // Sort by each byte (8 bytes for 64-bit)
        for (int byte = 0; byte < 8; byte++) {
            countingSortByByte(arr, byte);
        }
    }
};


std::vector<uint32_t> generateRandom32(int size) {
    std::vector<uint32_t> vec(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dist(0, 99999);
    
    for (int i = 0; i < size; i++) {
        vec[i] = dist(gen);
    }
    return vec;
}


std::vector<uint64_t> generateRandom64(int size) {
    std::vector<uint64_t> vec(size);
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dist(0, 99999);
    
    for (int i = 0; i < size; i++) {
        vec[i] = dist(gen);
    }
    return vec;
}

int main() {
    std::cout << "\n";
    std::cout << "============================================================\n";
    std::cout << "   BONUS: 64-bit Memory Bandwidth Bottleneck\n";
    std::cout << "============================================================\n";
    
    const int N = 5000000;
    
    std::cout << "\nTesting Radix Sort on " << N << " elements...\n";
    std::cout << std::string(60, '-') << "\n";
    
  
    std::vector<uint32_t> data32 = generateRandom32(N);
    
    auto start = std::chrono::high_resolution_clock::now();
    
    std::vector<int> data32int(data32.begin(), data32.end());
    SortingAlgorithms::radixSort(data32int);
    auto end = std::chrono::high_resolution_clock::now();
    auto time32 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Test A (32-bit integers): " << time32.count() << " ms\n";
    std::cout << "  Memory usage: " << (N * sizeof(uint32_t)) / (1024 * 1024) << " MB\n";
    
    
    std::vector<uint64_t> data64 = generateRandom64(N);
    
    start = std::chrono::high_resolution_clock::now();
    RadixSort64::radixSort64(data64);
    end = std::chrono::high_resolution_clock::now();
    auto time64 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Test B (64-bit integers): " << time64.count() << " ms\n";
    std::cout << "  Memory usage: " << (N * sizeof(uint64_t)) / (1024 * 1024) << " MB\n";
    
    std::cout << std::string(60, '-') << "\n";
    std::cout << "Slowdown (64-bit vs 32-bit): " << (double)time64.count() / time32.count() << "x\n";
    std::cout << "Memory difference: 2x (64-bit uses twice the RAM)\n";
    std::cout << "\nConclusion: Even with the same algorithmic complexity (O(N)),\n";
    std::cout << "64-bit sorting is slower due to memory bandwidth limitations.\n";
    std::cout << "CPU cache misses increase when data doesn't fit in cache.\n";
    
  
    std::ofstream file("bonus_results.csv");
    file << "Type,Size,Time(ms),Memory(MB)\n";
    file << "32-bit," << N << "," << time32.count() << "," << (N * sizeof(uint32_t)) / (1024 * 1024) << "\n";
    file << "64-bit," << N << "," << time64.count() << "," << (N * sizeof(uint64_t)) / (1024 * 1024) << "\n";
    file.close();
    
    std::cout << "\nResults exported to bonus_results.csv\n";
    
    return 0;
}