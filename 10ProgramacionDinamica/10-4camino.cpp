
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

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
4
2 5 8 3
1 4 2 9
9 2 8 5
3 5 2 1
3
1 1 1
1 1 1
1 1 1

SALIDA
30 2
3 1

*/

struct tSol {
    int valor_max;
    int col;
};

void caminoMax(int N, Matriz<int>& matriz) {
    tSol sol = {-1, -1};

    for (int i = 1; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j == 0) {
                matriz[i][j] += max(matriz[i - 1][j], matriz[i - 1][j + 1]);
            }
            else if (j == N - 1) {
                matriz[i][j] += max(matriz[i - 1][j], matriz[i - 1][j - 1]);
            } else {
                matriz[i][j] += max(max(matriz[i - 1][j], matriz[i - 1][j - 1]), matriz[i - 1][j + 1]);
            }
            if (i == N - 1 && (sol.col == -1 || sol.valor_max < matriz[i][j])) {
                sol = {matriz[i][j], j};
            }
        }
    }

    cout << sol.valor_max << " " << sol.col + 1 << "\n";
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N;
    cin >> N;
    Matriz<int> matriz(N, N, 0);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> matriz[i][j];
        }
    }

    if (!std::cin) {
        return false;
    }

    // resolver el caso posiblemente llamando a otras funciones

    // escribir la solución
    caminoMax(N, matriz);

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
