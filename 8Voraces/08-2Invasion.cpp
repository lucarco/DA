
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
4
40 20 80 30
25 50 35 40
4
40 50 60 70
99 25 30 50



SALIDA
3
2

*/

int victorias(vector<int>& enemigos, vector<int>& defensa, int N) {
    int sol = 0;
    sort(enemigos.begin(), enemigos.end());
    sort(defensa.begin(), defensa.end());

    int contE = 0;
    int contD = 0;
    while (contD < N) {
        if (defensa[contD] >= enemigos[contE]) {
            sol++;
            contE++;
        }
        contD++;
    }

    return sol;
}
bool resuelveCaso() {
    // leer los datos de la entrada
    int N;
    cin >> N;
    vector<int> enemigos(N), defensa(N);
    for (int i = 0; i < N; i++) {
        cin >> enemigos[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> defensa[i];
    }

    if (!std::cin) {  // fin de la entrada
        return false;
    }

    // resolver el caso posiblemente llamando a otras funciones
    cout << victorias(enemigos, defensa, N) << "\n";
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
