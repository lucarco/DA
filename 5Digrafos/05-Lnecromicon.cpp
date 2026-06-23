
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <fstream>
#include <iostream>
#include <queue>
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
3
A
A
J 1
5
A
J 4
J 5
C 3
A
4
A
A
C 2
A

SALIDA
NUNCA
SIEMPRE
A VECES

*/

class AnalizadorNecronomicon {
private:
    vector<bool> visitado;
    vector<bool> apilado; // Para detectar ciclos (back-edges)
    bool llegaFinal;
    bool tieneCiclo;
    int meta; // El nodo que representa el final (L)

    void dfs(const Digrafo& g, int u) {
        visitado[u] = true;
        apilado[u] = true;

        if (u == meta) {
            llegaFinal = true;
        }

        for (int v : g.ady(u)) {
            if (!visitado[v]) {
                dfs(g, v);
            } else if (apilado[v]) {
                // Si el vecino ya está visitado Y está en la pila de recursión actual,
                // hemos encontrado un ciclo (back-edge).
                tieneCiclo = true;
            }
        }

        apilado[u] = false; // Desmarcamos al salir de la recursión
    }

public:
    AnalizadorNecronomicon(const Digrafo& g, int L) : 
        visitado(g.V(), false), apilado(g.V(), false), 
        llegaFinal(false), tieneCiclo(false), meta(L) {
        
        // Iniciamos el análisis desde la instrucción 1 (índice 0)
        dfs(g, 0);
    }

    string resultado() const {
        if (!llegaFinal) return "NUNCA";
        if (tieneCiclo) return "A VECES";
        return "SIEMPRE";
    }
};


bool resuelveCaso() {
    // leer los datos de la entrada
    int L;
    cin >> L;
    if (!std::cin) {  // fin de la entrada
        return false;
    }

    Digrafo g(L + 1);
    char aux;
    int salto;

    for (int i = 0; i < L; i++) {
        cin >> aux;
        switch (aux) {
            case 'A':
                g.ponArista(i, i + 1);
                break;
            case 'J':
                cin >> salto;
                g.ponArista(i, salto - 1);
                break;
            case 'C':
                cin >> salto;
                g.ponArista(i, salto - 1);
                g.ponArista(i, i + 1);

                break;
            default:
                break;
        }
    }

    // resolver el caso posiblemente llamando a otras funciones
    AnalizadorNecronomicon sol(g, L);
    cout << sol.resultado() << "\n";

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
