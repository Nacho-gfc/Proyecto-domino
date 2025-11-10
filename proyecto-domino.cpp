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

ficha* CrearFicha(int izq, int der){ // Esta Función de encarga de crear las fichas, asigna valores de la derecha e izquierda
    ficha* nueva = new ficha;
    nueva->izq=izq;
    nueva->der=der;
    nueva->prox=nullptr;
    return nueva;
}

void AgregarAMano(Jugador* jugador, ficha* nuevaFicha){ // Esta Función tiene como objetivo agregar fichas a la mano del jugador. TIENES QUE LIMITARLA PARA 7 PERSONAS
    if(jugador->mano == nullptr){
        jugador->mano = nuevaFicha;
    } else {
        ficha* actual = jugador->mano;
        while(actual->prox != nullptr){
            actual = actual->prox;
        }
        actual->prox = nuevaFicha;
    }
}

void ListasFichas(ficha *&inicio, int valorIzq, int valorDer){ // Esta Función tiene como objetivo hacer el guardado de todas las fichas, para no perderlas
    ficha *nuevo = CrearFicha(valorIzq, valorDer);
    if (inicio==nullptr){
        inicio = nuevo;
    } else{
        ficha *auxiliar = inicio;
        while (auxiliar->prox != nullptr){
        auxiliar = auxiliar->prox;
    }
    auxiliar->prox = nuevo;
    }
}

ficha* llenarFicha(){ // Llenar fichas. solo llenara las fichas del lado derecho e izquierdo
    ficha* fichasMezcladas = nullptr;
    for(int i=0; i<=6; i++){
        for(int j = i; j <=6;j++){
            ListasFichas(fichasMezcladas, i, j);
        }
    }
    return fichasMezcladas;
}

pozo* crearPozo(ficha* fichasMezcladas){ // Esta Función se encarga de hacer el pozo de fichas restantes
    pozo* nuevoPozo = new pozo;
    nuevoPozo->fichapozo = fichasMezcladas;
    nuevoPozo->prox = nullptr;
    return nuevoPozo;
}


int generarAleatorio(int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, max);
    return distrib(gen);
}
int contarFichas(ficha* mano){
    int cont = 0;
    ficha* aux = mano;
    while(aux != nullptr){
        cont++;
        aux = aux->prox;
    }
    return cont;
}

int contarFichasPozo(pozo* p){
    int cont = 0;
    pozo* aux = p;
    while(aux != nullptr){
        cont++;
        aux = aux->prox;
    }
    return cont;
}
void repartirFichas(pozo *&Pozo, Jugador *&player1, Jugador *&player2)
{
    int cont=14, piezas=28;
    while (cont > 0)
    {
        pozo *aux=Pozo;
        int num= generarAleatorio(piezas), pos=0;

        while (aux!=nullptr && pos !=num)
        {
            aux=aux->prox;
        }
        if (cont > 7)
            AgregarAMano(player1,aux->fichapozo);
        else
            AgregarAMano(player2,aux->fichapozo);
        
        cont--;
        piezas--;
    }
}

void repartirFichas(pozo *&Pozo, Jugador *&player1, Jugador *&player2, Jugador *&player3)
{
    int cont=21, piezas=28;
    while (cont > 0)
    {
        pozo *aux=Pozo;
        int num= generarAleatorio(piezas), pos=0;

        while (aux!=nullptr && pos !=num)
        {
            aux=aux->prox;
        }
        if (cont > 14)
            AgregarAMano(player1,aux->fichapozo);
        else if (cont > 7)
            AgregarAMano(player2,aux->fichapozo);
        else
            AgregarAMano(player3, aux->fichapozo);
        
        cont--;
        piezas--;
    }
}

void repartirFichas(pozo *&Pozo, Jugador *&player1, Jugador *&player2, Jugador *&player3, Jugador *&player4)
{
    int cont=28, piezas=28;
    while (cont > 0)
    {
        pozo *aux=Pozo;
        int num= generarAleatorio(piezas), pos=0;

        while (aux!=nullptr && pos !=num)
        {
            aux=aux->prox;
        }
        if (cont > 21)
            AgregarAMano(player1,aux->fichapozo);
        else if (cont > 14)
            AgregarAMano(player2,aux->fichapozo);
        else if (cont > 7)
            AgregarAMano(player3,aux->fichapozo);
        else
            AgregarAMano(player4, aux->fichapozo);
        
        cont--;
        piezas--;
    }
}


int main() {
    cout << "Proyecto Domino - En desarrollo" << endl;
    return 0;
}