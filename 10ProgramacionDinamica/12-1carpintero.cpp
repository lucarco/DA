
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

#include "EnterosInf.h"
#include "Matriz.h"  // propios o los de las estructuras de datos de clase

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
10 3
3 6 8
20 4
8 10 15 17
0 0

SALIDA
40
88

*/


EntInf minEsfuerzo(int N, int L, vector<int>& cortes) {
    Matriz<EntInf> matriz(N + 2, N + 2, 0);

    // l = long del segmento (nº cortes entre [i y j], ambos inclusive)
    for (int l = 2; l <= N + 1; l++) {
        for (int i = 0; i <= N + 1 - l; i++) {
            int j = i + l;
            matriz[i][j] = Infinito;

            // Se prueban todos los cortes entre i y j
            for (int k = i + 1; k < j; k++) {
                EntInf valor = matriz[i][k] + matriz[k][j] + 2 * (cortes[j] - cortes[i]);
                matriz[i][j] = min(matriz[i][j], valor);
            }
        }
    }

    return matriz[0][N + 1];
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int L, N;
    cin >> L >> N;

    if (L == 0 && N == 0) {
        return false;
    }
    // resolver el caso posiblemente llamando a otras funciones
    vector<int> cortes(N + 2);  // se dan en orden creciente
    cortes[0] = 0;
    for (int i = 1; i <= N; i++) {
        cin >> cortes[i];
    }
    cortes[N + 1] = L;  // array de donde estan los cortes

    // escribir la solución
    cout << minEsfuerzo(N, L, cortes) << "\n";
    /* for (int i = 0; i < matriz.numcols(); i++) {
         for (int j = 0; j < matriz.numfils(); j++) {
             cout << matriz[i][j] << " ";
         }
         cout << "\n";
     }*/
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
