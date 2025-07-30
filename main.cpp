#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int FILAS = 5;
const int COLUMNAS = 5;
const int MINAS = 5;

void inicializarTablero(char tablero[FILAS][COLUMNAS], char valor) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            tablero[i][j] = valor;
        }
    }
}

void colocarMinas(char tablero[FILAS][COLUMNAS]) {
    int minasColocadas = 0;
    while (minasColocadas < MINAS) {
        int fila = rand() % FILAS;
        int columna = rand() % COLUMNAS;
        if (tablero[fila][columna] != '*') {
            tablero[fila][columna] = '*';
            minasColocadas++;
        }
    }
}

int contarMinasCercanas(char tablero[FILAS][COLUMNAS], int fila, int columna) {
    int contador = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int nuevaFila = fila + i;
            int nuevaColumna = columna + j;
            if (nuevaFila >= 0 && nuevaFila < FILAS && nuevaColumna >= 0 && nuevaColumna < COLUMNAS) {
                if (tablero[nuevaFila][nuevaColumna] == '*') {
                    contador++;
                }
            }
        }
    }
    return contador;
}

void mostrarTablero(char tablero[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            cout << tablero[i][j] << " ";
        }
        cout << endl;
    }
}

bool esEntradaValida(int valor, int limite) {
    if (valor < 0 || valor >= limite) {
        return false;
    }
    return true;
}

int main() {
    char tablero[FILAS][COLUMNAS];
    char tableroVisible[FILAS][COLUMNAS];
    int fila, columna;

    srand(time(NULL));

    inicializarTablero(tablero, '0');
    inicializarTablero(tableroVisible, '#');
    colocarMinas(tablero);

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j] != '*') {
                tablero[i][j] = '0' + contarMinasCercanas(tablero, i, j);
            }
        }
    }

    cout << "Bienvenido al buscaminas!" << endl;
    cout << "Descubre las casillas sin explotar." << endl;

    while (true) {
        mostrarTablero(tableroVisible);
        cout << "Introduce la fila y columna (0-" << FILAS - 1 << "): ";
        cin >> fila >> columna;

        // Validar entrada del usuario
        if (!esEntradaValida(fila, FILAS) || !esEntradaValida(columna, COLUMNAS)) {
            cout << "Posicion invalida. Intenta nuevamente." << endl;
            continue;
        }

        if (tablero[fila][columna] == '*') {
            cout << "Boom! Pisaste una mina. Fin del juego." << endl;
            mostrarTablero(tablero);
            break;
        } else {
            tableroVisible[fila][columna] = tablero[fila][columna];
        }

        int descubiertas = 0;
        for (int i = 0; i < FILAS; i++) {
            for (int j = 0; j < COLUMNAS; j++) {
                if (tableroVisible[i][j] != '#' && tablero[i][j] != '*') {
                    descubiertas++;
                }
            }
        }

        if (descubiertas == FILAS * COLUMNAS - MINAS) {
            cout << "Ganastes! Descubriste todas las casillas sin minas." << endl;
            mostrarTablero(tablero);
            break;
        }
    }

    return 0;
}
