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

ficha* CrearFicha(int izq, int der){ // Esta Funcion de encarga de crear las fichas, asigna valores de la derecha e izquierda
    ficha* nueva = new ficha;
    nueva->izq=izq;
    nueva->der=der;
    nueva->prox=nullptr;
    return nueva;
}

void AgregarAMano(Jugador* jugador, ficha* nuevaFicha){ // Esta Funcion tiene como objetivo agregar fichas a la mano del jugador. TIENES QUE LIMITARLA PARA 7 PERSONAS
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

void ListasFichas(ficha *&inicio, int valorIzq, int valorDer){ // Esta Funcion tiene como objetivo hacer el guardado de todas las fichas, para no perderlas
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

pozo* crearPozo(ficha* fichasMezcladas){ // Esta Funcion se encarga de hacer el pozo de fichas restantes
    pozo* nuevoPozo = new pozo;
    nuevoPozo->fichapozo = fichasMezcladas;
    nuevoPozo->prox = nullptr;
    return nuevoPozo;
}


int generarAleatorio(int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, max - 1);
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
void repartirFichas(pozo *&Pozo, Jugador* jugadores[], int numJugadores) {
    int fichasPorJugador = 7;
    int piezasDisponibles = contarFichasPozo(Pozo);
    
    for(int i = 0; i < numJugadores; i++){
        for(int j = 0; j < fichasPorJugador; j++){
            if(piezasDisponibles > 0){
                int posAleatoria = generarAleatorio(piezasDisponibles - 1);
                ficha* fichaObtenida = eliminarFichaPozo(Pozo, posAleatoria);
                if(fichaObtenida != nullptr){
                    AgregarAMano(jugadores[i], fichaObtenida);
                    piezasDisponibles--;
                }
            }
        }
    }
}

bool puedeJugar(ficha* f, mesa* Mesa){
    if(f == nullptr) return false;
    if(Mesa == nullptr || Mesa->inicio == nullptr) return true;
    return (f->izq == Mesa->izq || f->der == Mesa->izq || 
            f->izq == Mesa->der || f->der == Mesa->der);
}

bool tieneJugada(Jugador* jugador, mesa* Mesa){
    ficha* aux = jugador->mano;
    while(aux != nullptr){
        if(puedeJugar(aux, Mesa)) return true;
        aux = aux->prox;
    }
    return false;
}

// Funciones de visualizacion
void mostrarFicha(ficha* f){
    if(f == nullptr){
        cout << "[vacio]";
        return;
    }
    cout << "[" << f->izq << "|" << f->der << "]";
}

void tomarDelPozo(Jugador* jugador, pozo* &Pozo){
    int cantidadPozo = contarFichasPozo(Pozo);
    if(cantidadPozo == 0){
        cout << "No hay fichas en el pozo!" << endl;
        return;
    }
    
    int posAleatoria = generarAleatorio(cantidadPozo);
    ficha* fichaObtenida = eliminarFichaPozo(Pozo, posAleatoria);
    
    if(fichaObtenida != nullptr){
        fichaObtenida->prox = nullptr;
        AgregarAMano(jugador, fichaObtenida);
        cout << "El jugador " << jugador->id << " tomo una ficha del pozo: ";
        mostrarFicha(fichaObtenida);
        cout << endl;
    }
}

int sumaPuntos(ficha* mano){
    int suma = 0;
    ficha* aux = mano;
    while(aux != nullptr){
        suma += aux->izq + aux->der;
        aux = aux->prox;
    }
    return suma;
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
    cout << "\n========== MESA ==========" << endl;
    if(Mesa->inicio == nullptr){
        cout << "La mesa esta vacia" << endl;
    } else {
        cout << "Extremo izquierdo: " << Mesa->izq << " | Extremo derecho: " << Mesa->der << endl;
        cout << "Fichas en mesa: ";
        ficha* aux = Mesa->inicio;
        while(aux != nullptr){
            mostrarFicha(aux);
            cout << " ";
            aux = aux->prox;
        }
        cout << endl;
    }
    cout << "=========================\n" << endl;
}

void colocarFicha(ficha* fichaJugada, mesa* &Mesa, char lado){
    if(Mesa->inicio == nullptr){
        Mesa->inicio = fichaJugada;
        Mesa->fin = fichaJugada;
        Mesa->izq = fichaJugada->izq;
        Mesa->der = fichaJugada->der;
        fichaJugada->prox = nullptr;
        return;
    }
    
    if(lado == 'i' || lado == 'I'){
        if(fichaJugada->der == Mesa->izq){
            fichaJugada->prox = Mesa->inicio;
            Mesa->inicio = fichaJugada;
            Mesa->izq = fichaJugada->izq;
        } else if(fichaJugada->izq == Mesa->izq){
            int temp = fichaJugada->izq;
            fichaJugada->izq = fichaJugada->der;
            fichaJugada->der = temp;
            fichaJugada->prox = Mesa->inicio;
            Mesa->inicio = fichaJugada;
            Mesa->izq = fichaJugada->izq;
        }
    } else {
        if(fichaJugada->izq == Mesa->der){
            Mesa->fin->prox = fichaJugada;
            Mesa->fin = fichaJugada;
            Mesa->der = fichaJugada->der;
            fichaJugada->prox = nullptr;
        } else if(fichaJugada->der == Mesa->der){
            int temp = fichaJugada->izq;
            fichaJugada->izq = fichaJugada->der;
            fichaJugada->der = temp;
            Mesa->fin->prox = fichaJugada;
            Mesa->fin = fichaJugada;
            Mesa->der = fichaJugada->der;
            fichaJugada->prox = nullptr;
        }
    }
}

void tomarYMostrar(Jugador* jugador, pozo* &Pozo){
    int cantidadAntes = contarFichas(jugador->mano);
    while(!tieneJugada(jugador, nullptr) && contarFichasPozo(Pozo) > 0){
        tomarDelPozo(jugador, Pozo);
        int cantidadDespues = contarFichas(jugador->mano);
        if(cantidadDespues > cantidadAntes){
            ficha* fichaObtenida = jugador->mano;
            while(fichaObtenida->prox != nullptr){
                fichaObtenida = fichaObtenida->prox;
            }
            cout << "Tomaste: ";
            mostrarFicha(fichaObtenida);
            cout << endl;
        }
    }
}

bool jugarTurno(Jugador* jugador, mesa* &Mesa, pozo* &Pozo, int numJugadores){
    cout << "\n--- Turno del Jugador " << jugador->id << " ---" << endl;
    mostrarMesa(Mesa);
    mostrarMano(jugador);
    
    if(!tieneJugada(jugador, Mesa)){
        if(numJugadores == 4 || contarFichasPozo(Pozo) == 0){
            cout << "No puedes jugar. Pasas tu turno." << endl;
            return false;
        }
        
        cout << "No tienes jugada. Tomando del pozo..." << endl;
        tomarYMostrar(jugador, Pozo);
        mostrarMano(jugador);
        
        if(!tieneJugada(jugador, Mesa)){
            cout << "Aun no tienes jugada. Pasas tu turno." << endl;
            return false;
        }
    }
    
    cout << "\nFichas que puedes jugar: ";
    ficha* aux = jugador->mano;
    int pos = 1;
    while(aux != nullptr){
        if(puedeJugar(aux, Mesa)){
            cout << pos << " ";
        }
        aux = aux->prox;
        pos++;
    }
    cout << endl;
    
    int fichaElegida;
    cout << "Selecciona la ficha que quieres jugar (numero): ";
    cin >> fichaElegida;
    
    ficha* fichaJugada = eliminarFichaDeMano(jugador, fichaElegida);
    if(fichaJugada == nullptr){
        cout << "Ficha invalida." << endl;
        return false;
    }
    
    char lado = 'd';
    if(Mesa->inicio != nullptr){
        cout << "En que lado? (i=izquierda, d=derecha): ";
        cin >> lado;
    }
    
    colocarFicha(fichaJugada, Mesa, lado);
    
    cout << "Jugaste: ";
    mostrarFicha(fichaJugada);
    cout << endl;
    
    return true;
}

void limpiarFichas(ficha* &mano){
    ficha* actual = mano;
    while(actual != nullptr){
        ficha* siguiente = actual->prox;
        delete actual;
        actual = siguiente;
    }
    mano = nullptr;
}

void limpiarPozo(pozo* &Pozo){
    pozo* actual = Pozo;
    while(actual != nullptr){
        pozo* siguiente = actual->prox;
        delete actual;
        actual = siguiente;
    }
    Pozo = nullptr;
}

void limpiarMesa(mesa* &Mesa){
    if(Mesa != nullptr){
        limpiarFichas(Mesa->inicio);
        Mesa->inicio = nullptr;
        Mesa->fin = nullptr;
    }
}

void reiniciarManos(Jugador* jugadores[], int numJugadores){
    for(int i = 0; i < numJugadores; i++){
        limpiarFichas(jugadores[i]->mano);
        jugadores[i]->mano = nullptr;
    }
}
int main() {
    cout << "======================================" << endl;
    cout << "   BIENVENIDO AL JUEGO DE DOMINO" << endl;
    cout << "======================================" << endl;
    
    int numJugadores;
    cout << "\nCuantos jugadores van a jugar? (2-4): ";
    cin >> numJugadores;
    
    while(numJugadores < 2 || numJugadores > 4){
        cout << "Numero invalido. Debe ser entre 2 y 4: ";
        cin >> numJugadores;
    }
    
    Jugador* jugadores[4];
    for(int i = 0; i < numJugadores; i++){
        jugadores[i] = new Jugador;
        jugadores[i]->id = i + 1;
        jugadores[i]->mano = nullptr;
        jugadores[i]->puntos = 0;
        jugadores[i]->prox = nullptr;
    }
    
    for(int ronda = 1; ronda <= 3; ronda++){
        cout << "\n\n########################################" << endl;
        cout << "          RONDA " << ronda << endl;
        cout << "########################################" << endl;
        
        ficha* fichasMezcladas = llenarFicha();
        
        // Convertir lista de fichas a lista de pozos
        pozo* Pozo = nullptr;
        pozo* ultimoPozo = nullptr;
        ficha* auxFicha = fichasMezcladas;
        while(auxFicha != nullptr){
            pozo* nuevoNodo = new pozo;
            nuevoNodo->fichapozo = auxFicha;
            nuevoNodo->prox = nullptr;
            
            if(Pozo == nullptr){
                Pozo = nuevoNodo;
                ultimoPozo = nuevoNodo;
            } else {
                ultimoPozo->prox = nuevoNodo;
                ultimoPozo = nuevoNodo;
            }
            
            auxFicha = auxFicha->prox;
        }
        
        repartirFichas(Pozo, jugadores, numJugadores);
        
        mesa* Mesa = new mesa;
        Mesa->inicio = nullptr;
        Mesa->fin = nullptr;
        Mesa->izq = -1;
        Mesa->der = -1;
        
        int jugadorActual = 0;
        for(int i = 0; i < numJugadores; i++){
            ficha* aux = jugadores[i]->mano;
            while(aux != nullptr){
                if(aux->izq == 6 && aux->der == 6){
                    jugadorActual = i;
                    break;
                }
                aux = aux->prox;
            }
        }
        
        bool rondaTerminada = false;
        int turnos = 0;
        int maxTurnos = 100;
        int turnosSinJugar = 0;
        
        while(!rondaTerminada && turnos < maxTurnos){
            bool jugo = jugarTurno(jugadores[jugadorActual], Mesa, Pozo, numJugadores);
            
            if(!jugo){
                turnosSinJugar++;
            } else {
                turnosSinJugar = 0;
            }
            
            if(contarFichas(jugadores[jugadorActual]->mano) == 0){
                cout << "\n¡¡¡ Jugador " << jugadores[jugadorActual]->id << " gano la ronda !!!" << endl;
                rondaTerminada = true;
            }
            
            if(turnosSinJugar >= numJugadores){
                cout << "\n¡¡¡ TRANCA !!! Nadie puede jugar" << endl;
                
                // Determinar ganador por menos puntos
                int menosPuntos = 999999;
                int ganadorTranca = 0;
                for(int i = 0; i < numJugadores; i++){
                    int puntosActuales = sumaPuntos(jugadores[i]->mano);
                    cout << "Jugador " << jugadores[i]->id << " tiene " << puntosActuales << " puntos en su mano" << endl;
                    if(puntosActuales < menosPuntos){
                        menosPuntos = puntosActuales;
                        ganadorTranca = i;
                    }
                }
                cout << "El jugador " << jugadores[ganadorTranca]->id << " tenia menos puntos" << endl;
                rondaTerminada = true;
            }
            
            if(rondaTerminada){
                break;
            }
            
            jugadorActual = (jugadorActual + 1) % numJugadores;
            turnos++;
        }
        
        cout << "\n--- Resumen de la Ronda " << ronda << " ---" << endl;
        for(int i = 0; i < numJugadores; i++){
            int puntosRonda = sumaPuntos(jugadores[i]->mano);
            jugadores[i]->puntos += puntosRonda;
            cout << "Jugador " << jugadores[i]->id << ": " << puntosRonda 
                 << " puntos en esta ronda (Total: " << jugadores[i]->puntos << ")" << endl;
        }
        
        limpiarMesa(Mesa);
        delete Mesa;
        limpiarPozo(Pozo);
        reiniciarManos(jugadores, numJugadores);
    }
    
    cout << "\n\n======================================" << endl;
    cout << "       RESULTADOS FINALES" << endl;
    cout << "======================================" << endl;
    
    int ganador = 0;
    for(int i = 1; i < numJugadores; i++){
        if(jugadores[i]->puntos < jugadores[ganador]->puntos){
            ganador = i;
        }
    }
    
    cout << "\n¡¡¡ EL GANADOR ES EL JUGADOR " << jugadores[ganador]->id << " !!!" << endl;
    cout << "Con " << jugadores[ganador]->puntos << " puntos totales" << endl;
    
    for(int i = 0; i < numJugadores; i++){
        delete jugadores[i];
    }
    
    return 0;
}