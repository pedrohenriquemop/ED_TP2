#include <cmath>
#include <fstream>
#include <iostream>

#include "FechoConvexo.hpp"
#include "Ponto.hpp"
#include "Sorter.hpp"
#include "Stack.hpp"
#include "Utils.hpp"

using namespace std;

int* gerenateRandomArray(int size) {
    int* arr = new int[size];

    int maxRand = max(100, (int)pow(10, (int)log10(size)));

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % maxRand;
    }

    return arr;
}

void generateRandomInputDots(int size) {
    ofstream out("dots.in");

    for (int i = 0; i < size; i++) {
        out << rand() % 100 << " " << rand() % 100 << endl;
    }

    out.close();
}

Stack<Ponto> readDotsFromFile(string fileName) {
    ifstream in;
    in.open(fileName);

    Stack<Ponto> stack;
    Ponto p;

    if (in.is_open()) {
        int x, y;
        while (in >> x) {
            in >> y;
            Ponto p = Ponto(x, y);
            stack.push(p);
        }
    }

    return stack;
}

void testSortingMethods() {
    int SIZE = 20;

    int* arr1 = gerenateRandomArray(SIZE);
    int* arr2 = gerenateRandomArray(SIZE);
    int* arr3 = gerenateRandomArray(SIZE);

    cout << "Array 1: " << endl;
    utils::printArray(arr1, SIZE);
    Sorter::mergeSort(arr1, 0, SIZE - 1);
    cout << "Array 1 mergeSort:" << endl;
    utils::printArray(arr1, SIZE);

    cout << "Array 2: " << endl;
    utils::printArray(arr2, SIZE);
    Sorter::insertionSort(arr2, SIZE);
    cout << "Array 2 insertionSort:" << endl;
    utils::printArray(arr2, SIZE);

    cout << "Array 3: " << endl;
    utils::printArray(arr3, SIZE);
    Sorter::countingSort(arr3, SIZE);
    cout << "Array 3 countingSort:" << endl;
    utils::printArray(arr3, SIZE);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
}

int main() {
    srand(time(0));

    // generateRandomInputDots(20);
    Stack<Ponto> pontosStack = readDotsFromFile("dots.in");

    int size = pontosStack.getSize();

    Ponto* pontosArray = new Ponto[size];

    for (int i = 0; i < size; i++) {
        pontosArray[i] = pontosStack.pop();
    }

    FechoConvexo f = FechoConvexo(pontosArray, size);

    f.getFechoConvexoGraham(0);
    f.getFechoConvexoJarvis(0);
    f.getFechoConvexoGraham(1);
    f.getFechoConvexoJarvis(1);

    delete pontosArray;

    return 0;
}