#pragma once

#include <cmath>
#include <iostream>

using namespace std;

class Ponto {
   public:
    Ponto(int x, int y) : x(x), y(y) {}

    Ponto() : Ponto(0, 0) {}

    static double calculaDistancia(Ponto a, Ponto b) {
        return sqrt(pow(a.getX() - b.getX(), 2) + pow(a.getY() - b.getY(), 2));
    }

    static int getOrientacao(Ponto p0, Ponto p1, Ponto p2) {
        int val = (p1.getY() - p0.getY()) * (p2.getX() - p1.getX()) - (p1.getX() - p0.getX()) * (p2.getY() - p1.getY());

        if (val == 0)
            return 0;               // colinear
        return (val > 0) ? 1 : -1;  // sentido horario ou anti-horario
    }

    bool operator==(Ponto &p) {
        if (x == p.getX() && y == p.getY())
            return true;
        return false;
    }

    bool operator!=(Ponto &p) {
        if (x == p.getX() && y == p.getY())
            return false;
        return true;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    void setX(int newX) {
        x = newX;
    }

    void setY(int newY) {
        y = newY;
    }

    void print() {
        std::cout << "(" << x << ", " << y << ")";
    }

    string toString() {
        return "(" + to_string(x) + ", " + to_string(y) + ")";
    }

   private:
    int x, y;
};