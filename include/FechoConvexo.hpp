#pragma once

#include "Ponto.hpp"
#include "Sorter.hpp"
#include "Stack.hpp"
#include "Utils.hpp"

class FechoConvexo {
   public:
    FechoConvexo(Ponto* arrPontos, int size) {
        pontosSize = size;
        utils::printArray(arrPontos, pontosSize);

        pontos = new Ponto[pontosSize];
        utils::copyArray(arrPontos, pontos, size);
    }

    ~FechoConvexo() {
        delete[] pontos;
    }

    void getFechoConvexoGrahamMerge() {
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

        mergeSortPontos(newPontos, 0, newSize - 1);

        Stack<Ponto> stack;
        stack.push(p0);
        stack.push(newPontos[0]);
        stack.push(newPontos[1]);

        for (int i = 2; i < newSize; i++) {
            while (Ponto::getOrientacao(stack.getSecond(), stack.getTop(), newPontos[i]) != -1)
                stack.pop();
            stack.push(newPontos[i]);
        }

        cout << "PONTOS NO FECHO: " << endl;
        stack.print();
    }

   private:
    Ponto* pontos;
    Ponto p0;
    int pontosSize;

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

            if (orientacao == 0) {                                                         // caso os pontos sejam colineares
                if (Ponto::calculaDistancia(p0, p1) >= Ponto::calculaDistancia(p0, p2)) {  // o mais proximo de p0 vem antes
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