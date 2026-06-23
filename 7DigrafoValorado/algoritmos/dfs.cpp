#include <iostream>
#include "DigrafoValorado.h"




// visita los vértices alcanzables desde v respetando el umbral
void dfs(DigrafoValorado<int> const& g, int v, int ancho) {
    visit[v] = true;
    for (auto a : g.ady(v)) {
        if (a.valor() > ancho) {
            int w = a.hasta();
            if (!visit[w])
                dfs(g, w, ancho);
        }
    }
}