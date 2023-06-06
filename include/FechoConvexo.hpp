#pragma once

#include <chrono>

#include "Ponto.hpp"
#include "Stack.hpp"
#include "Utils.hpp"

class FechoConvexo {
   public:
    FechoConvexo(Ponto* arrPontos, int size);

    ~FechoConvexo();

    unsigned long getFechoConvexoGraham(int sortType = 0, bool printResult = false);

    unsigned long getFechoConvexoJarvis(bool printResult = false);

   private:
    Ponto* pontos;
    Ponto p0;
    int pontosSize;

    chrono::_V2::high_resolution_clock::time_point TIME_COUNTER;

    void startTimer();

    unsigned long endTimer();

    int findMinXIndex(Ponto* pontos, int size);

    int findMinYIndex(Ponto* pontos, int size);

    void bucketSortPontos(Ponto* arr, int size);

    void insertionSortPontos(Ponto* arr, int size);

    void mergeSortPontos(Ponto* pontos, int esq, int dir);

    void mergePontos(Ponto* pontos, int esq, int meio, int dir);
};