#!/bin/bash

echo "=== Threads Lab2 - Test Runner ==="
echo "Version 1.0"
echo "=================================="

# Clean previous build
rm -rf build
mkdir build
cd build

# Configure and build
cmake ..
make

# Run tests
echo -e "\n=== Running Tests ===\n"
./test_runner

# Show summary
echo -e "\n=== Test Summary ==="
echo "Date: $(date)"
echo "Tests completed"

cd ..
