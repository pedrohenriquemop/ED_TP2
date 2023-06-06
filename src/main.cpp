#include <cmath>
#include <fstream>
#include <iostream>

#include "FechoConvexo.hpp"
#include "Ponto.hpp"
#include "Stack.hpp"
#include "Utils.hpp"

using namespace std;

Stack<Ponto> readDotsFromFile(string fileName) {
    ifstream in;
    in.open(fileName);

    if (in.fail()) {
        throw runtime_error("Erro ao ler aquivo \"" + fileName + "\"");
    }

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

    if (string(argv[1]) != "fecho" || argv[2] == nullptr) {
        cout << "Argumento inválido. O argumento de linha de comando deve ter o seguinte formato: fecho arquivoentrada" << endl;
        return 0;
    }

    try {
        Stack<Ponto> pontosStack = readDotsFromFile(argv[2]);

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

        return 0;
    } catch (exception& e) {
        cout << e.what() << endl;
        exit(1);
    }
}