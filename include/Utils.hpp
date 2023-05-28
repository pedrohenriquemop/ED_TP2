#pragma once

#include <iostream>

#include "Ponto.hpp"

using namespace std;

namespace utils {
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\n";
}

void printArray(Ponto* arr, int n) {
    for (int i = 0; i < n; i++)
        cout << ">" << arr[i].toString() << endl;
    cout << "\n";
}

void copyArray(Ponto* arrSource, Ponto* arrTarget, int size) {
    for (int i = 0; i < size; i++) {
        arrTarget[i] = arrSource[i];
    }
}

void swap(Ponto& p1, Ponto& p2) {
    Ponto temp = p1;
    p1 = p2;
    p2 = temp;
}
}  // namespace utils