
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

#include "EnterosInf.h"
#include "Matriz.h"  // propios o los de las estructuras de datos de clase
#define Infinito 10000

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
1 5 10 50
10 2 5 4
260
3
1 10 100
3 2 2
114
3
10 15 5
2 2 2
20

SALIDA
SI 11
NO
SI 2


*/
struct tMoneda {
    int cantidad;
    int valor;
};

bool operator<(tMoneda m1, tMoneda m2) {
    return m1.valor < m2.valor;
}

// matriz[i][j] = min(matriz[i-1][j] , matriz[i][j - monedas[i-1].valor])
int minMonedas(vector<tMoneda>& monedas, int coche) {
    Matriz<int> matriz(monedas.size() + 1, coche + 1, 0);
    sort(monedas.begin(), monedas.end());
    for (int i = 0; i <= coche; i++) {
        matriz[0][i] = Infinito;
    }

    for (int i = 1; i <= monedas.size(); i++) {
        vector<int> disp(coche + 1, monedas[i - 1].cantidad);
        /*for (int j = 0; j <= coche; j++) {
            cout << disp[j] << " ";
        }*/
        // matriz[i][0] = 0;
        for (int j = 1; j <= coche; j++) {
            if (monedas[i - 1].valor > j) {
                matriz[i][j] = matriz[i - 1][j];
                if (i == 1) matriz[i][j] = 0;
            } else if (disp[j - monedas[i - 1].valor] <= 0) {
                matriz[i][j] = min(matriz[i - 1][j], matriz[i][j - monedas[i - 1].valor] + matriz[i - 1][j] - matriz[i - 1][j - monedas[i - 1].valor]);
                if (matriz[i][j] != matriz[i - 1][j]) {
                    disp[j] = disp[j - monedas[i - 1].valor];
                }
                /*
                if (matriz[i][j] != matriz[i - 1][j]) {
                    matriz[i][j] += matriz[i - 1][j] - matriz[i - 1][j - monedas[i - 1].valor];
                }*/
            } else {
                matriz[i][j] = min(matriz[i - 1][j], matriz[i][j - monedas[i - 1].valor] + 1);
                if (matriz[i][j] != matriz[i - 1][j]) {
                    disp[j] = disp[j - monedas[i - 1].valor] - 1;
                } /*
                 if (matriz[i - 1][j] != matriz[i - 1][j - monedas[i - 1].valor]) {
                     matriz[i][j] += matriz[i - 1][j] - matriz[i - 1][j - monedas[i - 1].valor];
                 }*/
            }
        }
        /* for (int j = 0; j <= coche; j++) {
             cout << disp[j] << " ";
         }*/
    }

    
    for (int i = 0; i <= coche; i++) {
        cout << " " << i;
    }
    cout << "\n";
    for (int i = 0; i <= monedas.size(); i++) {
        for (int j = 0; j <= coche; j++) {
            cout << " " << matriz[i][j];
        }
        cout << "\n";
    }
    return matriz[matriz.numfils() - 1][matriz.numcols() - 1];
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, coche;
    cin >> N;
    vector<tMoneda> monedas(N);

    for (int i = 0; i < N; i++) {
        cin >> monedas[i].valor;
    }
    for (int i = 0; i < N; i++) {
        cin >> monedas[i].cantidad;
    }
    cin >> coche;

    if (!std::cin) {
        return false;
    }
    // resolver el caso posiblemente llamando a otras funciones

    cout << minMonedas(monedas, coche) << "\n";

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
