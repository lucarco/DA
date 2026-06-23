
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

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
2 4 6
1 8
4 10
3 6 14 6
0
2 7
1 4
0
4 4

Salida de ejemplo
FALLO EN EL SISTEMA
3 12
---
CORRECTO
1 10
3 10
2 14
---
ABANDONEN INMEDIATAMENTE LA BASE
---





*/
struct tBateria {
    int id;
    int duracion;
    int sumar_duracion;
};

bool operator<(tBateria b1, tBateria b2) {
    if (b1.duracion == b2.duracion) {
        return b1.id < b2.id;
    }
    return b1.duracion < b2.duracion;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int B;
    cin >> B;

    if (!std::cin)  // fin de la entrada
        return false;

    // resolver el caso posiblemente llamando a otras funciones
    PriorityQueue<tBateria, less<tBateria>> pq;
    int aux;
    for (int i = 0; i < B; i++) {
        cin >> aux;
        pq.push({i + 1, aux, aux});
    }

    int R, Z, T;
    cin >> R;
    vector<tBateria> repuesto(R);
    for (int i = 0; i < R; i++) {
        cin >> aux;
        repuesto[i] = {B + i + 1, aux, aux};
    }

    cin >> Z >> T;
    R = 0;

    tBateria principal;
    while (!pq.empty() && pq.top().duracion <= T) {
        principal = pq.top();
        pq.pop();
        if (principal.sumar_duracion - Z > 0) {
            principal.sumar_duracion -= Z;
            pq.push({principal.id, principal.duracion + principal.sumar_duracion, principal.sumar_duracion});
        } else if (R < repuesto.size()) {
            repuesto[R].duracion += principal.duracion;
            pq.push(repuesto[R]);
            R++;
        }
    }

    // escribir la solución
    if (pq.empty()) {
        cout << "ABANDONEN INMEDIATAMENTE LA BASE\n";
    } else {
        if (pq.size() == B) {
            cout << "CORRECTO\n";
        } else {
            cout << "FALLO EN EL SISTEMA\n";
        }
        tBateria b;
        while (!pq.empty()) {
            b = pq.top();
            pq.pop();
            cout << b.id << " " << b.duracion << "\n";
        }
    }
    cout << "---\n";
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
