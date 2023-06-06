#pragma once

#include <cmath>
#include <iostream>

using namespace std;

class Ponto {
   public:
    Ponto(int x, int y);

    Ponto();

    static double calculaDistancia(Ponto a, Ponto b);

    static int getOrientacao(Ponto p0, Ponto p1, Ponto p2);

    bool operator==(Ponto &p);

    bool operator!=(Ponto &p);

    int getX();

    int getY();

    void setX(int newX);

    void setY(int newY);

    void print();

    string toString();

   private:
    int x, y;
};