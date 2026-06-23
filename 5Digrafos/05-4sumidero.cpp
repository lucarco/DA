
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

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
4
4
1 0
0 2
3 2
1 2
4
5
0 1
0 2
1 2
1 3
2 3


SALIDA
SI 2
NO



*/

class grafoSumidero {
  private:
    bool sumidero;
    int vertice_sumidero;
    Adys aristasSalida;

    void resuelve(Digrafo g) {
        for (int i = 0; i < g.V(); i++) {
            //  cout << "Arista " << i << " Aristas que salen " << g.ady(i).size() << "\n";
            aristasSalida[i] = g.ady(i).size();
        }

        Digrafo invertido = g.inverso();

        for (int i = 0; i < g.V(); i++) {
            // cout << "Arista " << i << " Aristas que salen " << invertido.ady(i).size() << "\n";

            if (aristasSalida[i] == 0 && invertido.ady(i).size() == g.V() - 1) {
                // cout << "Detecrtado con la arista " << i << endl;
                sumidero = true;
                vertice_sumidero = i;
            }
        }
    }

  public:
    grafoSumidero(Digrafo g) : sumidero(false), aristasSalida(g.V()) {
        resuelve(g);
    }

    bool haySumidero() {
        return sumidero;
    }
    int getSumidero() {
        return vertice_sumidero;
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int V, A;
    cin >> V >> A;
    if (!std::cin) {  // fin de la entrada
        return false;
    }

    Digrafo dg(V);

    for (int i = 0; i < A; i++) {
        int u, w;
        cin >> u >> w;
        dg.ponArista(u, w);
    }
    // resolver el caso posiblemente llamando a otras funciones

    grafoSumidero gs(dg);
    // escribir la solución
    if (gs.haySumidero()) {
        cout << "SI " << gs.getSumidero();
    } else {
        cout << "NO";
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
