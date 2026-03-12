#ifndef COMMON_H
#define COMMON_H

#include <cstddef>

static constexpr int MIN_ARRAY_SIZE = 1;
static constexpr int MAX_ARRAY_SIZE = 1000;
static constexpr int MIN_ELEMENT_VALUE = -1000;
static constexpr int MAX_ELEMENT_VALUE = 1000;
static constexpr int SLEEP_MS_MIN_MAX = 7;
static constexpr int SLEEP_MS_AVERAGE = 12;

// Структура для передачи данных в потоки
struct ThreadData {
    int* array;
    size_t size;
    int min;
    int max;
    double average;
    bool min_max_completed;
    bool average_completed;
};

#endif
