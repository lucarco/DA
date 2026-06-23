
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <deque>
#include <fstream>
#include <iostream>
using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase
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
5 6
1 2
2 3
3 2
3 4
4 3
2 5
3
1 4
1 5
5 1


SALIDA
2
3
IMPOSIBLE
---

*/

class CaminosDFS {
  private:
    std::vector<bool> visit;  // visit[v] = ¿hay camino de s a v?
    std::vector<int> ant;     // ant[v] = último vértice antes de llegar a v
    int s;                    // vértice origen
    void dfs(Digrafo const& G, int v) {
        visit[v] = true;
        for (int w : G.ady(v)) {
            if (!visit[w]) {
                ant[w] = v;
                dfs(G, w);
            }
        }
    }

  public:
    CaminosDFS(Digrafo const& g, int s) : visit(g.V(), false),
                                          ant(g.V()),
                                          s(s) {
        dfs(g, s);
    }
    // ¿hay camino del origen a v?
    bool hayCamino(int v) const {
        return visit[v];
    }
    using Camino = std::deque<int>;  // para representar caminos
    // devuelve un camino desde el origen a v (debe existir)
    Camino camino(int v) const {
        if (!hayCamino(v))
            throw std::domain_error("No existe camino");
        Camino cam;
        // recuperamos el camino retrocediendo
        for (int x = v; x != s; x = ant[x])
            cam.push_front(x);
        cam.push_front(s);
        return cam;
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int V, A, Q;
    cin >> V >> A;

    if (!std::cin) {  // fin de la entrada
        return false;
    }

    Digrafo gIni(V);
    Digrafo gFin(V);
    int v, w;
    for (int i = 0; i < A; i++) {
        cin >> v >> w;
        gIni.ponArista(v - 1, w - 1);
        gFin.ponArista(w - 1, v - 1);
    }

    cin >> Q;
    int origen, destino, cont;
    for (int i = 0; i < Q; i++) {
        cin >> origen >> destino;
        origen--;
        destino--;
        CaminosDFS dfs1(gIni, origen);
        CaminosDFS dfs2(gFin, destino);
        cont = 0;
        for (int j = 0; j < V; j++) {
            if (j != origen && j != destino && dfs1.hayCamino(j) && dfs2.hayCamino(j)) {
                cont++;
            }
        }
        if (cont == 0) {
            cout << "IMPOSIBLE\n";
        } else {
            cout << cont << "\n";
        }
    }

    cout << "---\n";

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
