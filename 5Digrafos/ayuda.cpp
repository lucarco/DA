/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "Digrafo.h"

/*@ <answer>
 
 El problema se resuelve modelando el programa como un grafo dirigido de L+1 vértices.
 - Los nodos 0 a L-1 representan las instrucciones.
 - El nodo L representa la terminación del programa (salida).
 
 Las aristas se construyen según el tipo de instrucción:
 - A: arista al siguiente (i -> i+1).
 - J n: arista al salto (i -> n-1).
 - C n: dos aristas, al siguiente y al salto (i -> i+1, i -> n-1).
 
 Usamos un recorrido DFS para determinar dos cosas:
 1. Si el nodo final (L) es alcanzable desde el inicio (0).
 2. Si existe algún ciclo alcanzable desde el inicio.
    Para detectar ciclos en un grafo dirigido usamos un vector 'apilado' que marca
    los nodos que están en la rama de recursión actual. Si visitamos un nodo 'apilado',
    hay un ciclo.
 
 Complejidad:
 - Construcción del grafo: O(L)
 - DFS: O(V + E). Como V = L+1 y cada nodo tiene máximo 2 aristas, E <= 2L.
   Por tanto, el coste es lineal O(L) tanto en tiempo como en espacio.
 
 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

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
    int L;
    cin >> L;
    if (!cin) return false;

    // Creamos un grafo con L instrucciones + 1 nodo de terminación
    Digrafo g(L + 1);

    char tipo;
    int salto;

    for (int i = 0; i < L; ++i) {
        cin >> tipo;
        if (tipo == 'A') {
            // Avanza a la siguiente instrucción
            g.ponArista(i, i + 1);
        } 
        else if (tipo == 'J') {
            cin >> salto;
            // Salta a la instrucción 'salto' (ajustando índice a 0-based)
            g.ponArista(i, salto - 1);
        } 
        else if (tipo == 'C') {
            cin >> salto;
            // Puede avanzar O saltar
            g.ponArista(i, i + 1);
            g.ponArista(i, salto - 1);
        }
    }

    AnalizadorNecronomicon sol(g, L);
    cout << sol.resultado() << "\n";

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