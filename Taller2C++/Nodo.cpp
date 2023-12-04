#include "Nodo.h"
#include <climits>
void Nodo::nuevoNodo(bool jugador) {
    // Inicializa la matriz con espacios en blanco
    for(int i = 0; i < 6; ++i) {
        for(int j = 0; j < 7; ++j) {
            matriz[i][j] = ' ';
        }
    }

    // Inicializa esMaximizador con true
    esMaximizador = jugador;

    // Inicializa Valor con 0
    Valor = 0;

    // Inicializa los punteros a los hijos con nullptr
    hijosIzquierda = nullptr;
    hijosDerecha = nullptr;
}
Nodo* Nodo::nodoHijo(Nodo* raiz,int columnaJugada) {
    // Crea un nuevo nodo
    Nodo* hijo = new Nodo();

    // Copia la matriz del nodo actual al nuevo nodo
    for(int i = 0; i < 6; ++i) {
        for(int j = 0; j < 7; ++j) {
            hijo->matriz[i][j] = matriz[i][j];
        }
    }

    // Encuentra la fila disponible más baja en la columna jugada
    int fila = 5;
    while(fila >= 0 && hijo->matriz[fila][columnaJugada] != ' ') {
        --fila;
    }

    // Coloca la ficha del jugador actual en la columna jugada
    hijo->matriz[fila][columnaJugada] = (raiz->esMaximizador) ? 'X' : 'O';

    // El nuevo nodo tiene el valor opuesto para esMaximizador
    hijo->esMaximizador = !raiz->esMaximizador;

    // Inicializa los hijos del nuevo nodo con nullptr
    hijo->hijosIzquierda = nullptr;
    hijo->hijosDerecha = nullptr;

    // Devuelve el nuevo nodo
    return hijo;
}

int Nodo::evaluarMatriz(char Jugador) {
    // Verifica si hay un ganador en filas
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j <= 3; ++j) {
            if (matriz[i][j] == Jugador && matriz[i][j + 1] == Jugador && matriz[i][j + 2] == Jugador && matriz[i][j + 3] == Jugador) {
                return 1;  // Hay un ganador
            }
        }
    }

    // Verifica si hay un ganador en columnas
    for (int i = 0; i <= 2; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (matriz[i][j] == Jugador && matriz[i + 1][j] == Jugador && matriz[i + 2][j] == Jugador && matriz[i + 3][j] == Jugador) {
                return 1;  // Hay un ganador
            }
        }
    }

    // Verifica si hay un ganador en diagonales ascendentes
    for (int i = 3; i < 6; ++i) {
        for (int j = 0; j <= 3; ++j) {
            if (matriz[i][j] == Jugador && matriz[i - 1][j + 1] == Jugador && matriz[i - 2][j + 2] == Jugador && matriz[i - 3][j + 3] == Jugador) {
                return 1;  // Hay un ganador
            }
        }
    }

    // Verifica si hay un ganador en diagonales descendentes
    for (int i = 0; i <= 2; ++i) {
        for (int j = 0; j <= 3; ++j) {
            if (matriz[i][j] == Jugador && matriz[i + 1][j + 1] == Jugador && matriz[i + 2][j + 2] == Jugador && matriz[i + 3][j + 3] == Jugador) {
                return 1;  // Hay un ganador
            }
        }
    }

    return 0;  // No hay un ganador aún
}

int Nodo::minimax(int profundidad, int alfa, int beta) {
    if (profundidad == 0 || evaluarMatriz('X') || evaluarMatriz('O')) {
        return evaluarMatriz('X') - evaluarMatriz('O');
    }

    if (esMaximizador) {
        int mejorValor = INT_MIN;
        Nodo* hijo = hijosIzquierda;

        while (hijo != nullptr) {
            mejorValor = std::max(mejorValor, hijo->minimax(profundidad - 1, alfa, beta));
            alfa = std::max(alfa, mejorValor);

            if (beta <= alfa) {
                break;  // Poda alfa-beta
            }

            hijo = hijo->hijosDerecha;
        }

        return mejorValor;
    } else {
        int mejorValor = INT_MAX;
        Nodo* hijo = hijosIzquierda;

        while (hijo != nullptr) {
            mejorValor = std::min(mejorValor, hijo->minimax(profundidad - 1, alfa, beta));
            beta = std::min(beta, mejorValor);

            if (beta <= alfa) {
                break;  // Poda alfa-beta
            }

            hijo = hijo->hijosDerecha;
        }

        return mejorValor;
    }
}

void Nodo::imprimirMatriz() {
    cout << "Estado actual del tablero:" << endl;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            cout << matriz[i][j] << " ";
        }
        cout << std::endl;
    }
    cout << "-----------------" << endl;
}
bool Nodo::realizarJugadaHumano(int columnaJugada) {
    char ficha = (esMaximizador) ? 'O' : 'X';

    // Encuentra la fila disponible para la ficha en la columna
    int fila = 5;
    while (fila >= 0 && matriz[fila][columnaJugada] != ' ') {
        --fila;
    }

    if (fila >= 0) {
        matriz[fila][columnaJugada] = ficha;
        return true;  // Jugada válida realizada
    } else {
        std::cout << "Columna llena. Realiza una jugada válida." << std::endl;
        return false;  // Jugada no válida
    }
}