#include <iostream>
#include "../include/common.h"

using std::cout;
using std::cerr;
using std::endl;

#ifdef _WIN32
DWORD WINAPI average_thread(LPVOID param) {
#else
void* average_thread(void* param) {
#endif
    ThreadData* data = static_cast<ThreadData*>(param);
    
    if (!data || !data->array || data->size == 0) {
        cerr << "Average thread: Invalid data received" << endl;
#ifdef _WIN32
        return 1;
#else
        return nullptr;
#endif
    }
    
    long long sum = 0;
    
    cout << "Average thread: Calculating average..." << endl;
    
    for (size_t i = 0; i < data->size; ++i) {
        sum += data->array[i];
        cout << "Average thread: Sum after " << (i + 1) << " elements: " << sum << endl;
        
        sleep_ms(SLEEP_MS_AVERAGE);
    }
    
    data->average = static_cast<double>(sum) / data->size;
    
    cout << "Average thread: Final average: " << data->average << endl;
    
    data->average_completed = true;
    
#ifdef _WIN32
    return 0;
#else
    return nullptr;
#endif
}
