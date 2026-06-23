
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */
#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>

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
7
7
1 2
2 3
1 4
4 5
5 6
4 6
6 7
4
4 2
4 3
7 3
1 0
6
5
1 3
3 5
5 1
2 4
2 6
2
1 2
2 1


SALIDA
1
0
2
6
---
3
3
---

*/

class CaminoMasCorto {
  public:
    CaminoMasCorto(Grafo const& g, int s, int TTL)
        : visit(g.V(), false),
          dist(g.V()),
          s(s),
          TTL(TTL) {
        bfs(g);
    }

    int sol() const {
        int cont = 0;
        for (int v = 0; v < visit.size(); v++) {
            if (!visit[v] || dist[v] > TTL) {
                cont++;
            }
        }
        return cont;
    }

  private:
    vector<bool> visit;
    vector<int> dist;
    int s;
    int TTL;

    void bfs(Grafo const& g) {
        queue<int> q;
        dist[s] = 0;
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
                }
            }
        }
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int V, A;
    cin >> V >> A;

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

    int k;
    cin >> k;
    // unordered_map<int, vector<int>> sol;
    for (int i = 0; i < k; i++) {
        int s, TTL;
        cin >> s >> TTL;
        CaminoMasCorto c(g, s - 1, TTL);
        cout << c.sol();
        cout << "\n";
    }

    cout << "---\n";

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
