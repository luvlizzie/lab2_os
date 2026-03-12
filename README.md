# Lab2_OS - Threads in C++

## Description
A cross-platform C++ program demonstrating multithreading with three threads:
- **main**: Creates array and manages threads
- **min_max**: Finds minimum and maximum elements
- **average**: Calculates arithmetic mean

## Requirements
- C++17 compatible compiler
- CMake 3.14+
- Google Test (automatically downloaded)

## Building
```bash
chmod +x run_tests.sh
./run_tests.sh
```

## Project Structure
```text
├── include/          # Header files
│   └── common.h      # Common constants and structures
├── src/              # Source files
│   ├── main.cpp      # Main thread
│   ├── min_max.cpp   # Min/max finding thread
│   └── average.cpp   # Average calculating thread
├── tests/            # Unit tests
│   ├── test_runner.cpp
│   ├── test_min_max.cpp
│   └── test_average.cpp
└── CMakeLists.txt    # Build configuration
```

## Thread Synchronization
- Windows: CreateThread + WaitForSingleObject
- macOS/Linux: pthread_create + pthread_join

## Author
Elizaveta Kudinova
