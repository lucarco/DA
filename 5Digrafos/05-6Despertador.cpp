/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <limits>
#include <algorithm>
#include<unordered_map>
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

struct hora {
    int horas;
    int minutos;
    int index;
};

bool operator <(hora a, hora b) {
    return a.horas < b.horas || a.horas == b.horas && a.minutos < b.minutos;
}


const int MAX = 10000;
const int INF = 1000000000;

int aMinutos(int h, int m) {
    return h * 60 + m;
}

int adyacente(hora v, hora avanza) {
    return ((v.horas + avanza.horas) % 24) * 60 + (v.minutos + avanza.minutos) % 60;
}

int distanciaCircular(int a, int b) {
    int diff = abs(a - b);
    return min(diff, 1440 - diff);
}

int distanciaAdelante(int origen, int destino) {
    return (destino - origen + 1440) % 1440;
}

pair<hora, int> bfs(hora origen, hora destino, const vector<hora> &avanzar) {
    if (origen.horas == destino.horas && origen.minutos == destino.minutos) return { destino, 0 };
    vector<int> distancia(1440, INF);
    int o = origen.horas * 60 + origen.minutos;
    int d = destino.horas * 60 + destino.minutos;
    int horaMasCercana = o;
    distancia[o] = 0;
    int cont = 1;
    queue<hora> cola; cola.push(origen);
    while (!cola.empty()) {
        auto v = cola.front(); cola.pop();
        int hv = v.horas * 60 + v.minutos;
        int distMejor = distanciaCircular(horaMasCercana, d);
        int distV = distanciaCircular(hv, d);

        if (distV < distMejor) {
            horaMasCercana = hv;
        }
        else if (distV == distMejor) {
            // Criterio 2 (Empate): La hora que despierte "antes" (menor valor numérico)
            if (distanciaAdelante(hv, d) < distanciaAdelante(horaMasCercana, d)) {
                horaMasCercana = hv;
            }
        }
        for (int i = 0; i < 2; ++i) {
            int hw = adyacente(v, avanzar[i]);
            hora w;
            w.horas = hw / 60;
            w.minutos = hw % 60;
            if (distancia[hw] == INF) {


                distancia[hw] = distancia[hv] + 1;
                if (w.horas == destino.horas && w.minutos == destino.minutos) return { destino, distancia[hw] };
                else cola.push(w);
            }
        }
    }

    hora sol;
    sol.horas = horaMasCercana / 60;
    sol.minutos = horaMasCercana % 60;

    return { sol, distancia[horaMasCercana] };
}

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {

    // leer los datos de la entrada

    hora h1, h2;
    char aux;

    cin >> h1.horas;
    cin >> aux;
    cin >> h1.minutos;

    cin >> h2.horas;
    cin >> aux;
    cin >> h2.minutos;


    if (!std::cin)  // fin de la entrada
        return false;

    hora avanzar1, avanzar2;
    vector<hora> av;

    cin >> avanzar1.horas;
    cin >> avanzar1.minutos;

    cin >> avanzar2.horas;
    cin >> avanzar2.minutos;

    av.push_back(avanzar1);
    av.push_back(avanzar2);

    auto sol = bfs(h1, h2, av);

    if (sol.first.horas == h2.horas && sol.first.minutos == h2.minutos) cout << sol.second;
    else {
        if (sol.first.horas < 10) cout << "0";
        cout << sol.first.horas;
        cout << ":";
        if (sol.first.minutos < 10) cout << "0";
        cout << sol.first.minutos << " " << sol.second;
    }
    cout << "\n";
    // resolver el caso posiblemente llamando a otras funciones

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