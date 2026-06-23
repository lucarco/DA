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

#include "DigrafoValorado.h"
#include "IndexPQ.h"

/*@ <answer>

 El problema pide encontrar un camino entre origen y destino tal que la arista de mayor peso en dicho camino sea mínima (problema Minimax o Bottleneck Path).

 Se resuelve utilizando una variación del algoritmo de Dijkstra.
 - Vector dist[v]: guarda la capacidad pulmonar mínima necesaria para llegar desde el origen hasta v.
 - Inicialización: dist[origen] = 0, resto Infinito.
 - Relajación: Al ir de v a w con una arista de peso P, el coste para llegar a w es max(dist[v], P).
   Si este valor es menor que dist[w], actualizamos.

 Coste: O(A log V) igual que Dijkstra, donde A es nº aristas y V nº vértices.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

template <typename Valor>
class DijkstraMinimax {
  public:
    DijkstraMinimax(DigrafoValorado<Valor> const& g, int orig) : dist(g.V(), INF), pq(g.V()) {
        dist[orig] = 0;
        pq.push(orig, 0);

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
    std::vector<Valor> dist;
    IndexPQ<Valor> pq;

    void relajar(AristaDirigida<Valor> a) {
        int v = a.desde();
        int w = a.hasta();

        // CORRECCIÓN CLAVE:
        // El coste de llegar a w es el MÁXIMO entre lo que costó llegar a v y la nueva arista.
        Valor costeRutaPorV = std::max(dist[v], a.valor());

        // Si ese máximo es mejor (menor) que lo que teníamos para w, actualizamos.
        if (dist[w] > costeRutaPorV) {
            dist[w] = costeRutaPorV;
            pq.update(w, dist[w]);
        }
    }
};

bool resuelveCaso() {
    int V, A;
    cin >> V >> A;

    if (!std::cin) return false;

    // Usamos DigrafoValorado aunque sea no dirigido poniendo aristas en ambos sentidos
    DigrafoValorado<int> g(V);

    int v, w, coste;
    for (int i = 0; i < A; i++) {
        cin >> v >> w >> coste;
        // El grafo es NO dirigido (se puede ir y volver por la galería)
        g.ponArista({v - 1, w - 1, coste});
        g.ponArista({w - 1, v - 1, coste});
    }

    int origen, destino;
    cin >> origen >> destino;

    DijkstraMinimax<int> dj(g, origen - 1);

    if (dj.hayCamino(destino - 1)) {
        cout << dj.distancia(destino - 1) << "\n";
    } else {
        cout << "IMPOSIBLE\n";
    }

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}