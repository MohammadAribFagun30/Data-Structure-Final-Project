#ifndef SORTING_ALGORITHMS_HPP
#define SORTING_ALGORITHMS_HPP

#include <vector>
#include <iostream>
#include <cstring>

class SortingAlgorithms {
public:
    // ============================================================
    // 1. INSERTION SORT - Optimized with shifting
    // ============================================================
    static void insertionSort(std::vector<int>& arr) {
        int n = arr.size();
        for (int i = 1; i < n; i++) {
            int key = arr[i];
            int j = i - 1;
            
            // Shift elements greater than key to the right
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
    
    // ============================================================
    // 2. SELECTION SORT - Baseline O(N²)
    // ============================================================
    static void selectionSort(std::vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[minIdx]) {
                    minIdx = j;
                }
            }
            if (minIdx != i) {
                std::swap(arr[i], arr[minIdx]);
            }
        }
    }
    
    // ============================================================
    // 3. HEAP SORT - Array-based Max-Heap
    // ============================================================
private:
    static void heapify(std::vector<int>& arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }
        
        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }
    
public:
    static void buildHeap(std::vector<int>& arr) {
        int n = arr.size();
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }
    }
    
    static int extractMax(std::vector<int>& heap, int& heapSize) {
        if (heapSize <= 0) return -1;
        
        int maxVal = heap[0];
        heap[0] = heap[heapSize - 1];
        heapSize--;
        heapify(heap, heapSize, 0);
        
        return maxVal;
    }
    
    static void heapSort(std::vector<int>& arr) {
        int n = arr.size();
        buildHeap(arr);
        
        for (int i = n - 1; i > 0; i--) {
            std::swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }
    
    // Extract top K elements using heap without full sort
    static std::vector<int> extractTopK(std::vector<int>& arr, int k) {
        int n = arr.size();
        buildHeap(arr);
        
        std::vector<int> topK;
        int heapSize = n;
        
        for (int i = 0; i < k && heapSize > 0; i++) {
            topK.push_back(extractMax(arr, heapSize));
        }
        
        return topK;
    }
    
    // ============================================================
    // 4. COUNTING SORT - Stable version
    // ============================================================
    static void countingSort(std::vector<int>& arr, int maxVal = -1) {
        if (arr.empty()) return;
        
        // Find max value if not provided
        if (maxVal == -1) {
            maxVal = arr[0];
            for (int val : arr) {
                if (val > maxVal) maxVal = val;
            }
        }
        
        int n = arr.size();
        std::vector<int> count(maxVal + 1, 0);
        std::vector<int> output(n);
        
        // Count frequencies
        for (int val : arr) {
            count[val]++;
        }
        
        // Cumulative sum for stable sorting
        for (int i = 1; i <= maxVal; i++) {
            count[i] += count[i - 1];
        }
        
        // Build output array (stable)
        for (int i = n - 1; i >= 0; i--) {
            output[count[arr[i]] - 1] = arr[i];
            count[arr[i]]--;
        }
        
        // Copy back
        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }
    }
    
    // ============================================================
    // 5. RADIX SORT - Base-10 using Counting Sort as subroutine
    // ============================================================
private:
    static void countingSortByDigit(std::vector<int>& arr, int exp) {
        int n = arr.size();
        std::vector<int> output(n);
        std::vector<int> count(10, 0);
        
        // Count occurrences of each digit
        for (int i = 0; i < n; i++) {
            int digit = (arr[i] / exp) % 10;
            count[digit]++;
        }
        
        // Cumulative sum
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        
        // Build output (stable)
        for (int i = n - 1; i >= 0; i--) {
            int digit = (arr[i] / exp) % 10;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }
        
        // Copy back
        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }
    }
    
public:
    static void radixSort(std::vector<int>& arr) {
        if (arr.empty()) return;
        
        // Find max value
        int maxVal = arr[0];
        for (int val : arr) {
            if (val > maxVal) maxVal = val;
        }
        
        // Sort by each digit
        for (int exp = 1; maxVal / exp > 0; exp *= 10) {
            countingSortByDigit(arr, exp);
        }
    }
};

#endif