#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int FILAS = 5;
const int COLUMNAS = 5;
const int MINAS = 5;

void inicializarTablero(char tablero[FILAS][COLUMNAS], char valor) {
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            tablero[i][j] = valor;
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

int contarMinasCerca(char minas[FILAS][COLUMNAS], int x, int y) {
    int cuenta = 0;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i >= 0 && i < FILAS && j >= 0 && j < COLUMNAS) {
                if (minas[i][j] == '*' && !(i == x && j == y))
                    cuenta++;
            }
        }
    }
    return cuenta;
}

void mostrarTablero(char tablero[FILAS][COLUMNAS]) {
    cout << "   ";
    for (int i = 0; i < COLUMNAS; i++)
        cout << i << " ";
    cout << endl;
    for (int i = 0; i < FILAS; i++) {
        cout << i << " |";
        for (int j = 0; j < COLUMNAS; j++)
            cout << tablero[i][j] << "|";
        cout << endl;
    }
}

int main() {
    srand(time(0));
    char tablero[FILAS][COLUMNAS];
    char minas[FILAS][COLUMNAS];
    bool juego = true;
    int descubiertas = 0;
    int totalCasillas = FILAS * COLUMNAS - MINAS;

    inicializarTablero(tablero, '-');
    inicializarTablero(minas, '-');
    colocarMinas(minas);

    while (juego) {
        mostrarTablero(tablero);
        int x, y;
        cout << "Introduce fila y columna (ejemplo: 1 2): ";
        cin >> x >> y;

        if (x < 0 || x >= FILAS || y < 0 || y >= COLUMNAS) {
            cout << "Posicion fuera de rango. Intenta de nuevo.\n";
            continue;
        }
        if (tablero[x][y] != '-') {
            cout << "Ya descubriste esa casilla.\n";
            continue;
        }
        if (minas[x][y] == '*') {
            cout << "GAME OVER! Pisaste una mina.\n";
            mostrarTablero(minas);
            juego = false;
            break;
        } else {
            int minasCerca = contarMinasCerca(minas, x, y);
            tablero[x][y] = minasCerca + '0';
            descubiertas++;
            if (descubiertas == totalCasillas) {
                cout << "¡Felicidades! Descubriste todas las casillas sin pisar minas.\n";
                mostrarTablero(minas);
                break;
            }
        }
    }
    return 0;
}