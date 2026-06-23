
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <fstream>
#include <iostream>
using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase

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
5
5
1 2 10
1 3 30
2 4 20
3 4 15
4 5 12
3
1 5 8
1 4 12
2 5 15


SALIDA
SI
SI
NO

*/

class verSiLLega {
  private:
    vector<bool> visit;
    int ancho;
    int ini, fin;

    // visita los nodos alcanzables desde v respetando el umbral
    void dfs(GrafoValorado<int> const& G, int v, int umbral) {
        if (!visit[fin]) {
            visit[v] = true;
            for (auto a : G.ady(v)) {
                if (a.valor() >= umbral) {
                    int w = a.otro(v);
                    if (!visit[w])
                        dfs(G, w, ancho);
                }
            }
        }
    }

  public:
    verSiLLega(GrafoValorado<int> g, int camion, int ini, int fin) : visit(g.V(), false), ini(ini), fin(fin) {
        ancho = camion;
        dfs(g, ini, ancho);
    }

    bool getVisit(int v) {
        return visit[v];
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int V, A;
    cin >> V >> A;
    GrafoValorado<int> g(V);

    for (int i = 0; i < A; i++) {
        int u, w, valor;
        cin >> u >> w >> valor;
        Arista<int> a(u - 1, w - 1, valor);
        g.ponArista(a);
    }

    if (!std::cin) {
        return false;
    }

    // resolver el caso posiblemente llamando a otras funciones
    int K;
    cin >> K;

    for (int i = 0; i < K; i++) {
        int ini, fin, ancho;
        cin >> ini >> fin >> ancho;
        verSiLLega vsl(g, ancho, ini - 1, fin - 1);
        if (vsl.getVisit(fin - 1)) {
            cout << "SI\n";
        } else {
            cout << "NO\n";
        }
    }
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
