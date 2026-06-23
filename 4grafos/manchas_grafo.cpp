
/*@ <answer>
 *
 * Nombre y Apellidos: Lucas Arranz
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

class mayorComponenteConexa {
  public:
    int numConexos;
    int mayorConexo;
    int actConexo;

    void dfs(Grafo g){

    }

  private:

    mayorComponenteConexa(Grafo g, vector<bool> es_mancha){
        numConexos = 0;
        mayorConexo = 0;
        actConexo = 0;
        for(int i = 0; i < g.V(); i++){
            if(es_mancha)
        }
    }

    int getNumConexos() {
        return numConexos;
    }
    int getMayorConexo() {
        return mayorConexo;
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int F, C;
    vector<bool> es_mancha;

    cin >> C >> F;
    if (!std::cin)  // fin de la entrada
        return false;

    Grafo g(F * C);

    for (int i = 0; i < F; i++) {
        for (int j = 0; j < C; j++) {
            char aux;
            cin >> aux;
            if (aux == '#') {
                es_mancha[i * 10 + j] = true;
                if (i != 0 && es_mancha[(i - 1) * 10 + j]) {
                    g.ponArista(i * 10 + j, (i - 1) * 10 + j);
                }
                if (j != 0 && es_mancha[i * 10 + j - 1]) {
                    g.ponArista(i * 10 + j, i * 10 + j - 1);
                }
            } else {
                es_mancha[i * 10 + j] = false;
            }
        }
    }
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
