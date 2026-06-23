
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
4 5
1 2 10
1 3 4
4 1 7
3 2 5
2 4 5
1 1
1 2


Salida de ejemplo
3 1


*/

template <typename Valor>
class DijkstraMultiple {
  public:
    DijkstraMultiple(DigrafoValorado<Valor> const& g, vector<int> orig) : dist(g.V(), INF),
                                                                          pq(g.V()) {
        for (int i = 0; i < orig.size(); i++) {
            dist[orig[i]] = 0;
            pq.push(orig[i], 0);
        }
        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    Valor distancia(int v) const {
        return dist[v];
    }

  private:
    const Valor INF = std::numeric_limits<Valor>::max();
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
    int V, A;
    cin >> V >> A;

    if (!std::cin)  // fin de la entrada
        return false;

    DigrafoValorado<int> g(V);
    int v, w, coste;
    for (int i = 0; i < A; i++) {
        cin >> v >> w >> coste;
        g.ponArista({v - 1, w - 1, coste});
        g.ponArista({w - 1, v - 1, coste});
    }

    int G, R, aux;
    vector<bool> neutral(V, true);

    cin >> G;
    vector<int> galos(G);
    for (int i = 0; i < G; i++) {
        cin >> aux;
        galos[i] = aux - 1;
        neutral[aux - 1] = false;
    }

    cin >> R;
    vector<int> romanos(R);
    for (int i = 0; i < R; i++) {
        cin >> aux;
        romanos[i] = aux - 1;
        neutral[aux - 1] = false;
    }

    // resolver el caso posiblemente llamando a otras funciones

    DijkstraMultiple<int> dksGalos(g, galos);
    DijkstraMultiple<int> dksRomanos(g, romanos);

    int pueblo, distancia = 10000;
    for (int i = 0; i < V; i++) {
        if (neutral[i] && abs(dksGalos.distancia(i) - dksRomanos.distancia(i)) < distancia) {
            pueblo = i;
            distancia = abs(dksGalos.distancia(i) - dksRomanos.distancia(i));
        }
    }

    cout << pueblo + 1 << " " << distancia << "\n";
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
