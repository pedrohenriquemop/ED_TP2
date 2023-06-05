#pragma once

#include "Ponto.hpp"
#include "Sorter.hpp"
#include "Stack.hpp"
#include "Utils.hpp"

class FechoConvexo {
   public:
    FechoConvexo(Ponto* arrPontos, int size) {
        pontosSize = size;

        pontos = new Ponto[pontosSize];
        utils::copyArray(arrPontos, pontos, size);
    }

    ~FechoConvexo() {
        delete[] pontos;
    }

    void getFechoConvexoGraham(int sortType = 0) {  // 0 = mergeSort, 1 = insertionSort, 2 = bucketSort
        if (sortType < 0 || sortType > 2) {
            throw runtime_error("sortType must be 0, 1 or 2");
        }

        if (pontosSize < 3)
            return;

        Ponto* pontosCopy = new Ponto[pontosSize];
        utils::copyArray(pontos, pontosCopy, pontosSize);

        int minYIndex = findMinYIndex(pontosCopy, pontosSize);
        utils::swap(pontosCopy[0], pontosCopy[minYIndex]);

        p0 = pontosCopy[0];
        int newSize = pontosSize - 1;
        Ponto* newPontos = new Ponto[newSize];

        for (int i = 0; i < newSize; i++) {
            newPontos[i] = pontosCopy[i + 1];
        }

        if (sortType == 0) {
            mergeSortPontos(newPontos, 0, newSize - 1);

            // cout << "newPontos depois merge: " << newSize << endl;
            // utils::printArray(newPontos, newSize);
            // cout << "------------" << endl;
        } else if (sortType == 1) {
            insertionSortPontos(newPontos, newSize);
        }

        Stack<Ponto> stack;
        stack.push(p0);
        stack.push(newPontos[0]);
        stack.push(newPontos[1]);

        for (int i = 2; i < newSize; i++) {
            while (Ponto::getOrientacao(stack.getSecond(), stack.getTop(), newPontos[i]) != -1)
                stack.pop();
            stack.push(newPontos[i]);
        }

        string sortName = "bucketSort";
        if (sortType == 0)
            sortName = "mergeSort";
        else if (sortType == 1)
            sortName = "insertionSort";

        cout
            << "FECHO GRAHAM (" << sortName << "): " << endl;
        stack.print();
    }

    void getFechoConvexoJarvis(int sortType = 0) {
        if (sortType < 0 || sortType > 2) {
            throw runtime_error("sortType must be 0, 1 or 2");
        }

        if (pontosSize < 3)
            return;

        Ponto* pontosCopy = new Ponto[pontosSize];
        utils::copyArray(pontos, pontosCopy, pontosSize);

        int minXIndex = findMinXIndex(pontosCopy, pontosSize);

        Stack<Ponto> fecho;

        Ponto pivot = pontosCopy[minXIndex];  // ponto pivo
        Ponto curr = pivot;                   // proximo ponto do fecho

        do {
            p0 = curr;
            if (sortType == 0) {
                mergeSortPontos(pontosCopy, 0, pontosSize - 1);
            } else if (sortType == 1) {
                insertionSortPontos(pontosCopy, pontosSize);
            }

            fecho.push(curr);
            curr = pontosCopy[0];

        } while (pivot != curr);

        string sortName = "bucketSort";
        if (sortType == 0)
            sortName = "mergeSort";
        else if (sortType == 1)
            sortName = "insertionSort";

        cout
            << "FECHO JARVIS (" << sortName << "): " << endl;
        fecho.print();
    }

   private:
    Ponto* pontos;
    Ponto p0;
    int pontosSize;

    int findMinXIndex(Ponto* pontos, int size) {
        int minIndex = 0, xMin = pontos[0].getX();

        for (int i = 1; i < size; i++) {
            int x = pontos[i].getX();

            if ((x < xMin) || (xMin == x && pontos[i].getY() < pontos[minIndex].getY())) {
                xMin = x;
                minIndex = i;
            }
        }

        return minIndex;
    }

    int findMinYIndex(Ponto* pontos, int size) {
        int minIndex = 0, yMin = pontos[0].getY();

        for (int i = 1; i < size; i++) {
            int y = pontos[i].getY();

            if ((y < yMin) || (yMin == y && pontos[i].getX() < pontos[minIndex].getX())) {
                yMin = y;
                minIndex = i;
            }
        }

        return minIndex;
    }

    // void bucketSortPontos(Ponto* arr, int size) {
    //     static int* bucket[10];
    //     static int i, j[10], k, l, d = 1;
    //     int c;

    //     for (int i = 0; i < 10; i++) {
    //         bucket[i] = new int[size];
    //     }
    //     c = utils::maxNumberOfDigits(arr, size);

    //     for (int m = 0; m < c; m++) {
    //         for (i = 0; i < 10; i++)
    //             j[i] = 0;
    //         for (i = 0; i < size; i++) {
    //             k = (arr[i] / d) % 10;
    //             bucket[k][j[k]] = arr[i];
    //             j[k]++;
    //         }

    //         l = 0;
    //         for (i = 0; i < 10; i++) {
    //             for (k = 0; k < j[i]; k++) {
    //                 arr[l] = bucket[i][k];
    //                 l++;
    //             }
    //         }
    //         d *= 10;
    //     }
    // }

    void insertionSortPontos(Ponto* arr, int size) {
        Ponto p1, p2;
        int j;
        for (int i = 1; i < size; i++) {
            p1 = arr[i];
            j = i - 1;

            while (j >= 0) {
                p2 = arr[j];
                int orientacao = Ponto::getOrientacao(p0, p1, p2);
                if (orientacao == 0 && Ponto::calculaDistancia(p0, p1) < Ponto::calculaDistancia(p0, p2)) {
                    break;
                } else if (orientacao == 1) {
                    break;
                }

                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = p1;
        }
    }

    void mergeSortPontos(Ponto* pontos, int esq, int dir) {
        if (esq < dir) {
            int meio = esq + (dir - esq) / 2;
            mergeSortPontos(pontos, esq, meio);
            mergeSortPontos(pontos, meio + 1, dir);
            mergePontos(pontos, esq, meio, dir);
        }
    }

    void mergePontos(Ponto* pontos, int esq, int meio, int dir) {
        int arrEsqSize = meio - esq + 1;
        int arrDirSize = dir - meio;

        Ponto* arrEsq = new Ponto[arrEsqSize];
        Ponto* arrDir = new Ponto[arrDirSize];

        for (int i = 0; i < arrEsqSize; i++) {
            arrEsq[i] = pontos[esq + i];
        }

        for (int j = 0; j < arrDirSize; j++) {
            arrDir[j] = pontos[meio + 1 + j];
        }

        int arrEsqIndex = 0, arrDirIndex = 0, mergedArrIndex = esq;

        while (arrEsqIndex < arrEsqSize && arrDirIndex < arrDirSize) {
            Ponto p1 = arrEsq[arrEsqIndex];
            Ponto p2 = arrDir[arrDirIndex];

            int orientacao = Ponto::getOrientacao(p0, p1, p2);

            if (orientacao == 0) {  // caso os pontos sejam colineares
                if (Ponto::calculaDistancia(p0, p1) >= Ponto::calculaDistancia(p0, p2)) {
                    pontos[mergedArrIndex] = p1;
                    arrEsqIndex++;
                } else {
                    pontos[mergedArrIndex] = p2;
                    arrDirIndex++;
                }
            } else {  // caso nao sejam colineares
                if (orientacao == -1) {
                    pontos[mergedArrIndex] = p1;
                    arrEsqIndex++;
                } else {
                    pontos[mergedArrIndex] = p2;
                    arrDirIndex++;
                }
            }

            mergedArrIndex++;
        }

        while (arrEsqIndex < arrEsqSize) {
            pontos[mergedArrIndex] = arrEsq[arrEsqIndex];
            arrEsqIndex++;
            mergedArrIndex++;
        }

        while (arrDirIndex < arrDirSize) {
            pontos[mergedArrIndex] = arrDir[arrDirIndex];
            arrDirIndex++;
            mergedArrIndex++;
        }

        delete[] arrEsq;
        delete[] arrDir;
    }
};