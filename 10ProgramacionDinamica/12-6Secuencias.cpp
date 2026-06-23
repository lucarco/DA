/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <limits>
#include <algorithm>
#include<unordered_map>
using namespace std;

#include "Matriz.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

int charToInt(char c) {
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'G') return 2;
    if (c == 'T') return 3;
    else return 4;
}


int patin_rec(string const& palabra1, string const& palabra2, int i, int j, const Matriz<int>& valores, Matriz<int> &secuencia) {
    
    int& res = secuencia[i][j];
    if (res == -1) {
        if (i == 0 && j == 0) res = 0;
        else if (i == 0) {
            int b = charToInt(palabra2[j - 1]);
            res = patin_rec(palabra1, palabra2, 0, j - 1, valores, secuencia) + valores[4][b];
        }
        else if (j == 0) {
            int a = charToInt(palabra1[i - 1]);
            res = patin_rec(palabra1, palabra2, i - 1, 0, valores, secuencia) + valores[a][4];
        }
        else {
            int a = charToInt(palabra1[i - 1]);
            int b = charToInt(palabra2[j - 1]);
            res = max(patin_rec(palabra1, palabra2, i - 1, j, valores, secuencia) + valores[a][4],
                max(patin_rec(palabra1, palabra2, i, j - 1, valores, secuencia) + valores[4][b],
                    patin_rec(palabra1, palabra2, i - 1, j - 1, valores, secuencia) + valores[a][b]));

        }
        

    }
    return res;
}

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

void resuelveCaso() {

    // leer los datos de la entrada

    Matriz<int> valores(5, 5);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> valores[i][j];
        }
    }

    int n;
    cin >> n;

    string cadena1, cadena2;

    for (int i = 0; i < n; i++) {
        cin >> cadena1 >> cadena2;
        Matriz<int> m(cadena1.size() + 1, cadena2.size() + 1, -1);

        cout << patin_rec(cadena1, cadena2, cadena1.size(), cadena2.size(), valores, m) << "\n";
    }


    // resolver el caso posiblemente llamando a otras funciones

    // escribir la solución
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