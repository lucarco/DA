
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>
//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.
/*

Entrada de ejemplo
3
6 10
6 100
10 100

Salida de ejemplo
35
189509
6292069
*/

int maneras_totales(int k, int suma) {
    vector<int> maneras(suma + 1, 0);
    maneras[0] = 1;

    for (int i = 1; i < k + 1; i++) {
        for (int j = 0; j < suma + 1; j++) {
            if (i <= j) {
                maneras[j] += maneras[j - i];
            }
        }
    }

    return maneras[suma];
}
void resuelveCaso() {
    // leer los datos de la entrada
    int k, suma;
    cin >> k >> suma;
    // resolver el caso posiblemente llamando a otras funciones

    // escribir la solución
    cout << maneras_totales(k, suma) << "\n";
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
