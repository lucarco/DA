
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


Entrada de ejemplo
3
1 11:00 90
1 12:30 90
1 12:45 60
3
1 11:00 90
1 12:45 60
1 11:00 180
2
2 12:00 80
1 20:00 80
0

Salida de ejemplo
150
180
160





*/
struct tPeli {
    int comienzo;
    int fin;
    int valor;
};

bool operator<(tPeli p1, tPeli p2) {
    return p1.fin < p2.fin;
}
bool resuelveCaso() {
    // leer los datos de la entrada
    int N;
    cin >> N;

    if (N == 0)
        return false;

    vector<tPeli> pelis(N);
    int dia, h, min, duracion, comienzo, fin;
    char aux;
    for (int i = 0; i < N; i++) {
        cin >> dia >> h >> aux >> min >> duracion;
        comienzo = 24 * 60 * (dia - 1) + h * 60 + min;
        fin = comienzo + duracion + 10;
        pelis[i] = {comienzo, fin, duracion};
    }

    // resolver el caso posiblemente llamando a otras funciones

    sort(pelis.begin(), pelis.end());

    for (int i = 1; i < N; i++) {
        int ver_anteriores = 0;

        tPeli busca;
        busca.fin = pelis[i].comienzo;  // el comparador operator< se fija en el fin;

        // búsqueda binaria, devuelve el primero estrictamente mayor
        auto it = upper_bound(pelis.begin(), pelis.begin() + i, busca);
        int index = distance(pelis.begin(), it) - 1;    // resto 1 para quedarme con el <=
        if (index >= 0) {
            ver_anteriores = pelis[index].valor;
        }

        pelis[i].valor = max(ver_anteriores + pelis[i].valor, pelis[i - 1].valor);
    }

    // escribir la solución

    cout << pelis[N - 1].valor << "\n";

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
