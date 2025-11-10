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
// Elimina un nodo del pozo y retorna la ficha
ficha* eliminarFichaPozo(pozo* &Pozo, int posicion){
    if(Pozo == nullptr) return nullptr;
    
    pozo* aux = Pozo;
    pozo* anterior = nullptr;
    int pos = 0;
    
    while(aux != nullptr && pos < posicion){
        anterior = aux;
        aux = aux->prox;
        pos++;
    }
    
    if(aux == nullptr) return nullptr;
    
    ficha* fichaObtenida = aux->fichapozo;
    
    if(anterior == nullptr){
        Pozo = aux->prox;
    } else {
        anterior->prox = aux->prox;
    }
    
    delete aux;
    return fichaObtenida;
}

// Elimina una ficha de la mano del jugador
ficha* eliminarFichaDeMano(Jugador* jugador, int posicion){
    if(jugador->mano == nullptr) return nullptr;
    
    ficha* aux = jugador->mano;
    ficha* anterior = nullptr;
    int pos = 1;
    
    while(aux != nullptr && pos < posicion){
        anterior = aux;
        aux = aux->prox;
        pos++;
    }
    
    if(aux == nullptr) return nullptr;
    
    if(anterior == nullptr){
        jugador->mano = aux->prox;
    } else {
        anterior->prox = aux->prox;
    }
    
    aux->prox = nullptr;
    return aux;
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

// Funciones de visualización
void mostrarFicha(ficha* f){
    if(f == nullptr){
        cout << "[vacío]";
        return;
    }
    cout << "[" << f->izq << "|" << f->der << "]";
}

void mostrarMano(Jugador* jugador){
    cout << "Jugador " << jugador->id << " - Fichas:" << endl;
    ficha* aux = jugador->mano;
    int pos = 1;
    while(aux != nullptr){
        cout << "  " << pos << ". ";
        mostrarFicha(aux);
        cout << endl;
        aux = aux->prox;
        pos++;
    }
}

void mostrarMesa(mesa* Mesa){
    cout << "\n=========================";
    cout << "\nMESA: ";
    ficha* aux = Mesa->inicio;
    while(aux != nullptr){
        mostrarFicha(aux);
        cout << " ";
        aux = aux->prox;
    }
    cout << "\n=========================\n" << endl;
}

int main() {
    cout << "Proyecto Domino - En desarrollo" << endl;
    return 0;
}