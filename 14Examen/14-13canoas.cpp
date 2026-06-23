
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <fstream>
#include <iostream>
using namespace std;

#include "EnterosInf.h"  // propios o los de las estructuras de datos de clase
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
Entrada de ejemplo
5
3 10 30 90
5 20 15
10 8
4

Salida de ejemplo
3 8 18 16
5 15 13
10 8
4

*/

void Floyd(Matriz<EntInf> const& G, Matriz<EntInf>& C) {
    int V = G.numfils();  // número de vértices de G
    // inicialización
    C = G;

    // actualizaciones de las matrices
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                auto temp = C[i][k] + C[k][j];
                if (temp < C[i][j]) {  // es mejor pasar por k
                    C[i][j] = temp;
                }
            }
        }
    }
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N;
    cin >> N;

    if (!std::cin)  // fin de la entrada
        return false;

    // resolver el caso posiblemente llamando a otras funciones

    Matriz<EntInf> G(N, N, Infinito);
    int aux;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            cin >> aux;
            G[i][j] = aux;
        }
    }

    Matriz<EntInf> C;

    Floyd(G, C);
    // escribir la solución
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            cout << C[i][j] << " ";
        }
        cout << "\n";
    }

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
