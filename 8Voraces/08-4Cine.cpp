
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
09:30 90
12:00 80
16:00 120
17:30 100
3
10:30 90
16:00 110
12:00 70
2
10:30 90
12:10 70
0


SALIDA
3
2
2

*/

struct tPeli {
    int comienzo;
    int duracion;
    int fin;
};

bool operator<(tPeli a, tPeli b) {
    return a.fin < b.fin;
}

int vorazPelis(vector<tPeli>& pelis, int N) {
    int sol = 1;                             // se ve minimo una peli
    sort(pelis.begin(), pelis.end());  // se ordena de antes a dps de q termina
    int termina = pelis[0].fin + 10;          // 10 minutos libre de ir a por palomitas y tal
    for (int i = 1; i < N; i++) {
        if(termina <= pelis[i].comienzo){
            termina = pelis[i].fin + 10;
            sol++;
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
    vector<tPeli> pelis(N);
    for (int i = 0; i < N; i++) {
        int h, min, duracion;
        char aux;
        cin >> h >> aux >> min >> duracion;
        int fin = h * 60 + min + duracion;
        int comienzo = h * 60 + min;
        pelis[i] = {comienzo, duracion, fin};
    }
    // resolver el caso posiblemente llamando a otras funciones

    // escribir la solución
    cout << vorazPelis(pelis, N) << "\n";

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
