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
        while (auxiliar->prox != NULL){
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

void repartirFichas(pozo *&Pozo, Jugador *&player1, Jugador *&player2)
{
    int cont=14, piezas=28;
    while (cont > 0)
    {
        pozo *aux=Pozo;
        int num= generarAleatorio(piezas), pos=0;

        while (aux!=NULL && pos !=num)
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

        while (aux!=NULL && pos !=num)
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

        while (aux!=NULL && pos !=num)
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

//main
int main() {

    Jugador jugadores[4];

    int N;
    cout<< "Cuantos jugadores? (2-4) : ";
    cin>>N;

    for(int i = 0; i < N; i++) {
        cout<< "Nombre del jugador" << (i + 1) << ":  ";
        cin>>jugadores[i].nombre;
    }
    
    for(int r= 1; r>=3; r++)
    jugarRonda(r , N, jugadores);

    cout<<"Resutado final del juego"

    int ganador = 0;
    for (int i=1 ; i<N; i++)
        if(jugadores[i].puntos < jugadores[ganador].puntos)
            ganador = i;

    cout<< "El ganador es:" <<jugadores[ganador].nombre<< "CON" <<jugadores[ganador].puntos<< "puntos.";

    return 0;

}
