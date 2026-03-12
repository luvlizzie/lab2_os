#ifndef COMMON_H
#define COMMON_H

#include <cstddef>

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <unistd.h>
#endif

static constexpr int MIN_ARRAY_SIZE = 1;
static constexpr int MAX_ARRAY_SIZE = 1000;
static constexpr int MIN_ELEMENT_VALUE = -1000;
static constexpr int MAX_ELEMENT_VALUE = 1000;
static constexpr int SLEEP_MS_MIN_MAX = 7;
static constexpr int SLEEP_MS_AVERAGE = 12;

struct ThreadData {
    int* array;
    size_t size;
    int min;
    int max;
    double average;
    bool min_max_completed;
    bool average_completed;
};

#ifdef _WIN32
    typedef HANDLE thread_t;
    #define THREAD_RETURN DWORD WINAPI
    typedef LPVOID thread_param_t;
#else
    typedef pthread_t thread_t;
    #define THREAD_RETURN void*
    typedef void* thread_param_t;
#endif

#ifdef _WIN32
DWORD WINAPI min_max_thread(LPVOID param);
DWORD WINAPI average_thread(LPVOID param);
#else
void* min_max_thread(void* param);
void* average_thread(void* param);
#endif

void sleep_ms(int milliseconds);

#endif
