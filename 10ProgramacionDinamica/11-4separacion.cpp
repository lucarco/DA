
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
using namespace std;

#include "EnterosInf.h"
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
4 4
Marta Mario
Mario Roberto
Roberto Raquel
Mario Raquel
4 2
Roberto Mario
Marta Raquel
1 1
Lucas Lucas
2 2
Mar Lucas
Lucas Lucas

SALIDA
2
DESCONECTADA
0
1

*/

void Floyd(Matriz<EntInf> const& G, Matriz<EntInf>& C, Matriz<int>& A) {
    int V = G.numfils();  // número de vértices de G
    // inicialización
    C = G;
    A = Matriz<int>(V, V, -1);
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i != j && G[i][j] != Infinito) A[i][j] = i;
        }
    }
    // actualizaciones de las matrices
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                auto temp = C[i][k] + C[k][j];
                if (temp < C[i][j]) {  // es mejor pasar por k
                    C[i][j] = temp;
                    A[i][j] = A[k][j];
                }
            }
        }
    }
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int P, R;
    cin >> P >> R;

    if (!std::cin) {
        return false;
    }
    Matriz<EntInf> grafo(P, P, Infinito);
    for (int i = 0; i < P; ++i) {
        grafo[i][i] = 0;
    }
    unordered_map<string, int> mapa;  // <nombre, indice_grafo>
    int idx = 0;

    for (int i = 0; i < R; i++) {
        string a, b;
        cin >> a >> b;

        if (!mapa.count(a)) {  // insertar a en el mapa ya que no existe
            mapa[a] = idx++;
        }
        if (!mapa.count(b)) {
            mapa[b] = idx++;
        }
        grafo[mapa[a]][mapa[b]] = 1;
        grafo[mapa[b]][mapa[a]] = 1;

        if (a == b) {  // caso en el que hagas relacion contigo mismo pq eres lerdo
            grafo[mapa[a]][mapa[b]] = 0;
        }
    }

    if (!std::cin) {
        return false;
    }
    // resolver el caso posiblemente llamando a otras funciones

    Matriz<EntInf> C;
    Matriz<int> S;

    Floyd(grafo, C, S);

    EntInf max = 0;
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < P; j++) {
            max = std::max(max, C[i][j]);
        }
    }

    // escribir la solución

    if (max == Infinito) {
        cout << "DESCONECTADA\n";
    } else {
        cout << max << "\n";
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
