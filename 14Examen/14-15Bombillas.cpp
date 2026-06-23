
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

Entrada de ejemplo
2 7 4
5 2
30 10
3 8 6
2 3 5
30 45 50
3 11 11
4 6 4
1 2 3

Salida de ejemplo
20 4
80 7
IMPOSIBLE

*/

struct tBombilla {
    int potencia;
    int valor;
};

struct tSol {
    int potencia;
    EntInf coste;
};

tSol minimo_coste(int N, int Pmax, int Pmin, vector<tBombilla> const& bombilla) {
    Matriz<EntInf> m(N + 1, Pmax + 1, Infinito);

    for (int i = 0; i < N + 1; i++) {
        m[i][0] = 0;
    }
    for (int i = 1; i < N + 1; i++) {
        for (int j = 1; j < Pmax + 1; j++) {
            if (bombilla[i - 1].potencia > j) {
                m[i][j] = m[i - 1][j];
            } else {
                m[i][j] = min(m[i - 1][j], m[i][j - bombilla[i - 1].potencia] + bombilla[i - 1].valor);
            }
        }
    }

    tSol sol = {-1, Infinito};

    for (int j = Pmin; j <= Pmax; j++) {
        if (m[N][j] < sol.coste) {
            sol = {j, m[N][j]};
        }
    }

    return sol;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, Pmax, Pmin;
    cin >> N >> Pmax >> Pmin;

    if (!std::cin)  // fin de la entrada
        return false;

    // resolver el caso posiblemente llamando a otras funciones
    vector<tBombilla> bombilla(N);
    for (int i = 0; i < N; i++) {
        cin >> bombilla[i].potencia;
    }
    for (int i = 0; i < N; i++) {
        cin >> bombilla[i].valor;
    }

    tSol sol = minimo_coste(N, Pmax, Pmin, bombilla);
    if (sol.coste == Infinito) {
        cout << "IMPOSIBLE\n";
    } else {
        cout << sol.coste << " " << sol.potencia << "\n";
    }

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
