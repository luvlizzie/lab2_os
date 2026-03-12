cmake_minimum_required(VERSION 3.14)
project(ThreadsLab2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Исполняемый файл
add_executable(threads.exe
    src/main.cpp
    src/min_max.cpp
    src/average.cpp
    src/thread_utils.cpp
)

target_include_directories(threads.exe PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Поддержка Windows
if (MINGW)
    set_target_properties(threads.exe PROPERTIES SUFFIX "")
endif()

# Поддержка потоков
find_package(Threads REQUIRED)
target_link_libraries(threads.exe PRIVATE Threads::Threads)

# Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(test_runner
    tests/test_runner.cpp
    tests/test_min_max.cpp
    tests/test_average.cpp
    src/min_max.cpp
    src/average.cpp      
    src/thread_utils.cpp
)

target_link_libraries(test_runner
    gtest_main
    gmock
    pthread
)

target_include_directories(test_runner PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

enable_testing()
add_test(NAME all_tests COMMAND test_runner)
