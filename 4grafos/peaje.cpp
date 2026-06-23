
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

// #include <...>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

#include "Grafos.h"  // propios o los de las estructuras de datos de clase

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
6 7 1 3 6
1 2
2 3
2 5
3 4
5 4
5 6
4 6
4 3 4 1 3
1 2
2 3
3 4


SALIDA
4
3

*/

class caminoBFS {
  private:
    std::vector<bool> visit;  // visit[v] = ¿hay camino de s a v?
    std::vector<int> dist;    // dist[v] = aristas en el camino s-v más corto
    int s;

    void bfs(Grafo const& g) {
        queue<int> q;
        q.push(s);

        visit[s] = true;
        dist[s] = true;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int w : g.ady(v)) {
                if (!visit[w]) {
                    q.push(w);
                    visit[w] = true;
                    cout << "La distancia de " << w << "es " << dist[v] + 1 << "\n";
                    dist[w] = dist[v] + 1;
                }
            }
        }
    }

  public:
    caminoBFS(const Grafo& g, int s) : s(s), visit(g.V(), false), dist(g.V(), 0) {
        bfs(g);
    }

    int getDist(int v) {
        return dist[v];
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int V, A, casaA, casaL, trabajo;
    cin >> V >> A >> casaA >> casaL >> trabajo;

    if (!std::cin)  // fin de la entrada
        return false;

    Grafo g(V);

    for (int i = 0; i < A; i++) {
        int a, b;
        cin >> a >> b;
        g.ponArista(a - 1, b - 1);
    }
    // resolver el caso posiblemente llamando a otras funciones
    int sol = 10000;
    for (int i = 0; i < V; i++) {
        cout << "Probando la arista: " << i << "\n";
        caminoBFS bfs(g, i);
        int aux = bfs.getDist(casaA - 1) + bfs.getDist(casaL - 1) + bfs.getDist(trabajo - 1);
        sol = min(aux, sol);
    }
    // escribir la solución
    cout << sol << "\n";

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
