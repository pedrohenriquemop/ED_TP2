#pragma once

#include <iostream>

#include "Ponto.hpp"

using namespace std;

namespace utils {
void printArray(int arr[], int n);

void printArray(Ponto* arr, int n);

void copyArray(Ponto* arrSource, Ponto* arrTarget, int size);

void swap(Ponto& p1, Ponto& p2);

int getMax(int arr[], int size);

int getMin(int arr[], int size);
}  // namespace utils