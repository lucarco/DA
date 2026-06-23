
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <fstream>
#include <iostream>

using namespace std;

#include "EnterosInf.h"
#include "Matriz.h"  // propios o los de las estructuras de datos de clase
/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>
/*
ENTRADA
4 5
.....
.X...
..X.X
.....
3 5
.X...
...X.
XXX..



SALIDA
4
0


*/
struct tMov {
    int fila;
    int col;
};

void caminoMinManeras(int filas, int cols, Matriz<char>& ciudad) {
    Matriz<EntInf> matriz(filas, cols, 0);
    matriz[0][0] = 1;

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == 0 && j == 0) {
            } else if (ciudad[i][j] == 'X') {
                matriz[i][j] = 0;
            } else {
                EntInf desdeArriba = 0;
                EntInf desdeIzq = 0;

                if (i > 0 && ciudad[i - 1][j] != 'X') {
                    desdeArriba = matriz[i - 1][j];
                }
                if (j > 0 && ciudad[i][j - 1] != 'X') {
                    desdeIzq = matriz[i][j - 1];
                }
                matriz[i][j] = desdeArriba + desdeIzq;
            }
        }
    }

    cout << matriz[filas - 1][cols - 1] << "\n";
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int filas, cols;
    cin >> filas >> cols;

    Matriz<char> ciudad(filas, cols);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            char aux;
            cin >> aux;
            ciudad[i][j] = aux;
        }
    }

    if (!std::cin) {
        return false;
    }

    // resolver el caso posiblemente llamando a otras funciones
    caminoMinManeras(filas, cols, ciudad);
    // escribir la solución

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
