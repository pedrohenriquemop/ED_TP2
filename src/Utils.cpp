#include "Utils.hpp"

void utils::printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\n";
}

void utils::printArray(Ponto* arr, int n) {
    for (int i = 0; i < n; i++)
        cout << ">" << arr[i].toString() << endl;
    cout << "\n";
}

void utils::copyArray(Ponto* arrSource, Ponto* arrTarget, int size) {
    for (int i = 0; i < size; i++) {
        arrTarget[i] = arrSource[i];
    }
}

void utils::swap(Ponto& p1, Ponto& p2) {
    Ponto temp = p1;
    p1 = p2;
    p2 = temp;
}

int utils::getMax(int arr[], int size) {
    int max = arr[0];

    for (int i = 1; i < size; i++) {
        if (arr[i] > max) max = arr[i];
    }

    return max;
}

int utils::getMin(int arr[], int size) {
    int min = arr[0];

    for (int i = 1; i < size; i++) {
        if (arr[i] < min) min = arr[i];
    }

    return min;
}