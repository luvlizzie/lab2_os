#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <stdexcept>
#include "../include/common.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;

int getValidatedInt(const string& prompt, int min, int max);
vector<int> inputArray(int size);
void printArray(const vector<int>& arr, const string& label);
void replaceMinMaxWithAverage(vector<int>& arr, int min, int max, double average);

#ifdef _WIN32
    #define THREAD_CREATE(thread, func, param) CreateThread(NULL, 0, func, param, 0, &thread)
    #define THREAD_JOIN(handle) WaitForSingleObject(handle, INFINITE); CloseHandle(handle)
#else
    #define THREAD_CREATE(thread, func, param) pthread_create(&thread, NULL, func, param)
    #define THREAD_JOIN(thread) pthread_join(thread, NULL)
#endif

int getValidatedInt(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= min && value <= max) {
            cin.ignore(256, '\n');
            return value;
        }
        cerr << "Invalid input. Please enter a number between "
             << min << " and " << max << endl;
        cin.clear();
        cin.ignore(256, '\n');
    }
}

vector<int> inputArray(int size) {
    vector<int> arr(size);
    cout << "Enter " << size << " integers:" << endl;
    
    for (int i = 0; i < size; ++i) {
        cout << "Element " << i + 1 << ": ";
        while (!(cin >> arr[i])) {
            cerr << "Invalid input. Please enter an integer." << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Element " << i + 1 << ": ";
        }
    }
    cin.ignore(256, '\n');
    
    return arr;
}

void printArray(const vector<int>& arr, const string& label) {
    cout << label << ": [";
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << arr[i];
        if (i < arr.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

void replaceMinMaxWithAverage(vector<int>& arr, int min, int max, double average) {
    int roundedAvg = static_cast<int>(average);
    
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == min || arr[i] == max) {
            arr[i] = roundedAvg;
        }
    }
}

int main() {
    try {
        cout << "\n=== Threads Lab2 - Main Program ===" << endl;
        cout << string(40, '=') << endl;
        
        // Step 1: Create array
        int size = getValidatedInt("Enter array size: ", MIN_ARRAY_SIZE, MAX_ARRAY_SIZE);
        
        vector<int> arr = inputArray(size);
        
        cout << "\nOriginal array:" << endl;
        printArray(arr, "Array");
        
        // Step 2: Create threads
        ThreadData data;
        data.array = arr.data();
        data.size = arr.size();
        data.min = 0;
        data.max = 0;
        data.average = 0.0;
        data.min_max_completed = false;
        data.average_completed = false;
        
        cout << "\nCreating threads..." << endl;
        
        #ifdef _WIN32
        HANDLE hMinMax = THREAD_CREATE(hMinMax, min_max_thread, &data);
        HANDLE hAverage = THREAD_CREATE(hAverage, average_thread, &data);
        
        if (!hMinMax || !hAverage) {
            cerr << "Failed to create threads" << endl;
            return 1;
        }
        #else
        thread_t minMaxThread, averageThread;
        
        if (pthread_create(&minMaxThread, NULL, min_max_thread, &data) != 0 ||
            pthread_create(&averageThread, NULL, average_thread, &data) != 0) {
            cerr << "Failed to create threads" << endl;
            return 1;
        }
        #endif
        
        // Step 3: Wait for threads to complete
        cout << "Waiting for threads to complete..." << endl;
        
        #ifdef _WIN32
        WaitForSingleObject(hMinMax, INFINITE);
        WaitForSingleObject(hAverage, INFINITE);
        
        CloseHandle(hMinMax);
        CloseHandle(hAverage);
        #else
        pthread_join(minMaxThread, NULL);
        pthread_join(averageThread, NULL);
        #endif
        
        cout << "Both threads completed successfully!" << endl;
        
        // Step 4: Replace min and max with average
        cout << "\nMin value: " << data.min << endl;
        cout << "Max value: " << data.max << endl;
        cout << "Average value: " << data.average << endl;
        
        replaceMinMaxWithAverage(arr, data.min, data.max, data.average);
        
        cout << "\nModified array (min/max replaced with average):" << endl;
        printArray(arr, "Array");
        
        cout << "\n=== Program completed successfully ===" << endl;
        
    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
