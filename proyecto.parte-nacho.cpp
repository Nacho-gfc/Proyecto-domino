#include <iostream>
#include <random>
using namespace std;

struct ficha{
    int izq;
    int der;
    ficha* prox;
};

struct Jugador {
    int id;
    ficha* mano;
    int puntos;
    Jugador* prox;
};

struct pozo{
    ficha* fichapozo;
    pozo* prox;
};

struct mesa{
    ficha* inicio;
    ficha* fin;
    int izq;
    int der;
};

ficha* CrearFicha(int izq, int der){
    ficha* nueva = new ficha;
    nueva->izq=izq;
    nueva->der=der;
    nueva->prox=nullptr;
    return nueva;
}

void ListasFichas(ficha *&inicio, int valorIzq, int valorDer){
    ficha *nuevo = CrearFicha(valorIzq, valorDer);
    if (inicio==nullptr){
        inicio = nuevo;
    } else{
        ficha *auxiliar = inicio;
        while (auxiliar->prox != NULL){
        auxiliar = auxiliar->prox;
    }
    auxiliar->prox = nuevo;
    }
}

ficha* llenarFicha(){
    ficha* fichasMezcladas = nullptr;
    for(int i=0; i<=6; i++){
        for(int j = i; j <=6;j++){
            ListasFichas(fichasMezcladas, i, j);
        }
    }
    return fichasMezcladas;
}

pozo* crearPozo(ficha* fichasMezcladas){
    pozo* nuevoPozo = new pozo;
    nuevoPozo->fichapozo = fichasMezcladas;
    nuevoPozo->prox = nullptr;
    return nuevoPozo;
}

Jugador* RepartirFichas(pozo *&pozo, int n, ficha* mano){
    
}