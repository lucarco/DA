
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

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
1
10
3
3 1 4
4
3 4 5 6
0

Salida de ejemplo
0
12
36



*/

bool resuelveCaso() {
    // leer los datos de la entrada
    int N;
    cin >> N;

    if (N == 0) {
        return false;
    }
    // resolver el caso posiblemente llamando a otras funciones

    PriorityQueue<long long> pq;
    long long aux;
    for (int i = 0; i < N; i++) {
        cin >> aux;
        pq.push(aux);
    }

    // escribir la solución
    long long sol = 0;
    long long equipo1, equipo2;
    while (pq.size() != 1) {
        equipo1 = pq.top();
        pq.pop();
        equipo2 = pq.top();
        pq.pop();
        sol += equipo1 + equipo2;
        pq.push(equipo1 + equipo2);
    }

    cout << sol << "\n";

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
