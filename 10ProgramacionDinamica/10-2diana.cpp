
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
100 5
10 15 20 25 30
8 3
1 4 6
25 2
8 12

SALIDA
4: 25 25 25 25
2: 4 4
Imposible

*/


struct tCasilla {
    EntInf num_dardos;
    int puntuacion_act;
};

bool operator<(tCasilla c1, tCasilla c2) {
    return c1.num_dardos < c2.num_dardos;
}

void mostrarSolucion(int valor, int S, vector<int>& sectores, Matriz<tCasilla>& matriz) {
    cout << matriz[sectores.size()][valor].num_dardos << ":";
    EntInf i = matriz[sectores.size()][valor].num_dardos;
    int fila = sectores.size(), col = valor;
    while (i > 0) {
        if (matriz[fila][col].num_dardos == matriz[fila - 1][col].num_dardos) {
            fila--;
        } else {
            cout << " " << sectores[fila - 1];
            col -= sectores[fila - 1];
            i = i + (-1);
        }
    }
}

void dardosMinimos(int valor, int S, vector<int>& sectores) {
    EntInf sol = Infinito;
    Matriz<tCasilla> matriz(sectores.size() + 1, valor + 1, {Infinito, 0});
    matriz[0][0].num_dardos = 0;
    for (int i = 1; i <= sectores.size(); i++) {
        matriz[i][0].num_dardos = 0;
        for (int j = 1; j <= valor; j++) {
            if (sectores[i - 1] > j) {
                matriz[i][j] = matriz[i - 1][j];
            } else {
                tCasilla aux = matriz[i][j - sectores[i - 1]];
                aux.num_dardos = aux.num_dardos + 1;
                aux.puntuacion_act += sectores[i - 1];
                matriz[i][j] = min(matriz[i - 1][j], aux);
            }
        }
       // cout << "Con el numero: " << sectores[i - 1] << " lleva una puntacion de " << matriz[i][valor].puntuacion_act << endl;
        //if (matriz[i][valor].puntuacion_act == valor) {
            //cout << "Estamos con el numero: " << sectores[i - 1] << "con la solucion anterior: " << sol << endl;
            sol = min(sol, matriz[i][valor].num_dardos);
            //cout << "Nueva solucion: " << sol << endl;
        //}
    }

    if (sol != Infinito)
        mostrarSolucion(valor, S, sectores, matriz);
    else
        cout << "Imposible";
    cout << "\n";
}


bool resuelveCaso() {
    // leer los datos de la entrada
    int valor, S;
    cin >> valor >> S;
    vector<int> sectores(S);

    for (int i = 0; i < S; i++) {
        cin >> sectores[i];
    }

    if (!std::cin) {
        return false;
    }

    // resolver el caso posiblemente llamando a otras funciones
    dardosMinimos(valor, S, sectores);
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
