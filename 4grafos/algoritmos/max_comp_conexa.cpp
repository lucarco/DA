#include <fstream>
#include <iostream>
// #include <...>
using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

class MaximaCompConexa {
  public:
    MaximaCompConexa(Grafo const& g) : visit(g.V(), false), maxim(0) {
        for (int v = 0; v < g.V(); ++v) {
            if (!visit[v]) {  // se recorre una nueva componente conexa
                int tam = dfs(g, v);
                maxim = max(maxim, tam);
            }
        }
    }
    // tamaño máximo de una componente conexa
    int maximo() const {
        return maxim;
    }

  private:
    vector<bool> visit;  // visit[v] = se ha visitado el vértice v?
    int maxim;           // tamaño de la componente mayor
    int dfs(Grafo const& g, int v) {
        visit[v] = true;
        int tam = 1;
        for (int w : g.ady(v)) {
            if (!visit[w])
                tam += dfs(g, w);
        }
        return tam;
    }
};