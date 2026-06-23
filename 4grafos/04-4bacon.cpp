
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

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
6
AlgunosHombresBuenos 4 TomCruise JackNicholson DemiMoore KevinBacon
RainMan 3 DustinHoffman TomCruise ValeriaGolino
Apolo13 4 TomHanks KevinBacon EdHarris KathleenQuinlan
MejorImposible 4 JackNicholson HelenHunt GregKinnear CubaGoodingJr
LoQueLaNocheEsconde 4 TyeSheridan AnaDeArmas JohnLeguizamo HelenHunt
ExperimentoIndie 3 SarahDavis JohnDoe MichaelAnderson
7
TomCruise
DustinHoffman
TomHanks
HelenHunt
AnaDeArmas
KevinBacon
JohnDoe

SALIDA
TomCruise 1
DustinHoffman 2
TomHanks 1
HelenHunt 2
AnaDeArmas 3
KevinBacon 0
JohnDoe INF
---


*/
class CaminoMasCorto {
  public:
    CaminoMasCorto(Grafo const& g, int s) : visit(g.V(), false),
                                            dist(g.V()),
                                            s(s) {
        bfs(g);
    }
    // ¿hay camino del origen a v?
    bool hayCamino(int v) const {
        return visit[v];
    }  // número de aristas entre s y v
    int distancia(int v) const {
        return dist[v];
    }

  private:
    std::vector<bool> visit;  // visit[v] = ¿hay camino de s a v?
    std::vector<int> dist;    // dist[v] = aristas en el camino s-v más corto
    int s;
    void bfs(Grafo const& g) {
        std::queue<int> q;
        dist[s] = 0;
        visit[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int w : g.ady(v)) {
                if (!visit[w]) {
                    dist[w] = dist[v] + 1;
                    visit[w] = true;
                    q.push(w);
                }
            }
        }
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int P;
    cin >> P;
    Grafo g(1000);
    int nextId = 0;
    unordered_map<string, int> stringToId;
    stringToId["KevinBacon"] = nextId++;
    if (!std::cin)  // fin de la entrada
        return false;
    for (int i = 0; i < P; i++) {
        string aux;
        cin >> aux;
        int actores;
        cin >> actores;
        int peli[actores];
        for (int j = 0; j < actores; j++) {
            string nombre;
            cin >> nombre;
            if (stringToId.find(nombre) == stringToId.end()) {
                stringToId[nombre] = nextId++;
            }
            peli[j] = stringToId[nombre];
        }
        for (int j = 0; j < actores; j++) {
            for (int k = j + 1; k < actores; k++) {
                g.ponArista(peli[j], peli[k]);
            }
        }
    }
    // resolver el caso posiblemente llamando a otras funciones
    int resolver;
    cin >> resolver;
    string res[resolver];
    for (int i = 0; i < resolver; i++) {
        cin >> res[i];
    }
    CaminoMasCorto c(g, 0);
    for (int i = 0; i < resolver; i++) {
        if (c.hayCamino(stringToId[res[i]])) {
            cout << res[i] << " " << c.distancia(stringToId[res[i]]) << "\n";
        } else {
            cout << res[i] << " INF\n";
        }
    }
    // escribir la solución
    cout <<"---\n";

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
