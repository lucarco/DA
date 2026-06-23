
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <fstream>
#include <iostream>
#include <queue>
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
10 6 5 6
50 13
68 55
81 16
93 43
98 36
3 60
6 47
32 53
45 86
51 94
61 83
0 0 0 0


SALIDA
3



*/

int bfs(int N, int K, const vector<int>& salto) {
    int destino = N * N;
    vector<int> distancia(destino + 1, -1);
    queue<int> cola;
    distancia[1] = 0;
    cola.push(1);

    while (!cola.empty()) {
        int v = cola.front();
        cola.pop();

        int d = 1;
        while (d <= K && v + d <= destino) {
            int w = v + d;

            if (salto[w] != -1) {  // se ha topado con el principio de una S o una E y se va al final (por eso tbn se va a meter en el siguiente if)
                w = salto[w];
            }

            if (distancia[w] == -1) {  // No se ha topado con ninguna S o E, o se ha metido en el anterior if y ahora siq está en -1
                distancia[w] = distancia[v] + 1;
                if (w == destino) {
                    // sol = min(sol, distancia[w]); -->  No es necesario ya que estás en búsquda en anchura
                    return distancia[w];
                }
                cola.push(w);
            }

            ++d;
        }
    }

    return -1;  // por seguridad (aunque el enunciado garantiza alcanzabilidad)
}

bool resuelveCaso() {
    int N, K, S, E;
    cin >> N >> K >> S >> E;
    if (!cin || (N == 0 && K == 0 && S == 0 && E == 0)) return false;

    int N2 = N * N;
    vector<int> salto(N2 + 1, -1);

    for (int i = 0; i < S; ++i) {
        int a, b;
        cin >> a >> b;  // serpientes
        salto[a] = b;
    }

    for (int i = 0; i < E; ++i) {
        int a, b;
        cin >> a >> b;  // escaleras
        salto[a] = b;
    }

    cout << bfs(N, K, salto) << "\n";
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
