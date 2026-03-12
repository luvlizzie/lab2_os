# Lab2_OS - Threads in C++

## Description
A cross-platform C++ program demonstrating multithreading with three threads:
- **main**: Creates array and manages threads
- **min_max**: Finds minimum and maximum elements with 7ms sleep after each comparison
- **average**: Calculates arithmetic mean with 12ms sleep after each summation

## Requirements
- C++17 compatible compiler
- CMake 3.14+
- Google Test (automatically downloaded)

## Building and Running

```bash
# Clone the repository
git clone git@github.com:luvlizzie/lab2_os.git
cd lab2_os

# Make the test script executable
chmod +x run_tests.sh

# Build and run tests
./run_tests.sh

# Run the main program
cd build
./threads.exe
```

## Project Structure

```text
lab2_os/
├── include/
│   └── common.h           # Common constants, structures and thread declarations
├── src/
│   ├── main.cpp           # Main thread: creates array, starts threads, replaces min/max
│   ├── min_max.cpp        # Min/max thread: finds min and max with 7ms sleeps
│   ├── average.cpp        # Average thread: calculates mean with 12ms sleeps
│   └── thread_utils.cpp   # Cross-platform utility functions (sleep, etc.)
├── tests/
│   ├── test_runner.cpp    # Google Test runner
│   ├── test_min_max.cpp   # Unit tests for min_max thread (5 tests)
│   └── test_average.cpp   # Unit tests for average thread (6 tests)
├── CMakeLists.txt         # CMake build configuration
└── README.md              # This file
```

## Features

### Cross-Platform Support

- macOS/Linux: Uses pthread library
- Windows: Uses Windows Thread API (CreateThread, WaitForSingleObject)

### Thread Synchronization

- Main thread waits for both worker threads using:

    - `pthread_join` (macOS/Linux)
    - `WaitForSingleObject` (Windows)

### Thread Implementation

**Min/Max Thread**

- Iterates through array to find minimum and maximum elements
- Sleeps for **7 milliseconds** after each comparison
- Prints progress and final results to console

**Average Thread**

- Calculates sum of all array elements
- Sleeps for **12 milliseconds** after each addition
- Computes and prints arithmetic mean

### Error Handling

- Input validation for array size and elements
- Null pointer checks in threads
- Exception handling in main program

### Testing

The project includes **11 unit tests**:

#### MinMaxTest (5 tests)

- `FindsMinAndMaxInPositiveArray`
- `FindsMinAndMaxInNegativeArray`
- `HandlesSingleElementArray`
- `HandlesIdenticalElements`
- `SetsCompletedFlag`

#### AverageTest (6 tests)

- `CalculatesAverageOfPositiveNumbers`
- `CalculatesAverageOfNegativeNumbers`
- `CalculatesAverageOfMixedNumbers`
- `HandlesSingleElement`
- `HandlesLargeNumbers`
- `SetsCompletedFlag`

All tests pass automatically with the provided test script.

### Example Run

```text
=== Threads Lab2 - Main Program ===
========================================
Enter array size: 5
Enter 5 integers:
Element 1: 10
Element 2: 25
Element 3: 5
Element 4: 30
Element 5: 15

Original array:
Array: [10, 25, 5, 30, 15]

Creating threads...
Waiting for threads to complete...

MinMax thread: Searching for min and max...
MinMax thread: New maximum found: 25 at position 1
MinMax thread: New minimum found: 5 at position 2
MinMax thread: New maximum found: 30 at position 3
MinMax thread: Final results - Min: 5, Max: 30

Average thread: Calculating average...
Average thread: Sum after 1 elements: 10
Average thread: Sum after 2 elements: 35
Average thread: Sum after 3 elements: 40
Average thread: Sum after 4 elements: 70
Average thread: Sum after 5 elements: 85
Average thread: Final average: 17

Both threads completed successfully!

Min value: 5
Max value: 30
Average value: 17

Modified array (min/max replaced with average):
Array: [10, 25, 17, 17, 15]

=== Program completed successfully ===
```

### Requirements Met

| Requirement | Implementation |
|-------------|----------------|
| Main creates array | `inputArray()` function |
| Main creates min_max and average threads | `pthread_create` / `CreateThread` |
| Wait for thread completion | `pthread_join` / `WaitForSingleObject` |
| Replace min/max with average | `replaceMinMaxWithAverage()` |
| Min/max thread with 7ms sleeps | `sleep_ms(SLEEP_MS_MIN_MAX)` |
| Average thread with 12ms sleeps | `sleep_ms(SLEEP_MS_AVERAGE)` |
### Author

Elizaveta Kudinova

### License

This project is created for educational purposes as part of Operating Systems course.
