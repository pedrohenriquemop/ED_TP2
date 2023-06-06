#include "Ponto.hpp"

Ponto::Ponto(int x, int y) : x(x), y(y) {}

Ponto::Ponto() : Ponto(0, 0) {}

double Ponto::calculaDistancia(Ponto a, Ponto b) {
    return sqrt(pow(a.getX() - b.getX(), 2) + pow(a.getY() - b.getY(), 2));
}

int Ponto::getOrientacao(Ponto p0, Ponto p1, Ponto p2) {
    int val = (p1.getY() - p0.getY()) * (p2.getX() - p1.getX()) - (p1.getX() - p0.getX()) * (p2.getY() - p1.getY());

    if (val == 0)
        return 0;               // colinear
    return (val > 0) ? 1 : -1;  // sentido horario ou anti-horario
}

bool Ponto::operator==(Ponto &p) {
    if (x == p.getX() && y == p.getY())
        return true;
    return false;
}

bool Ponto::operator!=(Ponto &p) {
    if (x == p.getX() && y == p.getY())
        return false;
    return true;
}

int Ponto::getX() {
    return x;
}

int Ponto::getY() {
    return y;
}

void Ponto::setX(int newX) {
    x = newX;
}

void Ponto::setY(int newY) {
    y = newY;
}

void Ponto::print() {
    std::cout << "(" << x << ", " << y << ")";
}

string Ponto::toString() {
    return to_string(x) + " " + to_string(y);
}