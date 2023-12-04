#include <iostream>
#include <string>
#include <climits>
#include "Nodo.h"


using namespace std;

int obtenerMejorJugada(Nodo* raiz) {
    int mejorValor = INT_MIN;
    int mejorColumna = -1;
    Nodo* hijo = raiz->hijosIzquierda;

    while (hijo != nullptr) {
        int valor = hijo->minimax(5, INT_MIN, INT_MAX);

        if (valor > mejorValor) {
            mejorValor = valor;
            mejorColumna = hijo->matriz[0][0];  // La columna en el nodo hijo
        }

        hijo = hijo->hijosDerecha;
    }

    return mejorColumna;
}
int main() {
    Nodo* raiz = new Nodo;
    raiz->nuevoNodo(true);
    // Configura la matriz y otros valores según tus necesidades
    // Puedes establecer el estado inicial del tablero aquí

    raiz->imprimirMatriz();  // Imprime el tablero inicial
    int columnaJugadaHumano;

    int cantFichas=0;
    
    Nodo* actual;

    while (cantFichas < 42) {  // Número máximo de fichas en un tablero de 7x6
        // Turno del jugador humano
        int columnaJugadaHumano;
        do {
            cout << "Turno del jugador humano. Ingresa la columna para tu jugada (0-6): ";
            cin >> columnaJugadaHumano;
        } while (!raiz->realizarJugadaHumano(columnaJugadaHumano));

        raiz->imprimirMatriz();  // Imprime el tablero después de la jugada del humano

        // Verificar si el jugador humano ganó
        if (raiz->evaluarMatriz('O') == 1) {
            cout << "¡Felicidades! El jugador humano ha ganado." << endl;
            break;
        }

        // Turno de la computadora
        int mejorColumna = obtenerMejorJugada(raiz);
        cout << "Turno de la computadora. Juega en la columna " << mejorColumna << "." << endl;

        // Realiza la jugada en el tablero
        Nodo* hijo = raiz->nodoHijo(raiz,mejorColumna);

        hijo->imprimirMatriz();  // Imprime el tablero después de la jugada de la computadora

        // Verificar si la computadora ganó
        if (hijo->evaluarMatriz('X') == 1) {
            cout << "¡La computadora ha ganado!" << endl;
            break;
        }

        // Actualizar el nodo raíz para el próximo turno
        
        actual = hijo;

        cantFichas += 2;  // Se han realizado dos jugadas en cada turno
    }

    if (cantFichas == 42) {
        cout << "El juego ha terminado en empate." << std::endl;
    }

    // Recuerda liberar la memoria cuando hayas terminado
    delete raiz;

    return 0;
}