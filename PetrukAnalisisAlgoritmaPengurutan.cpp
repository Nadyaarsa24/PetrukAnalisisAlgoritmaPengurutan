#include <iostream>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <ctime>

// Deklarasi fungsi sorting
void bubbleSort(int arr[], int n);
void insertionSort(int arr[], int n);
void selectionSort(int arr[], int n);
void mergeSort(int arr[], int l, int r);
void quickSort(int arr[], int low, int high);

void merge(int arr[], int l, int m, int r);
int partition(int arr[], int low, int high);

// Fungsi untuk menghasilkan array dengan kondisi yang berbeda
void generateRandomArray(int arr[], int n);
void generateSortedArray(int arr[], int n);
void generateReverseSortedArray(int arr[], int n);

// Fungsi untuk mengukur waktu eksekusi
void measureTime(void (*sortFunc)(int[], int), int arr[], int n, const std::string &sortName, const std::string &dataCondition);
void measureTime(void (*sortFunc)(int[], int, int), int arr[], int n, const std::string &sortName, const std::string &dataCondition);

// Fungsi utama
int main() {
    const int sizes[] = {10, 100, 500, 1000, 10000};
    const int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < numSizes; i++) {
        int n = sizes[i];

        int* arrRandom = new int[n];
        int* arrSorted = new int[n];
        int* arrReverseSorted = new int[n];

        generateRandomArray(arrRandom, n);
        std::copy(arrRandom, arrRandom + n, arrSorted);
        std::copy(arrRandom, arrRandom + n, arrReverseSorted);

        std::sort(arrSorted, arrSorted + n);
        std::reverse(arrReverseSorted, arrReverseSorted + n);

        std::cout << "Array Size: " << n << std::endl;

        measureTime(bubbleSort, arrRandom, n, "Bubble Sort", "Random");
        measureTime(bubbleSort, arrSorted, n, "Bubble Sort", "Sorted");
        measureTime(bubbleSort, arrReverseSorted, n, "Bubble Sort", "Reverse Sorted");

        measureTime(insertionSort, arrRandom, n, "Insertion Sort", "Random");
        measureTime(insertionSort, arrSorted, n, "Insertion Sort", "Sorted");
        measureTime(insertionSort, arrReverseSorted, n, "Insertion Sort", "Reverse Sorted");

        measureTime(selectionSort, arrRandom, n, "Selection Sort", "Random");
        measureTime(selectionSort, arrSorted, n, "Selection Sort", "Sorted");
        measureTime(selectionSort, arrReverseSorted, n, "Selection Sort", "Reverse Sorted");

        measureTime(mergeSort, arrRandom, n, "Merge Sort", "Random");
        measureTime(mergeSort, arrSorted, n, "Merge Sort", "Sorted");
        measureTime(mergeSort, arrReverseSorted, n, "Merge Sort", "Reverse Sorted");

        measureTime(quickSort, arrRandom, n, "Quick Sort", "Random");
        measureTime(quickSort, arrSorted, n, "Quick Sort", "Sorted");
        measureTime(quickSort, arrReverseSorted, n, "Quick Sort", "Reverse Sorted");

        delete[] arrRandom;
        delete[] arrSorted;
        delete[] arrReverseSorted;

        std::cout << std::endl;
    }

    return 0;
}

// Implementasi fungsi sorting
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                std::swap(arr[j], arr[j+1]);
            }
        }
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        std::swap(arr[min_idx], arr[i]);
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    int
    i = 0, j = 0, k = l;
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

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void generateRandomArray(int arr[], int n) {
    std::srand(std::time(nullptr));
    for (int i = 0; i < n; i++) {
        arr[i] = std::rand() % 10000;
    }
}

void generateSortedArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
}

void generateReverseSortedArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i - 1;
    }
}

void measureTime(void (*sortFunc)(int[], int), int arr[], int n, const std::string &sortName, const std::string &dataCondition) {
    int* arrCopy = new int[n];
    std::copy(arr, arr + n, arrCopy);

    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(arrCopy, n);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::micro> duration = end - start;
    std::cout << sortName << " (" << dataCondition << "): " << duration.count() << " microseconds" << std::endl;

    delete[] arrCopy;
}

void measureTime(void (*sortFunc)(int[], int, int), int arr[], int n, const std::string &sortName, const std::string &dataCondition) {
    int* arrCopy = new int[n];
    std::copy(arr, arr + n, arrCopy);

    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(arrCopy, 0, n - 1);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::micro> duration = end - start;
    std::cout << sortName << " (" << dataCondition << "): " << duration.count() << " microseconds" << std::endl;

    delete[] arrCopy;
}

