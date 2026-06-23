
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <fstream>
#include <iostream>

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
7 5
3 2 5 4
0
2 1 2
1 1
2 6 7
4 2
1 1
1 3


SALIDA
4 4 1 4 4 2 2
1 1 1 1


*/
class ComponenteConexa {
  private:
    vector<bool> visit;            // visit[v] = se ha visitado el vértice v?
    vector<int> amigo_componente;  // a qué componente pertenece cada amigo
    vector<int> tam_componente;    // tamaño de cada componente conexa
    int num_comp;               // contador para las funciones

    int dfs(Grafo const& g, int v, int comp_id) {
        visit[v] = true;
        amigo_componente[v] = comp_id;
        int tam = 1;
        for (int w : g.ady(v)) {
            if (!visit[w])
                tam += dfs(g, w, comp_id);
        }
        return tam;
    }

  public:
    ComponenteConexa(Grafo const& g) : visit(g.V(), false), amigo_componente(g.V(), -1) {
        num_comp = 0;
        for (int v = 0; v < g.V(); ++v) {
            if (!visit[v]) {  // se recorre una nueva componente conexa
                int tam = dfs(g, v, num_comp);
                tam_componente.push_back(tam);
                num_comp++;
            }
        }
    }

    int noticia(int amigo) const {
        return tam_componente[amigo_componente[amigo]];
    }
};

bool resuelveCaso() {
    int V, grupos;

    // Leer número de vértices y grupos
    cin >> V >> grupos;
    if (!cin) return false;

    Grafo g(V);

    for (int i = 0; i < grupos; i++) {
        int participantes;
        cin >> participantes;

        if (participantes > 0) {
            int u;
            cin >> u;
            for (int j = 1; j < participantes; j++) {
                int w;
                cin >> w;
                g.ponArista(u - 1, w - 1);
            }
        }
    }

    // Resolver el caso
    ComponenteConexa sol(g);

    // Escribir la solución
    for (int i = 0; i < V; i++) {
        cout << sol.noticia(i);
        if (i < V - 1) cout << " ";
    }
    cout << "\n";

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
