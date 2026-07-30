#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include "sorting_algorithms.hpp"


std::vector<int> generateRandomVector(int size, int minVal = 0, int maxVal = 100000) {
    std::vector<int> vec(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(minVal, maxVal);
    
    for (int i = 0; i < size; i++) {
        vec[i] = dist(gen);
    }
    return vec;
}


std::vector<int> generateNearlySortedVector(int size) {
    std::vector<int> vec(size);
    for (int i = 0; i < size; i++) {
        vec[i] = i;
    }
    
    if (size >= 2) {
        std::swap(vec[size - 1], vec[size - 2]);
    }
    return vec;
}


std::vector<int> generatePostalCodes(int size) {
    return generateRandomVector(size, 0, 99999);
}


std::vector<int> copyVector(const std::vector<int>& src) {
    return src;
}


void experiment1_MicroScale() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "PHASE 1: Micro-Scale (Active Shopping Carts)\n";
    std::cout << std::string(60, '=') << "\n";
    
    const int N = 50;
    const int REPETITIONS = 100000;  
    
    std::cout << "\n[1] Random Data (N=" << N << ", repeated " << REPETITIONS << "x):\n";
    
  
    std::vector<int> randomData = generateRandomVector(N, 0, 100);
    std::vector<int> nearlySortedData = generateNearlySortedVector(N);
    
  
    long long totalInsertionRandom = 0;
    for (int r = 0; r < REPETITIONS; r++) {
        std::vector<int> data = copyVector(randomData);
        auto start = std::chrono::high_resolution_clock::now();
        SortingAlgorithms::insertionSort(data);
        auto end = std::chrono::high_resolution_clock::now();
        totalInsertionRandom += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }
    
  
    long long totalSelectionRandom = 0;
    for (int r = 0; r < REPETITIONS; r++) {
        std::vector<int> data = copyVector(randomData);
        auto start = std::chrono::high_resolution_clock::now();
        SortingAlgorithms::selectionSort(data);
        auto end = std::chrono::high_resolution_clock::now();
        totalSelectionRandom += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }
    
  
    long long totalInsertionNearly = 0;
    for (int r = 0; r < REPETITIONS; r++) {
        std::vector<int> data = copyVector(nearlySortedData);
        auto start = std::chrono::high_resolution_clock::now();
        SortingAlgorithms::insertionSort(data);
        auto end = std::chrono::high_resolution_clock::now();
        totalInsertionNearly += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }
    
   
    long long totalSelectionNearly = 0;
    for (int r = 0; r < REPETITIONS; r++) {
        std::vector<int> data = copyVector(nearlySortedData);
        auto start = std::chrono::high_resolution_clock::now();
        SortingAlgorithms::selectionSort(data);
        auto end = std::chrono::high_resolution_clock::now();
        totalSelectionNearly += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }
 
    long long avgInsertionRandom = totalInsertionRandom / REPETITIONS;
    long long avgSelectionRandom = totalSelectionRandom / REPETITIONS;
    long long avgInsertionNearly = totalInsertionNearly / REPETITIONS;
    long long avgSelectionNearly = totalSelectionNearly / REPETITIONS;
    
    std::cout << "  Insertion Sort (Random): " << avgInsertionRandom << " μs\n";
    std::cout << "  Selection Sort (Random): " << avgSelectionRandom << " μs\n";
    std::cout << "  Insertion Sort (Nearly Sorted): " << avgInsertionNearly << " μs\n";
    std::cout << "  Selection Sort (Nearly Sorted): " << avgSelectionNearly << " μs\n";
    std::cout << "  Speedup (Insertion on Nearly Sorted vs Random): " 
              << (double)avgInsertionRandom / avgInsertionNearly << "x\n";
   
    std::ofstream file("phase1_results.csv");
    file << "Phase,Algorithm,DatasetSize,DataType,TimeMicroseconds\n";
    file << "Phase 1,Insertion Sort,50,Random repeated " << REPETITIONS << "x," << avgInsertionRandom << "\n";
    file << "Phase 1,Selection Sort,50,Random repeated " << REPETITIONS << "x," << avgSelectionRandom << "\n";
    file << "Phase 1,Insertion Sort,50,Nearly Sorted repeated " << REPETITIONS << "x," << avgInsertionNearly << "\n";
    file << "Phase 1,Selection Sort,50,Nearly Sorted repeated " << REPETITIONS << "x," << avgSelectionNearly << "\n";
    file.close();
}



void experiment2_VIPExtraction() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "PHASE 2: VIP Extraction (Flash Sale)\n";
    std::cout << std::string(60, '=') << "\n";
    
    const int N = 100000;
    const int K = 500;
    
    std::vector<int> data = generateRandomVector(N, 0, 1000000);
    
    std::cout << "\nExtracting Top " << K << " from " << N << " elements...\n";
    
    
    std::vector<int> data1 = copyVector(data);
    auto start = std::chrono::high_resolution_clock::now();
    SortingAlgorithms::heapSort(data1);
    auto end = std::chrono::high_resolution_clock::now();
    auto fullSortTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    
    std::vector<int> data2 = copyVector(data);
    start = std::chrono::high_resolution_clock::now();
    std::vector<int> topK = SortingAlgorithms::extractTopK(data2, K);
    end = std::chrono::high_resolution_clock::now();
    auto heapExtractTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "\n[1] Full Heap Sort + Take Top " << K << ": " << fullSortTime.count() << " μs\n";
    std::cout << "[2] Build Heap + Extract Max " << K << " times: " << heapExtractTime.count() << " μs\n";
    std::cout << "\n  ⚡ Speedup (Method 2 vs Method 1): " 
              << (double)fullSortTime.count() / heapExtractTime.count() << "x\n";
    

    std::ofstream file("phase2_results.csv");
    file << "Phase,Algorithm,DatasetSize,DataType,TimeMicroseconds\n";
    file << "Phase 2,Heap Sort Full Array," << N << ",Top " << K << " Extraction," << fullSortTime.count() << "\n";
    file << "Phase 2,Build Heap + " << K << " Extract Max," << N << ",Top " << K << " Extraction," << heapExtractTime.count() << "\n";
    file.close();
}



void experiment3_MacroScale() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "PHASE 3: Macro-Scale Routing (End-of-Day Logistics)\n";
    std::cout << std::string(60, '=') << "\n";
    
   
    std::vector<int> sizes = {50000, 100000, 250000, 500000, 1000000};
    
    std::cout << "\n🔍 Finding the exact point where Radix Sort overtakes Heap Sort...\n";
    std::cout << "\nComparing Heap Sort vs Radix Sort on 5-digit postal codes:\n";
    std::cout << std::string(90, '-') << "\n";
    std::cout << std::setw(12) << "Size" 
              << std::setw(20) << "Heap Sort (μs)" 
              << std::setw(20) << "Radix Sort (μs)"
              << std::setw(15) << "Speedup"
              << std::setw(25) << "Winner" << "\n";
    std::cout << std::string(90, '-') << "\n";
    
    std::ofstream file("phase3_results.csv");
    file << "Phase,Algorithm,DatasetSize,DataType,TimeMicroseconds\n";
    
    int threshold = -1;
    
    for (int size : sizes) {
        std::vector<int> data = generatePostalCodes(size);
        
      
        std::vector<int> data1 = copyVector(data);
        auto start = std::chrono::high_resolution_clock::now();
        SortingAlgorithms::heapSort(data1);
        auto end = std::chrono::high_resolution_clock::now();
        auto heapTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
     
        std::vector<int> data2 = copyVector(data);
        start = std::chrono::high_resolution_clock::now();
        SortingAlgorithms::radixSort(data2);
        end = std::chrono::high_resolution_clock::now();
        auto radixTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        double speedup = (double)heapTime.count() / radixTime.count();
        
       
        std::string winner;
        if (heapTime.count() < radixTime.count()) {
            winner = "Heap Sort Wins";
        } else if (radixTime.count() < heapTime.count()) {
            winner = "Radix Sort Wins";
        } else {
            winner = "Tie";
        }
        
        std::cout << std::setw(12) << size 
                  << std::setw(20) << heapTime.count()
                  << std::setw(20) << radixTime.count()
                  << std::setw(14) << std::fixed << std::setprecision(2) << speedup << "x"
                  << std::setw(25) << winner << "\n";
        
        
        file << "Phase 3 Overtake Check,Heap Sort," << size << ",5-Digit Postal Codes," << heapTime.count() << "\n";
        file << "Phase 3 Overtake Check,Radix Sort," << size << ",5-Digit Postal Codes," << radixTime.count() << "\n";
        
        
        if (threshold == -1 && radixTime.count() < heapTime.count()) {
            threshold = size;
        }
    }
    
    file.close();
    
    
    std::cout << std::string(90, '-') << "\n\n";
    std::cout << "📊 OVERTAKE ANALYSIS RESULTS:\n";
    std::cout << std::string(50, '-') << "\n";
    
    if (threshold != -1) {
        std::cout << "✅ Radix Sort overtakes Heap Sort at N = " << threshold << "\n";
        std::cout << "   (This is the point where Radix Sort becomes faster)\n";
    } else {
        std::cout << "⚠️ Radix Sort did not overtake Heap Sort in the tested range.\n";
    }
}



void bonus_MemoryBandwidth() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "BONUS: 64-bit Memory Bandwidth Bottleneck\n";
    std::cout << std::string(60, '=') << "\n";
    
    const int N = 5000000;
    
    std::cout << "\nTesting Radix Sort on " << N << " elements...\n";
    std::cout << std::string(60, '-') << "\n";
    
  
    std::vector<uint32_t> data32(N);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dist(0, 99999);
    
    for (int i = 0; i < N; i++) {
        data32[i] = dist(gen);
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> data32int(data32.begin(), data32.end());
    SortingAlgorithms::radixSort(data32int);
    auto end = std::chrono::high_resolution_clock::now();
    auto time32 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Test A (uint32_t): " << time32.count() << " μs\n";
    std::cout << "  Memory usage: " << (N * sizeof(uint32_t)) / (1024 * 1024) << " MB\n";
    
   
    std::vector<uint64_t> data64(N);
    std::mt19937_64 gen64(rd());
    std::uniform_int_distribution<uint64_t> dist64(0, 99999);
    
    for (int i = 0; i < N; i++) {
        data64[i] = dist64(gen64);
    }
    
    start = std::chrono::high_resolution_clock::now();
   
    for (int byte = 0; byte < 8; byte++) {
        std::vector<uint64_t> output(N);
        std::vector<int> count(256, 0);
        
        for (int i = 0; i < N; i++) {
            int digit = (data64[i] >> (byte * 8)) & 0xFF;
            count[digit]++;
        }
        
        for (int i = 1; i < 256; i++) {
            count[i] += count[i - 1];
        }
        
        for (int i = N - 1; i >= 0; i--) {
            int digit = (data64[i] >> (byte * 8)) & 0xFF;
            output[count[digit] - 1] = data64[i];
            count[digit]--;
        }
        
        for (int i = 0; i < N; i++) {
            data64[i] = output[i];
        }
    }
    end = std::chrono::high_resolution_clock::now();
    auto time64 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Test B (uint64_t): " << time64.count() << " μs\n";
    std::cout << "  Memory usage: " << (N * sizeof(uint64_t)) / (1024 * 1024) << " MB\n";
    
    std::cout << std::string(60, '-') << "\n";
    std::cout << "Slowdown (64-bit vs 32-bit): " << (double)time64.count() / time32.count() << "x\n";
    std::cout << "Memory difference: 2x (64-bit uses twice the RAM)\n";
    
    
    std::ofstream file("bonus_results.csv");
    file << "Phase,Algorithm,DatasetSize,DataType,TimeMicroseconds\n";
    file << "Bonus,Radix Sort uint32_t," << N << ",5-Digit Postal Codes," << time32.count() << "\n";
    file << "Bonus,Radix Sort uint64_t," << N << ",5-Digit Postal Codes," << time64.count() << "\n";
    file.close();
}



int main() {
    std::cout << "\n";
    std::cout << "============================================================\n";
    std::cout << "   E-COMMERCE SORTING PIPELINE - PERFORMANCE ANALYSIS\n";
    std::cout << "============================================================\n";
    
    // Run all experiments
    experiment1_MicroScale();
    experiment2_VIPExtraction();
    experiment3_MacroScale();
    bonus_MemoryBandwidth();
    
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "✅ All experiments completed! Results exported to CSV files.\n";
    std::cout << "📁 Files created:\n";
    std::cout << "   - phase1_results.csv\n";
    std::cout << "   - phase2_results.csv\n";
    std::cout << "   - phase3_results.csv\n";
    std::cout << "   - bonus_results.csv\n";
    std::cout << "📊 Run 'python analysis.py' to generate visualizations.\n";
    std::cout << std::string(60, '=') << "\n\n";
    
    return 0;
}