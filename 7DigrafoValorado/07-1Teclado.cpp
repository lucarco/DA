
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <fstream>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"

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
4
10 5 15 8
5
1 2 10
1 3 20
1 4 100
2 4 20
3 4 20
4
10 5 15 8
4
1 2 10
1 3 20
2 3 40
4 2 10
0

Salida de ejemplo
53
IMPOSIBLE


*/

template <typename Valor>
class Dijkstra {
  public:
    Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig),
                                                          dist(g.V(), INF),
                                                          pq(g.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }
    bool hayCamino(int v) const {
        return dist[v] != INF;
    }
    Valor distancia(int v) const {
        return dist[v];
    }

  private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    std::vector<Valor> dist;
    IndexPQ<Valor> pq;

    void relajar(AristaDirigida<Valor> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
        }
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int V;
    cin >> V;

    if (V == 0)
        return false;

    vector<int> carga(V);
    for (int i = 0; i < V; i++) {
        cin >> carga[i];
    }

    DigrafoValorado<int> g(V);
    int A, v, w, coste;
    cin >> A;

    for (int i = 0; i < A; i++) {
        cin >> v >> w >> coste;
        g.ponArista({v - 1, w - 1, coste + carga[w - 1]});
    }

    Dijkstra<int> dj(g, 0);
    if (dj.hayCamino(V - 1)) {
        cout << dj.distancia(V - 1) + carga[0] << "\n";
    } else {
        cout << "IMPOSIBLE\n";
    }

    // resolver el caso posiblemente llamando a otras funciones

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
