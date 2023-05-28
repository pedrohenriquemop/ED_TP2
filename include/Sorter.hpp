#pragma once

#include <iostream>

#include "Utils.hpp"

using namespace std;

class Sorter {
   public:
    static void mergeSort(int arr[], int esq, int dir) {
        if (esq < dir) {
            int meio = esq + (dir - esq) / 2;
            mergeSort(arr, esq, meio);
            mergeSort(arr, meio + 1, dir);
            merge(arr, esq, meio, dir);
        }
    }

    static void insertionSort(int arr[], int size) {
        int k, j;
        for (int i = 1; i < size; i++) {
            k = arr[i];
            j = i - 1;

            while (j >= 0 && arr[j] > k) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = k;
        }
    }

    static void countingSort(int arr[], int size) {
        int max = utils::getMax(arr, size);
        int min = utils::getMin(arr, size);
        int range = max - min + 1;

        int* counter = new int[range];

        for (int i = 0; i < range; i++) {
            counter[i] = 0;
        }

        int* saida = new int[size];

        for (int i = 0; i < size; i++)
            counter[arr[i] - min]++;

        for (int i = 1; i < range; i++)
            counter[i] += counter[i - 1];

        for (int i = size - 1; i >= 0; i--) {
            saida[counter[arr[i] - min] - 1] = arr[i];
            counter[arr[i] - min]--;
        }

        for (int i = 0; i < size; i++)
            arr[i] = saida[i];

        delete[] counter;
        delete[] saida;
    }

   private:
    static void merge(int arr[], int esq, int meio, int dir) {
        int arrEsqSize = meio - esq + 1;
        int arrDirSize = dir - meio;

        int* arrEsq = new int[arrEsqSize];
        int* arrDir = new int[arrDirSize];

        for (int i = 0; i < arrEsqSize; i++) {
            arrEsq[i] = arr[esq + i];
        }

        for (int j = 0; j < arrDirSize; j++) {
            arrDir[j] = arr[meio + 1 + j];
        }

        int arrEsqIndex = 0, arrDirIndex = 0, mergedArrIndex = esq;

        while (arrEsqIndex < arrEsqSize && arrDirIndex < arrDirSize) {
            if (arrEsq[arrEsqIndex] <= arrDir[arrDirIndex]) {
                arr[mergedArrIndex] = arrEsq[arrEsqIndex];
                arrEsqIndex++;
            } else {
                arr[mergedArrIndex] = arrDir[arrDirIndex];
                arrDirIndex++;
            }
            mergedArrIndex++;
        }

        while (arrEsqIndex < arrEsqSize) {
            arr[mergedArrIndex] = arrEsq[arrEsqIndex];
            arrEsqIndex++;
            mergedArrIndex++;
        }

        while (arrDirIndex < arrDirSize) {
            arr[mergedArrIndex] = arrDir[arrDirIndex];
            arrDirIndex++;
            mergedArrIndex++;
        }

        delete[] arrEsq;
        delete[] arrDir;
    }
};