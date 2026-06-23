
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <fstream>
#include <iostream>
using namespace std;

#include "ConjuntosDisjuntos.h"
#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
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
Entrada de ejemplo
5
7
1 2 7
1 3 6
3 2 1
1 4 10
3 4 15
3 5 3
4 5 12
4
3
1 3 2
1 4 3
3 4 5

Salida de ejemplo
20
Imposible






*/
template <typename Valor>
class ARM_Kruskal {
  private:
    Valor coste;
    bool conexo;

  public:
    Valor costeARM() const {
        return coste;
    }


    bool esConexo() {
        return conexo;
    }

    ARM_Kruskal(GrafoValorado<Valor> const& g) : coste(0), conexo(false) {
        PriorityQueue<Arista<Valor>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        while (!pq.empty()) {
            auto a = pq.top();
            pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                coste += a.valor();
            }
        }
        if (cjtos.num_cjtos() == 1) {
            conexo = true;
        }
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int V, A;
    cin >> V >> A;

    if (!std::cin)  // fin de la entrada
        return false;

    // resolver el caso posiblemente llamando a otras funciones
    GrafoValorado<int> g(V);

    int v, w, coste;
    for (int i = 0; i < A; i++) {
        cin >> v >> w >> coste;
        g.ponArista({v - 1, w - 1, coste});
    }

    // escribir la solución
    ARM_Kruskal<int> arm(g);

    if (arm.esConexo()) {
        cout << arm.costeARM() << "\n";
    } else {
        cout << "Imposible\n";
    }

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
