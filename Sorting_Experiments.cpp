#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include "sorting_algorithms.hpp"

// ============================================================
// Helper Functions
// ============================================================

// Generate random vector
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

// Generate nearly sorted vector (only last 2 elements out of place)
std::vector<int> generateNearlySortedVector(int size) {
    std::vector<int> vec(size);
    for (int i = 0; i < size; i++) {
        vec[i] = i;
    }
    // Swap last two elements to make it nearly sorted
    if (size >= 2) {
        std::swap(vec[size - 1], vec[size - 2]);
    }
    return vec;
}

// Generate 5-digit postal codes (00000-99999)
std::vector<int> generatePostalCodes(int size) {
    return generateRandomVector(size, 0, 99999);
}

// Copy vector
std::vector<int> copyVector(const std::vector<int>& src) {
    return src;
}

// ============================================================
// Experiment 1: Micro-Scale - Active Shopping Carts
// ============================================================

void experiment1_MicroScale() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "PHASE 1: Micro-Scale (Active Shopping Carts)\n";
    std::cout << std::string(60, '=') << "\n";
    
    const int N = 50;
    
    // Generate datasets
    std::vector<int> randomData = generateRandomVector(N, 0, 100);
    std::vector<int> nearlySortedData = generateNearlySortedVector(N);
    
    std::cout << "\n[1] Random Data (N=" << N << "):\n";
    
    // Insertion Sort on Random Data
    std::vector<int> data1 = copyVector(randomData);
    auto start = std::chrono::high_resolution_clock::now();
    SortingAlgorithms::insertionSort(data1);
    auto end = std::chrono::high_resolution_clock::now();
    auto insertionRandom = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Selection Sort on Random Data
    std::vector<int> data2 = copyVector(randomData);
    start = std::chrono::high_resolution_clock::now();
    SortingAlgorithms::selectionSort(data2);
    end = std::chrono::high_resolution_clock::now();
    auto selectionRandom = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "  Insertion Sort: " << insertionRandom.count() << " μs\n";
    std::cout << "  Selection Sort: " << selectionRandom.count() << " μs\n";
    
    std::cout << "\n[2] Nearly Sorted Data (N=" << N << "):\n";
    
    // Insertion Sort on Nearly Sorted Data
    data1 = copyVector(nearlySortedData);
    start = std::chrono::high_resolution_clock::now();
    SortingAlgorithms::insertionSort(data1);
    end = std::chrono::high_resolution_clock::now();
    auto insertionNearly = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Selection Sort on Nearly Sorted Data
    data2 = copyVector(nearlySortedData);
    start = std::chrono::high_resolution_clock::now();
    SortingAlgorithms::selectionSort(data2);
    end = std::chrono::high_resolution_clock::now();
    auto selectionNearly = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "  Insertion Sort: " << insertionNearly.count() << " μs\n";
    std::cout << "  Selection Sort: " << selectionNearly.count() << " μs\n";
    std::cout << "\n  Speedup (Insertion on Nearly Sorted vs Random): " 
              << (double)insertionRandom.count() / insertionNearly.count() << "x\n";
    
    // Export to CSV
    std::ofstream file("phase1_results.csv");
    file << "Dataset,Algorithm,Time(μs)\n";
    file << "Random,InsertionSort," << insertionRandom.count() << "\n";
    file << "Random,SelectionSort," << selectionRandom.count() << "\n";
    file << "NearlySorted,InsertionSort," << insertionNearly.count() << "\n";
    file << "NearlySorted,SelectionSort," << selectionNearly.count() << "\n";
    file.close();
}

// ============================================================
// Experiment 2: VIP Extraction - Flash Sale
// ============================================================

void experiment2_VIPExtraction() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "PHASE 2: VIP Extraction (Flash Sale)\n";
    std::cout << std::string(60, '=') << "\n";
    
    const int N = 100000;
    const int K = 500;
    
    std::vector<int> data = generateRandomVector(N, 0, 1000000);
    
    std::cout << "\nExtracting Top " << K << " from " << N << " elements...\n";
    
    // Method 1: Full Heap Sort then take top K
    std::vector<int> data1 = copyVector(data);
    auto start = std::chrono::high_resolution_clock::now();
    SortingAlgorithms::heapSort(data1);
    auto end = std::chrono::high_resolution_clock::now();
    auto fullSortTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Method 2: Build Heap + Extract Max K times
    std::vector<int> data2 = copyVector(data);
    start = std::chrono::high_resolution_clock::now();
    std::vector<int> topK = SortingAlgorithms::extractTopK(data2, K);
    end = std::chrono::high_resolution_clock::now();
    auto heapExtractTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "\n[1] Full Heap Sort + Take Top " << K << ": " << fullSortTime.count() << " μs\n";
    std::cout << "[2] Build Heap + Extract Max " << K << " times: " << heapExtractTime.count() << " μs\n";
    std::cout << "\n  Speedup (Method 2 vs Method 1): " 
              << (double)fullSortTime.count() / heapExtractTime.count() << "x\n";
    
    // Export to CSV
    std::ofstream file("phase2_results.csv");
    file << "Method,Time(μs)\n";
    file << "FullSort," << fullSortTime.count() << "\n";
    file << "HeapExtract," << heapExtractTime.count() << "\n";
    file.close();
}

// ============================================================
// Experiment 3: Macro-Scale Routing - End-of-Day Logistics
// ============================================================

void experiment3_MacroScale() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "PHASE 3: Macro-Scale Routing (End-of-Day Logistics)\n";
    std::cout << std::string(60, '=') << "\n";
    
    std::vector<int> sizes = {10000, 50000, 100000, 500000, 1000000};
    
    std::cout << "\nComparing Heap Sort vs Radix Sort on postal codes (5-digit):\n";
    std::cout << std::string(70, '-') << "\n";
    std::cout << std::setw(12) << "Size" 
              << std::setw(20) << "Heap Sort (μs)" 
              << std::setw(20) << "Radix Sort (μs)"
              << std::setw(15) << "Speedup" << "\n";
    std::cout << std::string(70, '-') << "\n";
    
    std::ofstream file("phase3_results.csv");
    file << "Size,HeapSortTime(μs),RadixSortTime(μs)\n";
    
    int threshold = -1;
    
    for (int size : sizes) {
        std::vector<int> data = generatePostalCodes(size);
        
        // Heap Sort
        std::vector<int> data1 = copyVector(data);
        auto start = std::chrono::high_resolution_clock::now();
        SortingAlgorithms::heapSort(data1);
        auto end = std::chrono::high_resolution_clock::now();
        auto heapTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // Radix Sort
        std::vector<int> data2 = copyVector(data);
        start = std::chrono::high_resolution_clock::now();
        SortingAlgorithms::radixSort(data2);
        end = std::chrono::high_resolution_clock::now();
        auto radixTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        double speedup = (double)heapTime.count() / radixTime.count();
        
        std::cout << std::setw(12) << size 
                  << std::setw(20) << heapTime.count()
                  << std::setw(20) << radixTime.count()
                  << std::setw(14) << std::fixed << std::setprecision(2) << speedup << "x\n";
        
        file << size << "," << heapTime.count() << "," << radixTime.count() << "\n";
        
        // Detect when Radix Sort becomes faster
        if (threshold == -1 && radixTime.count() < heapTime.count()) {
            threshold = size;
        }
    }
    
    file.close();
    
    std::cout << "\nRadix Sort becomes faster than Heap Sort at N = " << threshold << "\n";
}

// ============================================================
// Main Function
// ============================================================

int main() {
    std::cout << "\n";
    std::cout << "============================================================\n";
    std::cout << "   E-COMMERCE SORTING PIPELINE - PERFORMANCE ANALYSIS\n";
    std::cout << "============================================================\n";
    
    // Run all experiments
    experiment1_MicroScale();
    experiment2_VIPExtraction();
    experiment3_MacroScale();
    
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "All experiments completed. Results exported to CSV files.\n";
    std::cout << std::string(60, '=') << "\n\n";
    
    return 0;
}