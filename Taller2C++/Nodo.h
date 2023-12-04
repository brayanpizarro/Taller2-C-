#pragma once
#include <iostream>
#include <vector>

using namespace std;

struct Nodo{
    char matriz[6][7];
    bool esMaximizador;
    int Valor;
    Nodo* hijosIzquierda;
    Nodo* hijosDerecha;
    
    void nuevoNodo(bool jugador);
    Nodo* nodoHijo(Nodo* raiz,int ColumnaJugada);
    int evaluarMatriz(char Jugador);
    int minimax(int profundidad, int alfa, int beta);
    void imprimirMatriz();
    bool realizarJugadaHumano(int columnaJugada);
};
