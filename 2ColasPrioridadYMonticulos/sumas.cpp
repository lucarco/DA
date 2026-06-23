
/*@ <answer>
 *
 * Nombre y Apellidos: Lucas Arranz Corral
 *
 *@ </answer> */

#include <fstream>
#include <iostream>
// #include <...>
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

ENTRADA
3
1 2 3
4
3 1 4 2
4
30 40 50 60
1
5
0



SALIDA
9
19
360 // creo que está mal, que debería de poner 370
0

*/

bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;

    if (n == 0) return false;

    // resolver el caso posiblemente llamando a otras funciones

    PriorityQueue<int, less<int>> sumandos;

    for (int i = 0; i < n; i++) {
        int aux;
        cin >> aux;
        sumandos.push(aux);
    }

    int sol = 0;
    int sumandoAnt = sumandos.top();
    sumandos.pop();

    for (int i = 1; i < n; i++) {
        sumandoAnt += sumandos.top();
        sol += sumandoAnt;
        sumandos.pop();
    }

    cout << sol << "\n";
    // escribir la solución

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
