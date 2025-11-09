#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include <random>

using namespace std;

struct ficha {
    int izq;
    int der;
    ficha* sig;
    ficha* prev;
};

struct Jugador {
    int id;
    ficha* mano;
    int puntos;
    Jugador* siguiente;
};

struct pozo {
    ficha* tope;
};

struct mesa{
    ficha* inicio;
    ficha* fin;
    int izq;
    int der;
};

