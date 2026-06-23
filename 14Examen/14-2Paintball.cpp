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

#include "Grafo.h"

/*@ <answer>

 El problema se reduce a comprobar si el grafo es BIPARTITO.
 Un grafo es bipartito si se pueden dividir sus nodos en dos conjuntos disjuntos tal que
 no haya aristas entre nodos del mismo conjunto.

 Solución:
 Realizamos un recorrido (BFS o DFS) para intentar "colorear" el grafo con dos colores (1 y 2).
 - Vector 'equipo': Inicializado a 0 (sin equipo).
 - Si encontramos un nodo sin visitar, le asignamos equipo 1.
 - A sus vecinos les asignamos el equipo contrario (si soy 1, tú 2; si soy 2, tú 1).
 - Si encontramos un vecino que YA tiene equipo y es el MISMO que el nuestro -> Conflicto -> NO es posible.

 Coste: O(V + A), lineal respecto al tamaño del grafo.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class Paintball {
  private:
    vector<int> equipo;  // 0: Sin asignar, 1: Equipo A, 2: Equipo B
    bool posible;

    // BFS que intenta colorear una componente conexa empezando en 'src'
    void bfs(Grafo const& g, int src) {
        queue<int> q;
        q.push(src);
        equipo[src] = 1;  // Asignamos el primer equipo arbitrariamente

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (int w : g.ady(v)) {
                if (equipo[w] == 0) {
                    // Si el vecino no tiene equipo, le damos el contrario
                    // Si v es 1 -> w es 2. Si v es 2 -> w es 1.
                    equipo[w] = (equipo[v] == 1) ? 2 : 1;
                    q.push(w);
                } else if (equipo[w] == equipo[v]) {
                    // Conflicto: vecino ya visitado y tiene MI MISMO equipo
                    posible = false;
                    return;
                }
            }
        }
    }

  public:
    Paintball(Grafo const& g) : equipo(g.V(), 0), posible(true) {
        // El grafo puede tener varias islas (componentes conexas).
        // Hay que iterar sobre todos los nodos para asegurar que visitamos todos.
        for (int i = 0; i < g.V(); ++i) {
            if (equipo[i] == 0) {  // Si no ha sido visitado aún
                bfs(g, i);
                if (!posible) break;  // Si ya encontramos un conflicto, paramos
            }
        }
    }

    bool esFactible() const {
        return posible;
    }
};

bool resuelveCaso() {
    int V, A;
    cin >> V >> A;

    if (!std::cin) return false;

    Grafo g(V);
    int v, w;
    for (int i = 0; i < A; i++) {
        cin >> v >> w;
        // El enunciado usa índices 1..N, la clase Grafo usa 0..N-1
        g.ponArista(v - 1, w - 1);
    }

    Paintball solucion(g);

    if (solucion.esFactible())
        cout << "SI\n";
    else
        cout << "NO\n";

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