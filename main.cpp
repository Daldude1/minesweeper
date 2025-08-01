#include <iostream> // entrada y salida de datos
#include <cstdlib>  // funciones como rand() y srand()

using namespace std;

// se definen constantes para el tamaño del tablero y el número de minas
const int FILAS = 5;     // número de filas del tablero.
const int COLUMNAS = 5;  // número de columnas del tablero.
const int MINAS = 5;     // número total de minas en el tablero.

// función para inicializar el tablero con un valor inicial como '0' o '#'
void inicializarTablero(char tablero[FILAS][COLUMNAS], char valorInicial) {
    for (int i = 0; i < FILAS; i++) {         // recorremos todas las filas
        for (int j = 0; j < COLUMNAS; j++) { // recorremos todas las columnas
            tablero[i][j] = valorInicial;    //aasignamos el valor inicial a cada celda
        }
    }
}

// función para colocar minas en posiciones aleatorias usando una semilla manual
void colocarMinas(char tablero[FILAS][COLUMNAS]) {
    srand(0); // esto no se bien como es pero ponle que es para habilitar el random del programa.
    // sin el srand el programa no genera numeros aleatorios y sin la semilla tmp

    int minasColocadas = 0; // contador de minas colocadas
    // el while va sumando la cantidad segun las minas que se hayan puesto en el tablero

    while (minasColocadas < MINAS) { // se genera colocando minas hasta alcanzar la cantidad deseada
        int fila = rand() % FILAS; // generamos una fila aleatoria
        int columna = rand() % COLUMNAS; // generamos una columna aleatoria

        if (tablero[fila][columna] != 'M') { // si la celda no tiene ya una mina tonses
            // el if verifica que no haya una bomba antes en esa celda
            tablero[fila][columna] = 'M'; // colocamos una mina ('M') en esa celda
            // y el tablero[fila][columna] pone la mina en esa celda (la mina se represnta
            // con M

            minasColocadas++; // incrementamos el contador de minas colocadas
        }
    }
}

// función para contar cuántas minas hay alrededor de una casilla
int contarMinasCercanas(char tablero[FILAS][COLUMNAS], int fila, int columna) {
    // Para hacerlo mas facil de entender y leer
    // Lo que hace esta funcion es revisar las minas (las 8), las obtiene y les suma un 1
    // lo que modifica el valor original de la casilla, los fors lo que hacen es obtenerlo
    // recorriendo cada casilla, va desde la fila de arriba hasta la de abajo, luego
    // de la columna izquierda hasta la derecha y luego las diagonales, con eso
    // obtiene todo
    // pd el contador aumenta pero solo para un numero)

    int minasCercanas = 0; // contador para las minas cercanas.

    // se recorren las casillas vecinas (incluyendo diagonales)
    for (int i = -1; i <= 1; i++) { // Fila vecina: desde una fila arriba hasta una fila abajo
        for (int j = -1; j <= 1; j++) { // Columna vecina: desde una columna izquierda hasta una columna derecha
            int nuevaFila = fila + i; // Calculamos la fila vecina
            int nuevaColumna = columna + j; // Calculamos la columna vecina

            // Verificamos si la casilla vecina está dentro del tablero y si tiene una mina
            if (nuevaFila >= 0 && nuevaFila < FILAS && nuevaColumna >= 0 && nuevaColumna < COLUMNAS &&
                tablero[nuevaFila][nuevaColumna] == 'M') {
                minasCercanas++; // Incrementamos el contador si encontramos una mina
            }
        }
    }

    return minasCercanas; // Retornamos el número total de minas cercanas
}

// función para mostrar el tablero en la consola
void mostrarTablero(char tablero[FILAS][COLUMNAS]) {
    cout << "  "; // espacio inicial para alinear las columnas.
    for (int i = 0; i < COLUMNAS; i++) { // e imprime los números de las columnas como encabezado
        cout << i << " ";
    }
    cout << endl;

    // esto fue lo que te dije en clases de como generar el tablero y tal)

    for (int i = 0; i < FILAS; i++) { // Recorremos todas las filas.
        cout << i << " "; // Mostramos el número de la fila.
        for (int j = 0; j < COLUMNAS; j++) { // Recorremos las columnas de la fila actual.
            cout << tablero[i][j] << " "; // Mostramos el contenido de la celda.
        }
        cout << endl; // Nueva línea después de cada fila.
    }
}

// función principal del juego.
void jugar() {
    char tablero[FILAS][COLUMNAS];         // tablero real que contiene minas y números.
    char tableroVisible[FILAS][COLUMNAS]; // tablero visible para el jugador.
    bool juegoTerminado = false;          // variable para saber si el juego terminó.

    inicializarTablero(tablero, '0');         // inicializamos el tablero real con ceros.
    inicializarTablero(tableroVisible, '#'); // inicializamos el tablero visible con '#'.
    colocarMinas(tablero);                   // colocamos las minas en el tablero real.

    while (!juegoTerminado) { // continuamos el juego hasta que el jugador gane o pierda.
        mostrarTablero(tableroVisible); // mostramos el tablero visible al jugador.

        int fila, columna; // variables para las coordenadas.
        cout << "Ingrese la fila y columna para descubrir (e.g., 0 1): ";
        cin >> fila >> columna; // leemos las coordenadas del jugador.

        // verificar que las coordenadas sean válidas.
        if (fila < 0 || fila >= FILAS || columna < 0 || columna >= COLUMNAS) {
            cout << "Ingrese una fila y columna validas." << endl;
            continue; // pedir nuevas coordenadas si son inválidas.
        }

        if (tablero[fila][columna] == 'M') { // Si el jugador pisa una mina tebtibnces
            cout << "¡BOOM! Pisaste una mina :(" << endl;
            juegoTerminado = true; // mrrcamos el juego como terminado.
        } else {
            int minasCercanas = contarMinasCercanas(tablero, fila, columna); // Ccaulamos minas cercanas.
            tableroVisible[fila][columna] = minasCercanas + '0'; // mostramos el número de minas cercanas.

            // verificamos si el jugador ha ganado.
            bool victoria = true;
            for (int i = 0; i < FILAS; i++) { // recorremos todas las filas.
                for (int j = 0; j < COLUMNAS; j++) { // recorremos todas las columnas.
                    if (tableroVisible[i][j] == '#' && tablero[i][j] != 'M') {
                        victoria = false; // si queda alguna casilla sin descubrir, aún no ha ganado.
                    }
                }
            }

            // el for de arriba ayuda a comprobhar si ya se han visualziado todas las casillas
            // osea si ya se han seleccionado, recorre todas las filas y todas las columnas
            // en busqueda de alguna casilla sin descubrir (si hay alguna entonces no ha ganao)

            if (victoria) { // si el jugador ha descubierto todas las casillas sin minas entonces
                cout << "Ganaste el juego! Descubrist e todas las casillas" << endl;
                juegoTerminado = true; // terminar el juego
            }
        }
    }

    cout << "tablero final:" << endl;
    mostrarTablero(tablero); // este es el tablero con todo desbloqueado
}

// fnción principal del programa.
int main() {
    cout << "Bienvenido al Buscaminas!\n";
    jugar();
    return 0; 
}
