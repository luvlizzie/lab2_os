#include <iostream>
#include <climits>
#include "../include/common.h"

using std::cout;
using std::cerr;
using std::endl;

#ifdef _WIN32
DWORD WINAPI min_max_thread(LPVOID param) {
#else
void* min_max_thread(void* param) {
#endif
    ThreadData* data = static_cast<ThreadData*>(param);
    
    if (!data || !data->array || data->size == 0) {
        cerr << "MinMax thread: Invalid data received" << endl;
#ifdef _WIN32
        return 1;
#else
        return nullptr;
#endif
    }
    
    data->min = data->array[0];
    data->max = data->array[0];
    
    cout << "MinMax thread: Searching for min and max..." << endl;
    
    for (size_t i = 0; i < data->size; ++i) {
        int current = data->array[i];
        
        if (current < data->min) {
            data->min = current;
            cout << "MinMax thread: New minimum found: " << current << " at position " << i << endl;
        }
        
        if (current > data->max) {
            data->max = current;
            cout << "MinMax thread: New maximum found: " << current << " at position " << i << endl;
        }
        
        sleep_ms(SLEEP_MS_MIN_MAX);
    }
    
    cout << "MinMax thread: Final results - Min: " << data->min
         << ", Max: " << data->max << endl;
    
    data->min_max_completed = true;
    
#ifdef _WIN32
    return 0;
#else
    return nullptr;
#endif
}
