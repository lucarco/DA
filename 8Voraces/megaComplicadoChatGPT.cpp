/*
Una empresa de transporte quiere instalar estaciones de distribución en una red de carreteras dirigidas.
La red se representa mediante un grafo dirigido y valorado, donde cada arista tiene un coste que indica la
distancia o el tiempo de recorrido.

Existen varios tipos de nodos:
Candidatos a estaciones: lugares donde se puede instalar una estación (tienen un coste de instalación).
Terminales de entrega: puntos que deben ser atendidos por al menos una estación.
El resto de los nodos son intermedios o de paso.

Cada estación instalada tiene un rango máximo de alcance (una distancia máxima dentro de la cual puede atender
terminales).
Una estación cubre un terminal si existe un camino dirigido desde la estación hasta el terminal cuya suma
de pesos no supere ese rango.*/

/*
ENTRADA:
num_casos
V A max_cobertura(distancia)
u w valor A veces(cada uno en una linea)
una linea con V valores(E, T) dependiendo de si son estaciones, terminales o de paso

SALIDA:
int valor minimo para repartir la mercancia

/*
ENTRADA:
2
6 7 6
0 1 2
0 2 5
1 3 2
2 3 1
3 4 3
1 5 7
4 5 1
E E E T T T
5 6 6
0 1 4
1 2 3
2 3 5
1 4 2
4 3 4
0 2 6
E T P E T


SALIDA
4



*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
#include "DigrafoValorado.h"


void resuelveCaso(){
    int V, A;
    DigrafoValorado<int> dV(V);
    for(int)

}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}