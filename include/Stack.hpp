#pragma once

#include <iostream>

using namespace std;

template <class T>  // permite a criação de pilhas de diversos tipos
class Stack {
   public:
    Stack() {  // construtor sem parâmetros para a pilha
        top = -1;
        size = 0;
    };

    void push(T item) {  // insere item na pilha
        if (size == MAXTAM)
            throw runtime_error("Stack is full.");

        top++;
        size++;
        items[top] = item;
    };

    T pop() {  // remove item da pilha, retornando-o
        if (isEmpty())
            throw runtime_error("Stack is empty.");

        T aux = items[top];
        top--;
        size--;
        return aux;
    };

    T getTop() {  // retorna o topo da pilha
        return items[top];
    }

    T getSecond() {
        if (isEmpty())
            throw runtime_error("Stack is empty.");

        if (size < 2)
            throw runtime_error("Stack is not big enough.");

        return items[top - 1];
    }

    int getSize() {  // retorna o tamanho da pilha
        return size;
    }

    bool isEmpty() {  // retorna se a pilha está vazia
        return size == 0;
    }

    void clean() {  // limpa a pilha
        top = -1;
        size = 0;
    };

    void print() {  // imprime o estado atual da pilha
        for (int i = size - 1; i >= 0; i--) {
            cout << items[i].toString() << endl;
        }
    }

   private:
    int top, size;                   // variáveis para o topo e tamanh da pilha
    static const int MAXTAM = 1000;  // tamanho máximo do array que armazena os itens da pilha
    T items[MAXTAM];                 // array que armazena os itens da pilha
};