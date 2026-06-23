
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

Entrada de ejemplo
3
1 5
3 10
6 12
2
5 10
1 5
3
1 5
2 6
3 7
0

Salida de ejemplo
1
0
2

*/

struct tActividad {
    int ini;
    int fin;
};

// bool operator<(tActividad a1, tActividad a2) {
//     return a1.fin < a2.fin;
// }
bool operator<(tActividad a1, tActividad a2) {
    return a1.ini < a2.ini;
}

int solucionar(PriorityQueue<tActividad, less<tActividad>>& pq, int N) {
    PriorityQueue<int, less<int>> amigos;
    amigos.push(0);
    int sol = 0;

    for (int i = 0; i < N; i++) {
        tActividad aux = pq.top();
        pq.pop();
        int amigo = amigos.top();
        if (amigo > aux.ini) {
            sol++;
        } else {
            amigos.pop();
        }
        amigos.push(aux.fin);
    }

    return sol;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N;
    cin >> N;

    if (N == 0)
        return false;

    // resolver el caso posiblemente llamando a otras funciones
    PriorityQueue<tActividad, less<tActividad>> pq;  // se ordenan de cuanto antes termine a dps
    int ini, fin;
    for (int i = 0; i < N; i++) {
        cin >> ini >> fin;
        pq.push({ini, fin});
    }

    // escribir la solución
    int sol = solucionar(pq, N);
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
