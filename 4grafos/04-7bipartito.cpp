#include "Grafo.h"
#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

/*@ <answer>
La solución usa un recorrido BFS para comprobar si el grafo es bipartito.  
Cada vértice se marca con un nivel (distancia desde el origen).  
Si encontramos dos vértices adyacentes con la misma paridad de nivel, el grafo no es bipartito.  
Se repite el proceso para todas las componentes conexas.  
El coste total es O(V + A).
@ </answer>*/

class grafoBipartito {
  public:
    grafoBipartito(Grafo const& g)
        : visit(g.V(), false), dist(g.V()), bipartito(true) {
        for (int i = 0; i < g.V(); i++) {
            if (!visit[i]) {
                s = i;
                bfs(g);
            }
        }
    }

    bool getBipartito() const { return bipartito; }

  private:
    std::vector<bool> visit;
    std::vector<int> dist;
    int s;
    bool bipartito;

    void bfs(Grafo const& g) {
        std::queue<int> q;
        dist[s] = 0;
        visit[s] = true;
        q.push(s);
        while (!q.empty() && bipartito) {
            int v = q.front();
            q.pop();
            for (int w : g.ady(v)) {
                if (!visit[w]) {
                    dist[w] = dist[v] + 1;
                    visit[w] = true;
                    q.push(w);
                } else if (dist[w] % 2 == dist[v] % 2) {  // ✅ corregido
                    bipartito = false;
                }
            }
        }
    }
};

bool resuelveCaso() {
    int V, A;
    if (!(cin >> V)) return false;
    cin >> A;

    Grafo g(V);
    for (int i = 0; i < A; i++) {
        int u, v;
        cin >> u >> v;
        g.ponArista(u, v);
    }

    grafoBipartito gb(g);

    cout << (gb.getBipartito() ? "SI\n" : "NO\n");
    return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
