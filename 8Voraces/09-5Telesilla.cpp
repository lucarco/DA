
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
20 4
10 10 10 10
30 5
12 20 10 16 8
40 6
30 30 30 30 30 30


SALIDA
2
3
6

*/

int telesilla(vector<int> pesos, int N, int max_permitido) {
    int sol = 0;
    sort(pesos.begin(), pesos.end(), greater<int>());
    int contMin = N - 1;
    
    for(int i = 0; i<=contMin; i++){
        if(i != contMin && pesos[i] + pesos[contMin] <= max_permitido){
            contMin--;            
        }
        sol++;
    }

    return sol;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int max_permitido, N;
    cin >> max_permitido >> N;

    vector<int> pesos(N);
    for (int i = 0; i < N; i++) {
        cin >> pesos[i];
    }

    if (!std::cin) {
        return false;
    }  // fin de la entrada

    // resolver el caso posiblemente llamando a otras funciones
    cout << telesilla(pesos, N, max_permitido) << "\n";
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
