
/*@ <answer>
 *
 * Nombre y Apellidos: Lucas Arranz Corral
 *
 *@ </answer> */

#include <deque>
#include <fstream>
#include <iostream>
// #include <...>
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

6
5
0 5
0 2
2 1
2 3
4 3
6
5
0 1
1 2
2 3
3 0
4 5

SALIDA
SI
NO

*/

class ArbolLibreDFS {
    private:
        std::vector<bool> visitado;  // visitado[v] = ¿ha sido visitado el vértice v?
        bool hayCiclo;               // indica si se encontró un ciclo durante el DFS

        // DFS modificado para detectar ciclos
        void dfs(Grafo const& g, int v, int padre) {
            visitado[v] = true;
            for (int w : g.ady(v)) {
                if (!visitado[w]) {
                    dfs(g, w, v);
                } else if (w != padre) {    
                    // Encontramos un vértice ya visitado que no es el padre →
                    // ciclo
                    hayCiclo = true;
                }
            }
        }

    public:
        // Constructor principal: realiza el análisis
        ArbolLibreDFS(Grafo const& g) {
            int V = g.V();
            visitado.assign(V, false);
            hayCiclo = false;

            // Lanzamos DFS desde el primer vértice
            dfs(g, 0, -1);

            // Comprobamos si el grafo es conexo
            bool conexo = true;
            for (bool v : visitado)
                if (!v) conexo = false;

            // Resultado final
            if (!hayCiclo && conexo && g.A() == g.V() - 1)
                std::cout << "SI\n";
            else
                std::cout << "NO\n";
        }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int V, A;
    cin >> V >> A;

    if (!std::cin)  // fin de la entrada
        return false;

    Grafo g(V);
    for (int i = 0; i < A; i++) {
        int a, b;
        cin >> a >> b;
        g.ponArista(a, b);
    }
    // resolver el caso posiblemente llamando a otras funciones
    ArbolLibreDFS analisis(g);

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
