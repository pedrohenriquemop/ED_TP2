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

    static void bucketSort(int arr[], int size) {
        static int* bucket[10];
        static int i, j[10], k, l, d = 1;
        int c;

        for (int i = 0; i < 10; i++) {
            bucket[i] = new int[size];
        }
        c = utils::maxNumberOfDigits(arr, size);

        for (int m = 0; m < c; m++) {
            for (i = 0; i < 10; i++)
                j[i] = 0;
            for (i = 0; i < size; i++) {
                k = (arr[i] / d) % 10;
                bucket[k][j[k]] = arr[i];
                j[k]++;
            }

            l = 0;
            for (i = 0; i < 10; i++) {
                for (k = 0; k < j[i]; k++) {
                    arr[l] = bucket[i][k];
                    l++;
                }
            }
            d *= 10;
        }
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