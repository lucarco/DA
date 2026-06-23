
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

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
3 2
1 6 10
3 5
1 7 10
8 10
3 8 8 9 20 45 55 90


SALIDA
3
2
4



*/

int parches(vector<int> agujeros, int N, int L) {
    int sol = 1;                       
    int cubreHasta = agujeros[0] + L;  

    for (int i = 1; i < N; i++) {
        if (agujeros[i] > cubreHasta) {
            sol++;                         
            cubreHasta = agujeros[i] + L;  
        }
    }
    return sol;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, L;
    cin >> N >> L;
    vector<int> agujeros(N);

    for (int i = 0; i < N; i++) {
        cin >> agujeros[i];
    }
    if (!std::cin) {  // fin de la entrada
        return false;
    }
    // resolver el caso posiblemente llamando a otras funciones

    cout << parches(agujeros, N, L) << "\n";
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
