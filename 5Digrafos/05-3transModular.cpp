#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
/*


ENTRADA
7 2 6
2
3 1
2 2
5 1 0
2
2 1
3 1
10 2 1
1
2 0

SALIDA
1
2
-1



*/
const int INF = 1000000000;  // ∞

int bfs(int origen, int destino, const vector<int>& a, const vector<int>& b, int M, int N) {
    if (origen == destino) return 0;
    vector<int> distancia(M, INF);
    distancia[origen] = 0;
    queue<int> cola;
    cola.push(origen);

    while (!cola.empty()) {
        int v = cola.front();
        cola.pop();

        for (int i = 0; i < N; ++i) {
            int w = (a[i] * v + b[i]) % M;
            if (distancia[w] == INF) {
                distancia[w] = distancia[v] + 1;
                if (w == destino)
                    return distancia[w];
                cola.push(w);
            }
        }
    }
    return -1;
}

bool resuelveCaso() {
    int M, S, T;
    if (!(cin >> M >> S >> T)) return false;

    int N;
    cin >> N;
    vector<int> a(N), b(N);
    for (int i = 0; i < N; i++) cin >> a[i] >> b[i];

    cout << bfs(S, T, a, b, M, N) << "\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
