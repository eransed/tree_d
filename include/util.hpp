/*
    File: util.hpp
    Updated: 2018-10-10

**/

#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include <cmath>
#include <cstdlib>

#define log(a) std::cout << a
#define logn(a) std::cout << a << std::endl

template <typename T>
std::string to_string (const T& t){
    std::stringstream ss;
    ss << t;
    return ss.str();
}

class ScopedTimer {
private:
    std::chrono::system_clock::time_point start, end;
    long long duration_us;
    std::string name_;
    bool printAtScopeEnd_;
    long long calculateDuration_us();
public:
    long long getDuration_us();
    std::string getDuration_pretty();
    void prettyPrint(const std::string& string);
    ScopedTimer();
    ScopedTimer(std::string name);
    ScopedTimer(std::string name, bool printAtScopeEnd);
    ~ScopedTimer();
};

class Math {
    public:
    static bool seeded;
    static void seed();
    static int random(int under);
    static int random(int min, int max);
    static void fillRndArr(int a[], int size, int min, int max);
};

class Sort {
public:
    static bool isSorted(int a[], int N);
    static void isSortedPrint(int a[], int N);
    static void isSortedPrettyPrint(int a[], int N);
    static bool less(int a[], int i, int j);
    static void exch(int a[], int i, int j);
    static void print(int a[], int N);
    static void print(int a[], int low, int high);
};

class Selection {
public:
    static void sort(int a[], int N);
};

class Insertion {
public:
    static void sort(int a[], int N);
};

class Merge {
    static int * aux;
    static void sort(int a[], int low, int mid);
    static void merge(int a[], int low, int mid, int high);
public:
    static void sort(int a[], int N);
};

class Heap {
    int * heapArray;
public:
    Heap(); // Create a heap.
    // Heap(int N); // Create a uninitialized heap with initial size N.
    // Heap(int * someArray, int N); // Create an heap of size N with the values of someArray.
    ~Heap();
    static void sink(int a[], int size, int k);
    static void sort(int a[], int N);

};

class Shell {
public:
    static void sort(int a[], int N);
};

#endif