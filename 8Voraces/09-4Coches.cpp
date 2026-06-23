
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <algorithm>
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
/*

ENTRADA
2
4 20
8 10 12 15
5 30
20 12 7 18 2


SALIDA
2
1


*/
int coches(vector<int> pilas, int N, int V) {
    int sol = 0;
    sort(pilas.begin(), pilas.end());
    int contMax = N - 1;
    for (int i = 0; i < contMax; i++) {
        if(pilas[i] + pilas[contMax] >= V){
            sol++;
            contMax--;
        }
    }

    return sol;
}
void resuelveCaso() {
    int N, V;
    cin >> N >> V;
    // leer los datos de la entrada
    vector<int> pilas(N);
    for (int i = 0; i < N; i++) {
        cin >> pilas[i];
    }

    // resolver el caso posiblemente llamando a otras funciones

    // escribir la solución
    cout << coches(pilas, N, V) << "\n";
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

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
