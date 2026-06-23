
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

#include "Matriz.h"

// #include "Matriz.h"  // propios o los de las estructuras de datos de clase

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
roda
amad
reconor
reconocer


SALIDA
3 adoroda
1 damad
2 reconocer
0 reconocer

*/

string reconstruir(string const& palabra, Matriz<int> const& m, int i, int j) {
    if (i > j) return {};
    if (i == j) return string(1, palabra[i]);  // O return { palabra[i] };

    if (palabra[i] == palabra[j]) {
        // Coinciden: ponemos la letra a los lados y cerramos el intervalo
        return palabra[i] + reconstruir(palabra, m, i + 1, j - 1) + palabra[j];
    }
    // Si no coinciden, miramos de dónde vino el valor mínimo en la tabla m
    // Recordamos que m[i][j] = 1 + min(m[i+1][j], m[i][j-1])
    else if (m[i][j] == 1 + m[i + 1][j]) {
        // La solución óptima vino de emparejar palabra[i].
        // Ponemos palabra[i] a ambos lados y resolvemos para (i+1, j)
        return palabra[i] + reconstruir(palabra, m, i + 1, j) + palabra[i];
    } else {
        // La solución óptima vino de emparejar palabra[j].
        // Ponemos palabra[j] a ambos lados y resolvemos para (i, j-1)
        return palabra[j] + reconstruir(palabra, m, i, j - 1) + palabra[j];
    }
}

int min_inserciones(string const& palabra, int i, int j, Matriz<int>& m) {
    int& res = m[i][j];  // Referencia a la casilla de la matriz

    if (res == -1) {  // Si no ha sido calculado
        if (i >= j) {
            // Caso base: Si la longitud es 0 o 1, ya es palíndromo.
            // Coste = 0 inserciones.
            res = 0;
        } else if (palabra[i] == palabra[j]) {
            // Si coinciden los extremos, no cuesta nada extra.
            // Nos fiamos del interior.
            res = min_inserciones(palabra, i + 1, j - 1, m);
        } else {
            // Si no coinciden, probamos las dos opciones y sumamos 1 inserción.
            // Usamos 'min' porque buscamos el menor número de letras a añadir.
            res = 1 + min(min_inserciones(palabra, i + 1, j, m),
                          min_inserciones(palabra, i, j - 1, m));
        }
    }
    return res;
}

bool resuelveCaso() {
    string palabra;
    cin >> palabra;

    if (!std::cin) return false;

    int n = palabra.length();

    Matriz<int> m(n, n, -1);

    // Llamamos a la función para toda la palabra (desde 0 hasta n-1)
    int coste = min_inserciones(palabra, 0, n - 1, m);
    string recontruccion = reconstruir(palabra, m, 0, n - 1);
    cout << coste << " " << recontruccion << "\n";

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
