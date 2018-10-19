#include "../include/util.hpp"

long long ScopedTimer::calculateDuration_us() {
    end = std::chrono::system_clock::now();
    duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return duration_us;
}

long long ScopedTimer::getDuration_us(){
    return calculateDuration_us();
}

std::string ScopedTimer::getDuration_pretty(){
    double us = (double) getDuration_us();
    std::string unit = "_not_set_";

    if (us < 1000) {
        unit = (std::string) "us";
    }else if (us < 1000 * 1000) {
        us /= 1000;
        unit = (std::string) "ms";
    }else if (us < 1000 * 1000 * 1000) {
        us /= 1000 * 1000;
        unit = (std::string) "s";
    }else if (us < 1000.0 * 1000.0 * 1000.0 * 60.0) {
        us /= 1000.0 * 1000.0 * 60.0;
        unit = (std::string) "m";
    }else{
        us /= 1000.0 * 1000.0 * 60.0 * 60.0;
        unit = (std::string) "h";
    }

    std::string out = name_;
    out.append(": ");
    out.append(to_string(us));
    out.append(unit);
    return out;
}

void ScopedTimer::prettyPrint(const std::string& string){
    std::cout << string << std::endl;
}

ScopedTimer::ScopedTimer(){
    name_ = "_Unnamed_";
    printAtScopeEnd_ = false;
    start = std::chrono::system_clock::now();
}

ScopedTimer::ScopedTimer(std::string name){
    name_ = name;
    printAtScopeEnd_ = false;
    start = std::chrono::system_clock::now();
}

ScopedTimer::ScopedTimer(std::string name, bool printAtScopeEnd){
    name_ = name;
    printAtScopeEnd_ = printAtScopeEnd;
    start = std::chrono::system_clock::now();
}

ScopedTimer::~ScopedTimer(){
    end = std::chrono::system_clock::now();
    if (printAtScopeEnd_){
        prettyPrint(getDuration_pretty());
    }
}

bool Math::seeded = false;
void Math::seed(){
    if (!Math::seeded) {
        std::srand(std::time(nullptr));
        Math::seeded = true;
    }
}

int Math::random(int under) {
    Math::seed();
    return std::rand() / ( (RAND_MAX + 1u) / under );  // Note: 1+rand()%6 is biased
}

int Math::random(int min, int max) {
    Math::seed();
    return min + std::rand() / ( (RAND_MAX + 1u) / max );
}

void Math::fillRndArr(int a[], int size, int min, int max) {
    for (int i = 0; i < size; i++) {
        a[i] = Math::random(min, max);
    }
}

bool Sort::isSorted(int a[], int N){
    for (int n = 0; n < N - 1; n++){
        if (a[n] > a[n + 1]) {
            return false;
        }
    }
    return true;
}

void Sort::isSortedPrint(int a[], int N){
    Sort::print(a, N);
    Sort::isSortedPrettyPrint(a, N);
}

void Sort::isSortedPrettyPrint(int a[], int N){
    std::string arr = " {";
    int small = 3;

    if (small >= (int)N/2) {
        for (int i = 0; i < N - 1; i++){
            arr.append(to_string(a[i]));
            arr.append(", ");
        }
        arr.append(to_string(a[N - 1]));
    } else {
        for (int i = 0; i < small; i++){
            arr.append(to_string(a[i]));
            arr.append(", ");
        }
        arr.append(" ... ");
        for (int i = N - small; i < N - 1; i++){
            arr.append(to_string(a[i]));
            arr.append(", ");
        }
        arr.append(to_string(a[N - 1]));
    }
    arr.append("} ");
    std::cout << "Array [" << N << "]" << arr << (Sort::isSorted(a, N) ? "in order." : "UNORDERED!") << std::endl;
}

bool Sort::less(int a[], int i, int j){
    if (a[i] < a[j]) {
        return true;
    }
    return false;
}


void Sort::exch(int a[], int i, int j){
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void Sort::print(int a[], int N){
    std::cout << "[";
    for (int i = 0; i < N - 1; i++) {
        std::cout << a[i] << ", ";
    }
    std::cout << a[N - 1] << "]" << std::endl;
}

void Sort::print(int a[], int low, int high){
    std::cout << "[";
    for (int i = low; i < high; i++) {
        std::cout << a[i] << ", ";
    }
    std::cout << a[high] << "]" << std::endl;
}

void Selection::sort(int a[], int N){
    for (int n = 0; n < N; n++) {
        int min = n;
        for (int m = n + 1; m < N; m++) {
            if (a[m] < a[min]) {
                min = m;
            }
        }
        Sort::exch(a, n, min);
    }
}

void Insertion::sort(int a[], int N){
    for (int i = 1; i < N; i++){
        for (int j = i; j > 0; j--){
            if (a[j] < a[j - 1]) {
                Sort::exch(a, j, j - 1);
            }
        }
    }
}


int* Merge::aux;

void Merge::sort(int a[], int N){
    Merge::aux = new int[N];
    sort(a, 0, N - 1);
    delete[] Merge::aux;
}


void Merge::sort(int a[], int low, int high){
    if (high <= low) {
        return;
    }

    int mid = low + (high - low) / 2;

    sort(a, low, mid);
    sort(a, mid + 1, high);
    merge(a, low, mid, high);
}

void Merge::merge(int a[], int low, int mid, int high){
    for (int n = low; n <= high; n++){
        Merge::aux[n] = a[n];
    }

    int i = low; 
    int j = mid + 1;

    for (int n = low; n <= high; n++) {

        if (i > mid) {
            a[n] = Merge::aux[j++];

        } else if (j > high) {
            a[n] = Merge::aux[i++];

        } else if (Merge::aux[j] < Merge::aux[i]) {
            a[n] = Merge::aux[j++];

        } else {
            a[n] = Merge::aux[i++];

        }
        
    }

}

void Heap::sink(int a[], int size, int k) {
    int j;
    while (2 * k <= size) {
        
        j = 2 * k;

        if (j < size && Sort::less(a, j, j + 1)) {
            j++;
        }

        if (!Sort::less(a, k, j)) {
            break;
        }

        Sort::exch(a, k, j);
        k = j;
    }
}

void Heap::sort(int a[], int N) {

    for (int k = N/2; k >= 1; k--){
        Heap::sink(a, k, N);
    }

    while (N > 1){
        Sort::exch(a, 1, N--);
        Heap::sink(a, 1, N);
    }

}