/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#include "ConjuntosDisjuntos.h"
#include "GrafoValorado.h"
#include "PriorityQueue.h"

/*@ <answer>
 
 El problema pide conectar todos los nodos minimizando el tiempo total.
 Dado que las tareas se realizan en PARALELO, el tiempo total es igual al tiempo
 de la carretera más lenta necesaria para conectar el grafo (cuello de botella).
 
 Usamos el algoritmo de Kruskal para encontrar el Árbol de Recubrimiento Mínimo (ARM).
 Como Kruskal añade aristas de menor a mayor peso, la última arista añadida que 
 logra conectar el grafo tendrá el peso máximo necesario, que equivale al tiempo total.
 
 Coste: O(A log A) o O(A log V) debido a la ordenación de las aristas en la cola de prioridad.
 
 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>
/*
Entrada de ejemplo
3
3 3
1 2 10
2 3 20
3 1 30
4 2
1 3 10
4 2 10
4 3
1 2 20
1 3 30
1 4 10

Salida de ejemplo
20
Imposible
30






*/

template <typename Valor>
class ARM_Kruskal {
  private:
    int cont;
    Valor coste; // Guardará el tiempo máximo (no la suma)

  public:
    Valor costeARM() const {
        return coste;
    }

    bool esConexo() {
        return cont == 0;
    }

    ARM_Kruskal(GrafoValorado<Valor> const& g) : coste(0), cont(g.V() - 1) {
        // Si solo hay un pueblo, ya está conectado y el coste es 0
        if (g.V() <= 1) {
            cont = 0;
            return;
        }

        PriorityQueue<Arista<Valor>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        
        while (!pq.empty()) {
            auto a = pq.top();
            pq.pop();
            int v = a.uno(), w = a.otro(v);
            
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                
                // CORRECCIÓN 1: No sumamos (+=), asignamos (=).
                // Como las sacamos ordenadas de menor a mayor, la última que necesitemos
                // será la de mayor peso (la que más tarda) y determinará el tiempo final.
                coste = a.valor();
                
                cont--;
                if (cont == 0) break;
            }
        }
    }
};

void resuelveCaso() {
    // leer los datos de la entrada
    int V, A;
    cin >> V >> A;

    GrafoValorado<int> g(V);

    int v, w, coste;
    // CORRECCIÓN 2: Iteramos hasta A (número de carreteras), no V
    for (int i = 0; i < A; i++) {
        cin >> v >> w >> coste;
        g.ponArista({v - 1, w - 1, coste});
    }

    ARM_Kruskal<int> arm(g);

    // CORRECCIÓN 3: Evitamos aritmética de punteros en el cout
    if (arm.esConexo()) {
        cout << arm.costeARM() << "\n";
    } else {
        cout << "Imposible\n";
    }
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // CORRECCIÓN 4: Lectura del número de casos
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}