
ficha* CrearFicha(int izq, int der){
    ficha* nueva = new ficha;
    nueva->izq=izq;
    nueva->der=der;
    nueva->siguiente=nullptr;
    return nueva;
}

ficha* llenarFicha(ficha*& FichasMezcladas, pozo* Pozo, int NumeroDeJugadores){
    
    for(int i=0, i<=6,){
        i++;
        for(int j = 0, j <=6){
            j++;
            ficha* nueva = CrearFicha(i,j);
        }
    }
}

