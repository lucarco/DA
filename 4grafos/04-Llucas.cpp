
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

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
class CaminoMasCorto {
  public:
    CaminoMasCorto(Grafo const& g, int ini1, int ini2, int fin) : visit(g.V(), false),
                                                                  distIni1(g.V()),
                                                                  distIni2(g.V()),
                                                                  distFin(g.V()),
                                                                  min(g.V()) {
        s = ini1;
        bfs(g, distIni1, false);
        fill(visit.begin(), visit.end(), false);
        s = ini2;
        bfs(g, distIni2, false);
        fill(visit.begin(), visit.end(), false);
        s = fin;
        bfs(g, distFin, true);
    }

    int getMin() {
        return min;
    }

  private:
    std::vector<bool> visit;    // visit[v] = ¿hay camino de s a v?
    std::vector<int> distIni1;  // dist[v] = aristas en el camino ini1-v más corto
    std::vector<int> distIni2;  // dist[v] = aristas en el camino ini2-v más corto
    std::vector<int> distFin;   // dist[v] = aristas en el camino fin-v más corto
    int min;                    // la solucion
    int s;

    void bfs(Grafo const& g, vector<int>& dist, bool buscarMin) {
        std::queue<int> q;
        dist[s] = 0;
        if (buscarMin) {
            min = std::min(min, (distIni1[s] + distIni2[s] + dist[s]));
        }
        visit[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int w : g.ady(v)) {
                if (!visit[w]) {
                    dist[w] = dist[v] + 1;
                    visit[w] = true;
                    q.push(w);
                    if (buscarMin) {
                        min = std::min(min, (distIni1[w] + distIni2[w] + dist[w]));
                    }
                }
            }
        }
    }
};
bool resuelveCaso() {
    // leer los datos de la entrada
    int V, A, ini1, ini2, fin;
    cin >> V >> A >> ini1 >> ini2 >> fin;
    if (!std::cin) {
        // fin de la entrada
        return false;
    }

    Grafo g(V);

    for (int i = 0; i < A; i++) {
        int u, w;
        cin >> u >> w;
        g.ponArista(u - 1, w - 1);
    }
    // resolver el caso posiblemente llamando a otras funciones
    CaminoMasCorto cmc(g, ini1 - 1, ini2 - 1, fin - 1);
    // escribir la solución
    cout << cmc.getMin() << "\n";

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
