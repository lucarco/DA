
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

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
4 50
10 25
20 15
30 40
40 75
3 10
1 30
2 60
3 90
3 2
1 10
1 10
1 10



SALIDA
SI 2 2 55
NO
SI 3 2 20

// nº de formas de conseguir la cuerda, min cuerdas, min coste necesario

*/

struct tCuerda {
    int largo;
    int coste;
};

struct tSol {
    EntInf min_cuerdas;
    EntInf min_coste;
    int maneras;
};

tSol solucionar(int L, vector<tCuerda>& cuerdas) {
    vector<EntInf> cuerdas_usadas(L + 1, Infinito);
    vector<EntInf> costes(L + 1, Infinito);
    vector<int> maneras(L + 1, 0);

    cuerdas_usadas[0] = 0;
    costes[0] = 0;
    maneras[0] = 1;

    for (int i = 0; i < cuerdas.size(); i++) {
        for (int j = L; j >= cuerdas[i].largo; j--) {
            if (cuerdas[i].largo <= j) {
                if (cuerdas_usadas[j - cuerdas[i].largo] != Infinito) {
                    cuerdas_usadas[j] = min(cuerdas_usadas[j], cuerdas_usadas[j - cuerdas[i].largo] + 1);
                    costes[j] = min(costes[j], costes[j - cuerdas[i].largo] + cuerdas[i].coste);
                }
                maneras[j] += maneras[j - cuerdas[i].largo];
            }
        }
    }

    return {cuerdas_usadas[L], costes[L], maneras[L]};
}
bool resuelveCaso() {
    // leer los datos de la entrada
    int N, L;

    cin >> N >> L;
    vector<tCuerda> cuerdas(N);

    for (int i = 0; i < N; i++) {
        cin >> cuerdas[i].largo >> cuerdas[i].coste;
    }

    if (!std::cin) {
        return false;
    }
    // resolver el caso posiblemente llamando a otras funciones

    // escribir la solución

    tSol sol = solucionar(L, cuerdas);


    if (sol.maneras != 0) {
        cout << "SI " << sol.maneras << " " << sol.min_cuerdas << " " << sol.min_coste << "\n";
    } else {
        cout << "NO\n";
    }

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
