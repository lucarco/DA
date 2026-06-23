
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
60 4
15 50
10 40
5 10
8 20
80 2
10 100
7 90
10 3
3 10
4 10
3 10


SALIDA
20
0
4

*/

struct tFesti {
    int grupos;
    int precio;
};

int maxGrupos(int N, int P, vector<tFesti>& festis) {
    Matriz<int> matriz(N + 1, P + 1, 0);
    vector<int> dinero_restante(P + 1, P);

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= P; j++) {
            if (festis[i - 1].precio > j) {
                matriz[i][j] = matriz[i - 1][j];
            } else {
                matriz[i][j] = max(matriz[i - 1][j - festis[i - 1].precio] + festis[i - 1].grupos, matriz[i - 1][j]);
            }
        }
    }

    return matriz[N][P];
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int P, N;
    cin >> P >> N;

    vector<tFesti> festis(N);

    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        festis[i] = {a, b};
    }

    if (!std::cin) {
        return false;
    }
    // resolver el caso posiblemente llamando a otras funciones
    cout << maxGrupos(N, P, festis) << "\n";
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
