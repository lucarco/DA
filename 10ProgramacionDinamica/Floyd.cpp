

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

#include "Matriz.h"
#include "EnterosInf.h"

//
//  Matriz.h
//
//  Implementación de matrices (arrays bidimensionales)
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020  Alberto Verdejo
//




//
//  EnterosInf.h
//
//  Implementación de enteros con +infinito.
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020  Alberto Verdejo
//







void Floyd(Matriz<EntInf> const& G, Matriz<EntInf> & C, Matriz<int> & A) {
   int V = G.numfils(); // número de vértices de G
   // inicialización
   C = G;
   A = Matriz<int>(V, V, -1);
   for (int i = 0; i < V; ++i) {
      for (int j = 0; j < V; ++j) {
         if (i != j && G[i][j] != Infinito) A[i][j] = i;
      }
   }
   // actualizaciones de las matrices
   for (int k = 0; k < V; ++k) {
      for (int i = 0; i < V; ++i) {
         for (int j = 0; j < V; ++j) {
            auto temp = C[i][k] + C[k][j];
            if (temp < C[i][j]) { // es mejor pasar por k
               C[i][j] = temp;
               A[i][j] = A[k][j];
            }
         }
      }
   }
}

using Camino = std::deque<int>;
Camino ir_de(int i, int j, Matriz<int> const& A) {
   Camino cam;
   while (j != i) {
      cam.push_front(j);
      j = A[i][j];
   }
   cam.push_front(i);
   return cam;
}


// HAZ LOS CAMBIOS NECESARIOS EN LAS FUNCIONES Floyd y ir_de
// PARA QUE DE CADA CAMINO DESDE i HASTA j, LA MATRIZ DEVUELTA
// POR Floyd DIGA CUÁL ES EL SIGUIENTE VÉRTICE A i (EN VEZ DEL
// ANTERIOR A j)

int main() {
   
   // construcción del grafo
   int V = 5;
   Matriz<EntInf> grafo(V,V,Infinito);
   for (int i = 0; i < V; ++i) {
      grafo[i][i] = 0;
   }

   grafo[0][1] = 3;
   grafo[0][2] = 8;
   grafo[0][4] = -4;
   grafo[1][4] = 7;
   grafo[1][3] = 1;
   grafo[2][1] = 4;
   grafo[3][2] = -5;
   grafo[3][0] = 2;
   grafo[4][3] = 6;

   Matriz<EntInf> C;
   Matriz<int> S;
   
   Floyd(grafo, C, S);

   int u = 2, v = 4;
   cout << "Coste de " << u << " a " << v << ": " << C[u][v] << '\n';
   // debe salir: Coste de 2 a 4: 3
   if (C[u][v] != Infinito) {
      auto cam = ir_de(u, v, S);
      cout << "Camino:";
      for (int v : cam) cout << ' ' << v; cout << '\n';
      // debe salir: Camino: 2 1 3 0 4
   }
   return 0;
}
