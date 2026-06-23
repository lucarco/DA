
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

// propios o los de las estructuras de datos de clase

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
1 4
6 15
2 10
12 20
2
1 4
4 8
2
1 4
3 8
0

SALIDA
2
2
1


*/
struct tEdificio {
    int comienzo;
    int fin;
};

bool operator<(tEdificio a, tEdificio b) {
    return a.fin < b.fin;
}

int tuneles(vector<tEdificio>& edificios, int N) {
    sort(edificios.begin(), edificios.end());

    int prox_tunel = edificios[0].fin - 1;
    int sol = 1;    // Al menos un tunel es necesario

    for (int i = 1; i < N; i++) {
        if(edificios[i].comienzo > prox_tunel){
            sol++;
            prox_tunel = edificios[i].fin - 1;
        }
    }

    return sol;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N;
    cin >> N;

    if (N == 0) {
        return false;
    }

    vector<tEdificio> edificios(N);
    for (int i = 0; i < N; i++) {
        int comienzo, fin;
        cin >> comienzo >> fin;
        edificios[i] = {comienzo, fin};
    }

    // resolver el caso posiblemente llamando a otras funciones

    // escribir la solución
    cout << tuneles(edificios, N) << "\n";

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
