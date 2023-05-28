#pragma once

class Reta {
   public:
    Reta(double a, double b) : a(a), b(b) {}
    Reta() : Reta(0, 0) {}

    int getA() {
        return a;
    }

    int getB() {
        return b;
    }

    void setA(int newA) {
        a = newA;
    }

    void setB(int newB) {
        b = newB;
    }

   private:
    double a, b;
};