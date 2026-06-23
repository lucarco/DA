
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
5
10 6 8 5 7
2 3 5 3 1
2
8 3
2 1

SALIDA
2
2

*/
int salvar(vector<double>& tiempos, int Z) {
    sort(tiempos.begin(), tiempos.end());
    bool seguir = true;
    int i = 0;

    while (i < Z && seguir) {
        if (tiempos[i] <= i)  // si el zombi llega antes o justo cuando se le dispara → fin
            seguir = false;
        else
            i++;
    }

    return i;
}

bool resuelveCaso() {
    int Z;
    cin >> Z;

    if (!cin) return false;

    vector<double> zombies(Z);  // aquí se guardarán los tiempos de llegada
    for (int i = 0; i < Z; i++) {
        cin >> zombies[i];  // inicialmente guardamos la distancia
    }

    for (int i = 0; i < Z; i++) {
        int v;
        cin >> v;
        zombies[i] /= v;  // convertimos distancia en tiempo (distancia / velocidad)
    }
    
    cout << salvar(zombies, Z) << "\n";

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
