
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#include "Matriz.h"

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
4
8 7 1 4
4
2 4 15 5
7
6 11 3 15 9 4 12
0


SALIDA
12
17
35



*/

int maxGanancia(vector<int>& cubos, int i, int j, Matriz<int>& matriz) {
    if (j != cubos.size() || i != 1) {
        if (cubos[i - 1] > cubos[j - 1]) {
            i++;
        } else {
            j--;
        }
    }
    if (i <= j) {
        if (matriz[i][j] != -1) {
            return matriz[i][j];
        }
        if (i == j) {
            matriz[i][j] = cubos[i - 1];
            return matriz[i][j];
        } else {
            return matriz[i][j] = max(cubos[i - 1] + maxGanancia(cubos, i + 1, j, matriz), cubos[j - 1] + maxGanancia(cubos, i, j - 1, matriz));
        }
    }
    return 0;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int C;
    cin >> C;

    if (C == 0) {
        return false;
    }

    vector<int> cubos(C);
    for (int i = 0; i < C; i++) {
        cin >> cubos[i];
    }

    // resolver el caso posiblemente llamando a otras funciones
    Matriz<int> matriz(C + 1, C + 1, -1);
    cout << maxGanancia(cubos, 1, C, matriz) << "\n";

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
