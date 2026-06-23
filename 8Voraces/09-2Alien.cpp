
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
1 10 4
2 8
0 5
7 11
5 10
0 3 2
0 1
2 3
0 0 0


SALIDA
2
Imposible

*/
struct tTrabajo {
    int comienzo;
    int fin;
};

bool operator<(tTrabajo a, tTrabajo b) {
    return a.comienzo < b.comienzo;
}
int minTrabajos(vector<tTrabajo>& trabajos, int C, int F, int N) {
    sort(trabajos.begin(), trabajos.end());

    int sol = 0;
    int pos = C;  // Lo que llevamos cubierto
    int i = 0;
    bool encontrado = false;

    if (N == 0) return -1;

    while (pos < F) {
        bool avance = false;
        int fin = pos;

        // buscar el intervalo que empieza <= pos y que más lejos llega
        while (i < N && trabajos[i].comienzo <= pos) {
            fin = max(fin, trabajos[i].fin);
            i++;
            avance = true;
        }

        if (!avance) return -1;

        sol++;      // hemos seleccionado un trabajo (el que llevaba a 'fin')
        pos = fin;  // avanzamos la cobertura

        if (pos >= F) encontrado = true;
    }

    return sol;
}

/*
int minTrabajos(vector<tTrabajo>& trabajos, int C, int F, int N) {
    int sol = 1;
    sort(trabajos.begin(), trabajos.end());
    if(trabajos[0].comienzo > C) return -1;

    int llega_hasta = trabajos[0].fin;
    int i = 1;
    while (llega_hasta < F && i < N ) {
        if (trabajos[i].comienzo > llega_hasta) {   // hay un hueco
            return -1;
        }
        if(trabajos[i].fin > llega_hasta){
            llega_hasta = trabajos[i].fin;
            sol++;
        }
        i++;
    }

    return (llega_hasta < F) ? -1 : sol;     // si no ha llegado hasta F pero ha completado todo N
}
    */
bool resuelveCaso() {
    // leer los datos de la entrada
    int C, F, N;
    cin >> C >> F >> N;  // [C, F) es donde está expuesto el planeta

    if (C == 0 && F == 0 && N == 0) {
        return false;
    }

    vector<tTrabajo> trabajos(N);
    // resolver el caso posiblemente llamando a otras funciones
    for (int i = 0; i < N; i++) {
        int c, f;
        cin >> c >> f;
        trabajos[i] = {c, f};
    }

    // escribir la solución

    int sol = minTrabajos(trabajos, C, F, N);
    if (sol == -1) {
        cout << "Imposible\n";
    } else {
        cout << sol << "\n";
    }

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
