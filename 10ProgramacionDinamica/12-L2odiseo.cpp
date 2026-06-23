/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <limits>
#include <algorithm>
#include<unordered_map>
using namespace std;

#include "Matriz.h"
#include "EnterosInf.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

const int INF = 1e9;

struct Atajo {
    int destino;
    int coste;
};

bool resuelveCaso() {
    int N, P, A;
    // N: Ciudades intermedias (sin contar Gadir), P: Presupuesto, A: Atajos
    if (!(cin >> N >> P >> A)) return false;

    // Tiempos de espera en cada ciudad (indices 1 a N)
    vector<int> tiempos(N + 1);
    for (int i = 1; i <= N; ++i) cin >> tiempos[i];

    // Lista de adyacencia para los atajos
    vector<vector<Atajo>> atajos(N + 1);
    for (int i = 0; i < A; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        atajos[u].push_back({ v, c });
    }

    // Tabla DP: dp[ciudad][coste_gastado] = tiempo_minimo
    // Ciudades de 1 a N+1 (Gadir)
    vector<vector<int>> dp(N + 2, vector<int>(P + 1, INF));

    // Caso base: Estamos en la ciudad 1, coste 0.
    // El tiempo inicial es el tiempo que tardamos en "salir" de la ciudad 1 (t_1)
    dp[1][0] = tiempos[1];

    // Recorremos las ciudades en orden topológico (1 a N)
    for (int u = 1; u <= N; ++u) {
        // Para cada nivel de gasto posible
        for (int coste = 0; coste <= P; ++coste) {

            // Si este estado no es alcanzable, saltamos
            if (dp[u][coste] == INF) continue;

            // 1. CAMINO NORMAL (u -> u+1)
            // Solo si no estamos ya en la última ciudad "visitable" antes de Gadir
            // Si u = N, u+1 es Gadir.
            int v_normal = u + 1;
            // El tiempo añadido es t[v_normal]. Si v_normal es Gadir (N+1), tiempo es 0.
            int tiempo_extra = (v_normal <= N) ? tiempos[v_normal] : 0;

            if (dp[v_normal][coste] > dp[u][coste] + tiempo_extra) {
                dp[v_normal][coste] = dp[u][coste] + tiempo_extra;
            }

            // 2. ATAJOS (u -> v con coste C)
            for (auto& atajo : atajos[u]) {
                int v = atajo.destino;
                int c = atajo.coste;

                if (coste + c <= P) { // Si tenemos presupuesto
                    // Si el destino es Gadir (N+1), no sumamos tiempo extra
                    int tiempo_atajo = (v <= N) ? tiempos[v] : 0;

                    if (dp[v][coste + c] > dp[u][coste] + tiempo_atajo) {
                        dp[v][coste + c] = dp[u][coste] + tiempo_atajo;
                    }
                }
            }
        }
    }

    // La respuesta es el mínimo tiempo para llegar a Gadir (N+1) con CUALQUIER coste <= P
    int min_tiempo = INF;
    for (int c = 0; c <= P; ++c) {
        min_tiempo = min(min_tiempo, dp[N + 1][c]);
    }

    cout << min_tiempo << endl;

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