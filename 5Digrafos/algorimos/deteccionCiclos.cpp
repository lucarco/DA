#include <deque>

#include "Digrafo.h"

using namespace std;

class CicloDirigido {
  public:

    CicloDirigido(Digrafo const& g) : visit(g.V(), false), ant(g.V()), apilado(g.V(), false), hayciclo(false) {
        for (int v = 0; v < g.V(); ++v)
            if (!visit[v])
                dfs(g, v);
    }

    bool hayCiclo() const {
        return hayciclo;
    }

    // devuelve el camino más corto desde el origen a v (si existe)
    using Camino = std::deque<int>;  // para representar caminos

    Camino const& ciclo() const {
        return _ciclo;
    }

  private:
    std::vector<bool> visit;    // visit[v] = ¿se ha alcanzado a v en el dfs?
    std::vector<int> ant;       // ant[v] = vértice anterior en el camino a v
    std::vector<bool> apilado;  // apilado[v] = ¿está el vértice v en la pila?
    Camino _ciclo;              // ciclo dirigido (vacío si no existe)
    bool hayciclo;
    void dfs(Digrafo const& g, int v) {
        apilado[v] = true;
        visit[v] = true;
        for (int w : g.ady(v)) {
            if (hayciclo)  // si hemos encontrado un ciclo terminamos
                return;
            if (!visit[w]) {  // encontrado un nuevo vértice, seguimos
                ant[w] = v;
                dfs(g, w);
            } else if (apilado[w]) {  // hemos detectado un ciclo
                // se recupera retrocediendo
                hayciclo = true;
                for (int x = v; x != w; x = ant[x])
                    _ciclo.push_front(x);
                _ciclo.push_front(w);
                _ciclo.push_front(v);
            }
        }
        apilado[v] = false;
    }
};