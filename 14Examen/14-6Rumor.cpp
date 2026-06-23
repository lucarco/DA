
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
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

Entrada de ejemplo
5 2
8 5 3 2 4
1 4
4 5
10 5
1 6 2 7 3 8 4 9 5 10
1 2
3 4
5 6
7 8
9 10

Salida de ejemplo
10
15


*/

class CaminoMasCorto {
  public:
    CaminoMasCorto(Grafo const& g, vector<int> const& sobornos) : visit(g.V(), false),
                                                                  s(0),
                                                                  coste(0) {
        for (int i = 0; i < g.V(); i++) {
            if (!visit[i]) {
                s = i;
                coste += bfs(g, sobornos);
            }
        }
    }

    int getCoste() {
        return coste;
    }

  private:
    std::vector<bool> visit;  // visit[v] = ¿hay camino de s a v?
    int s;
    int coste;

    int bfs(Grafo const& g, vector<int> const& sobornos) {
        int min_monedas = sobornos[s];
        std::queue<int> q;
        visit[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int w : g.ady(v)) {
                if (!visit[w]) {
                    visit[w] = true;
                    q.push(w);
                    min_monedas = min(min_monedas, sobornos[w]);
                }
            }
        }
        return min_monedas;
    }
};
bool resuelveCaso() {
    // leer los datos de la entrada

    int V, A;
    cin >> V >> A;

    if (!std::cin)  // fin de la entrada
        return false;

    // resolver el caso posiblemente llamando a otras funciones

    vector<int> costes(V);
    for (int i = 0; i < V; i++) {
        cin >> costes[i];
    }

    Grafo g(V);
    int v, w;
    for (int i = 0; i < A; i++) {
        cin >> v >> w;
        g.ponArista(v - 1, w - 1);
    }
    // escribir la solución
    CaminoMasCorto sol(g, costes);

    cout << sol.getCoste() << "\n";

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
