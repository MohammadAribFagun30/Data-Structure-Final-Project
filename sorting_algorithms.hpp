#define SORTING_ALGORITHMS_HPP
#define SORTING_ALGORITHMS_HPP

#include <vector>
#include <iostream>
#include <cstring>
#include <algorithm>  // ONLY for std::swap (allowed for swapping elements)

class SortingAlgorithms {
public:
    // ============================================================
    // 1. INSERTION SORT - Optimized with shifting (O(n²))
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
    // 2. SELECTION SORT - Baseline O(n²)
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
    // 3. HEAP SORT - Array-based Max-Heap (O(n log n))
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
    
    // Extract top K elements without full sort
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
    // 4. COUNTING SORT - Stable integer sort (O(n + k))
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
        
        // Build output array (stable - iterating from end)
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
    // 5. RADIX SORT - Base-10 using Counting Sort (O(d * (n + k)))
    // ============================================================
private:
    static void countingSortByDigit(std::vector<int>& arr, int exp) {
        int n = arr.size();
        std::vector<int> output(n);
        std::vector<int> count(10, 0);  // Base-10 digits (0-9)
        
        // Count occurrences of each digit
        for (int i = 0; i < n; i++) {
            int digit = (arr[i] / exp) % 10;
            count[digit]++;
        }
        
        // Cumulative sum for stable sorting
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        
        // Build output (stable - iterating from end)
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
    
    // ============================================================
    // 6. BUBBLE SORT - Additional O(n²) for comparison
    // ============================================================
    static void bubbleSort(std::vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
    }
    
    // ============================================================
    // 7. MERGE SORT - Additional O(n log n) for comparison
    // ============================================================
private:
    static void merge(std::vector<int>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        
        std::vector<int> L(n1);
        std::vector<int> R(n2);
        
        for (int i = 0; i < n1; i++) L[i] = arr[left + i];
        for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
        
        int i = 0, j = 0, k = left;
        
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }
        
        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }
    
    static void mergeSortRecursive(std::vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortRecursive(arr, left, mid);
            mergeSortRecursive(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }
    
public:
    static void mergeSort(std::vector<int>& arr) {
        mergeSortRecursive(arr, 0, arr.size() - 1);
    }
};

