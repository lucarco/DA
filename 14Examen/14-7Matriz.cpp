
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <fstream>
#include <iostream>
using namespace std;

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
3 4
2 1 1 2
3 2 1 8
3 1 1 5
3 3
1 1 1
1 1 1
1 1 1

Salida de ejemplo
3
6



*/

int salto_rec(Matriz<int> const& valores, int i, int j, Matriz<int>& sol) {
    // 1. Caso Base: Hemos llegado a la esquina inferior derecha
    if (i == valores.numfils() - 1 && j == valores.numcols() - 1) {
        return 1;
    }

    // 2. Comprobamos la tabla de memoización
    int& res = sol[i][j];
    if (res == -1) {
        // Inicializamos a 0. Solo sumamos si los hijos encuentran caminos al destino.
        res = 0;
        int salto = valores[i][j];

        // Opción A: Saltar Abajo
        if (i + salto < valores.numfils()) {
            res += salto_rec(valores, i + salto, j, sol);
        }

        // Opción B: Saltar Derecha
        if (j + salto < valores.numcols()) {
            res += salto_rec(valores, i, j + salto, sol);
        }
    }
    return res;
}

bool resuelveCaso() {
    // leer los datos de la entrada

    int filas, cols;
    cin >> filas >> cols;

    if (!std::cin)  // fin de la entrada
        return false;

    Matriz<int> valores(filas, cols);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> valores[i][j];
        }
    }
    // resolver el caso posiblemente llamando a otras funciones
    Matriz<int> m(filas, cols, -1);
    int sol = salto_rec(valores, 0, 0, m);
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
