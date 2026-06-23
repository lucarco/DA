
/*@ <answer>
 *
 * Nombre y Apellidos: Lucas Arranz
 *
 *@ </answer> */

#include <algorithm>
#include <fstream>
#include <iostream>
// #include <...>
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
2
3 2
1 2
2 3
10 10
1 2
3 1
3 4
5 4
3 5
4 6
5 2
7 10
9 10
8 9

SALIDA
3
6


*/

class mayorConexo {
    private:
        vector<bool> visitado;
        int max;
        int maxAct;

        void dfs(Grafo const& g, int v) {
            visitado[v] = true;
            maxAct++;
            max = std::max(max, maxAct);
            for (int ady : g.ady(v)) {
                if (!visitado[ady]) {
                    dfs(g, ady);
                }
            }
        }

    public:
        // Constructor:
        mayorConexo(Grafo g) {
            visitado.assign(g.V(), false);
            max = 0;
            maxAct = 0;

            for (int i = 0; i < g.V(); i++) {
                if (!visitado[i]) {
                    maxAct = 0;
                    dfs(g, i);
                    max = std::max(max, maxAct);
                }
            }
        }

        int getMax(){
            return max;
        }
};

void resuelveCaso() {
    // leer los datos de la entrada

    // resolver el caso posiblemente llamando a otras funciones
    int V, A;
    cin >> V >> A;
    Grafo g(V);
    for (int i = 0; i < A; i++) {
        int a, b;
        cin >> a >> b;
        g.ponArista(a - 1, b - 1);
    }

    mayorConexo analisis(g);
    cout << analisis.getMax() <<"\n";
    // escribir la solución
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
