#include <unistd.h>

#include <cmath>
#include <fstream>
#include <iostream>

#include "FechoConvexo.hpp"
#include "Ponto.hpp"
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

int main(int argc, char** argv) {
    srand(time(0));
    int c;

    c = getopt(argc, argv, "i:");

    switch (c) {
        case 'i': {
            cout << "argumento para i: " << optarg << endl;
            // generateRandomInputDots(20);
            Stack<Ponto> pontosStack = readDotsFromFile(optarg);

            int size = pontosStack.getSize();

            Ponto* pontosArray = new Ponto[size];

            for (int i = 0; i < size; i++) {
                pontosArray[i] = pontosStack.pop();
            }

            FechoConvexo f = FechoConvexo(pontosArray, size);

            unsigned long grahamMerge = f.getFechoConvexoGraham(0);
            unsigned long grahamInsertion = f.getFechoConvexoGraham(1);
            unsigned long grahamBucket = f.getFechoConvexoGraham(2);
            unsigned long jarvis = f.getFechoConvexoJarvis(true);

            cout << endl;
            cout << "GRAHAM+MERGESORT: " << ((double)grahamMerge / 1000000) << "ms" << endl;
            cout << "GRAHAM+INSERTIONSORT: " << ((double)grahamInsertion / 1000000) << "ms" << endl;
            cout << "GRAHAM+LINEAR: " << ((double)grahamBucket / 1000000) << "ms" << endl;
            cout << "JARVIS: " << ((double)jarvis / 1000000) << "ms" << endl;

            delete pontosArray;
            break;
        }
        default: {
            cout << "Argumento inválido" << endl;
            break;
        }
    }

    return 0;
}