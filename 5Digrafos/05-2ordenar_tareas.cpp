
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

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
7
8
1 2
2 3
2 4
3 5
2 5
4 5
5 6
7 4
2
2
1 2
2 1




SALIDA
1 2 7 3 4 5 6
Imposible

*/
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <vector>

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase
using namespace std;

using Camino = list<int>;

class CicloDirigido {
  public:
    CicloDirigido(Digrafo const& g)
        : visit(g.V(), false), ant(g.V(), -1), apilado(g.V(), false), hayciclo(false) {
        for (int v = 0; v < g.V(); ++v)
            if (!visit[v]) dfs(g, v);
    }

    bool hayCiclo() const {
        return hayciclo;
    }

  private:
    vector<bool> visit, apilado;
    vector<int> ant;
    bool hayciclo;

    void dfs(Digrafo const& g, int v) {
        apilado[v] = true;
        visit[v] = true;
        for (int w : g.ady(v)) {
            if (hayciclo) return;
            if (!visit[w]) {
                ant[w] = v;
                dfs(g, w);
            } else if (apilado[w]) {
                hayciclo = true;
                return;
            }
        }
        apilado[v] = false;
    }
};
class OrdenTopologico {
  public:
    OrdenTopologico(Digrafo const& g) : visit(g.V(), false) {
        for (int v = 0; v < g.V(); ++v)
            if (!visit[v])
                dfs(g, v);
    }

    deque<int> const& orden() const {
        return _orden;
    }

  private:
    vector<bool> visit;
    deque<int> _orden;

    void dfs(Digrafo const& g, int v) {
        visit[v] = true;
        for (int w : g.ady(v))
            if (!visit[w])
                dfs(g, w);
        _orden.push_front(v);
    }
};
// ----------------------------------------------------------
bool resuelveCaso() {
    int N, M;
    if (!(cin >> N)) return false;
    cin >> M;

    Digrafo g(N);
    for (int i = 0; i < M; ++i) {
        int A, B;
        cin >> A >> B;
        g.ponArista(A - 1, B - 1);  // índices desde 0
    }

    // 1️⃣ Comprobamos si hay ciclo
    CicloDirigido cd(g);
    if (cd.hayCiclo()) {
        cout << "Imposible\n";
        return true;
    }

    // 2️⃣ Si no hay ciclo, calculamos orden topológico
    OrdenTopologico ot(g);
    const auto& orden = ot.orden();

    for (auto it = orden.begin(); it != orden.end(); ++it) {
        cout << (*it + 1);
        if (next(it) != orden.end()) cout << " ";
    }
    cout << "\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    cin.rdbuf(in.rdbuf());
#endif
    while (resuelveCaso());
#ifndef DOMJUDGE
    system("PAUSE");
#endif
    return 0;
}
