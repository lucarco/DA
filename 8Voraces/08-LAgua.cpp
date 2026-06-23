
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"
#include "PriorityQueue.h"

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
1 2 5
1 3 20
4 2 15
3 4 10
6 7
1 2 15
2 3 5
3 6 100
1 4 5
4 6 100
6 5 100
1 5 20

SALIDA
30
440


*/

struct tPueblo {
    int distN;
    int distS;
};

// Del que tiene mas diferencia al que menos
// el más negativo es que está mucho más cerca de distN
// osea que va desde el que tiene más diferencia a favor de distN al que tiene más diferencia
// a favor de distS
bool operator<(tPueblo const& a, tPueblo const& b) {
    return (a.distN - a.distS) < (b.distN - b.distS);
}

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
    int V, A;
    cin >> V >> A;

    DigrafoValorado<int> g(V);
    for (int i = 0; i < A; i++) {
        int u, v, valor;
        cin >> u >> v >> valor;
        g.ponArista({u - 1, v - 1, valor});
        g.ponArista({v - 1, u - 1, valor});
    }

    if (!std::cin) {
        return false;
    }

    // resolver el caso posiblemente llamando a otras funciones
    Dijkstra<int> dN(g, 0);
    Dijkstra<int> dS(g, V - 1);

    PriorityQueue<tPueblo> pueblos;  // se ordena por (distN - distS) ascendente

    // SOLO pueblos (excluye nodos 0 y V-1)
    for (int i = 1; i < V - 1; i++) {
        pueblos.push({dN.distancia(i), dS.distancia(i)});
    }

    int sol = 0;
    int mitad = (V - 2) / 2;

    // Los mejores para el norte (los que tienen menor diferencia distN - distS)
    for (int i = 0; i < mitad; i++) {
        tPueblo aux = pueblos.top();
        pueblos.pop();
        sol += aux.distN;
    }

    // Los restantes, para el sur
    while (!pueblos.empty()) {
        tPueblo aux = pueblos.top();
        pueblos.pop();
        sol += aux.distS;
    }

    cout << sol * 2 << "\n";  // ida + vuelta

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
