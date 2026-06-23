
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
5 4
12 12 12 12 12
13 14 12 10
3 4
13 10 12
15 11 12 14
3 3
10 14 17
6 4 50


SALIDA
3
0
3



*/
int comprar(vector<int>& tallas_necesitadas, vector<int>& tallas_disponibles, int N, int M) {
    int sol = 0;
    sort(tallas_necesitadas.begin(), tallas_necesitadas.end());
    sort(tallas_disponibles.begin(), tallas_disponibles.end());
    int contN = 0, contM = 0;

    while (contN < N && contM < M) {
        if (tallas_necesitadas[contN] > tallas_disponibles[contM]) {
            contM++;
        } else if (tallas_necesitadas[contN] == tallas_disponibles[contM] || tallas_necesitadas[contN] + 1 == tallas_disponibles[contM]) {
            contM++;
            contN++;
            sol++;  // en sol guardo los que encuentro, para despues devolver N - sol
        } else {
            contN++;
        }
    }

    return N - sol;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, M;
    cin >> N >> M;

    vector<int> tallas_necesitadas(N);
    vector<int> tallas_disponibles(M);

    for (int i = 0; i < N; i++) {
        cin >> tallas_necesitadas[i];
    }
    for (int i = 0; i < M; i++) {
        cin >> tallas_disponibles[i];
    }

    if (!std::cin) {  // fin de la entrada
        return false;
    }
    // resolver el caso posiblemente llamando a otras funciones
    cout << comprar(tallas_necesitadas, tallas_disponibles, N, M) << "\n";
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
