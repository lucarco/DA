
/*@ <answer>
 *
 * Nombre y Apellidos: Lucas Arranz Corral
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

ENTRADA

2
1234 200
9000 300
5
2
1111 100
9999 1000
9
0


SALIDA
1234
9000
1234
1234
9000
---
1111
1111
1111
1111
1111
1111
1111
1111
1111
---


*/
struct tMensaje {
    int id;
    int tiempo_restante;
    int periodo_inicial;
};

bool operator>(tMensaje a, tMensaje b) {
    if (a.tiempo_restante == b.tiempo_restante) return a.id < b.id;
    return a.tiempo_restante < b.tiempo_restante;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;

    if (n == 0) return false;

    // resolver el caso posiblemente llamando a otras funciones
    PriorityQueue<tMensaje, greater<tMensaje>> mensajes1;
    PriorityQueue<tMensaje, greater<tMensaje>> mensajes2;

    for (int i = 0; i < n; i++) {
        tMensaje aux;
        cin >> aux.id >> aux.periodo_inicial;
        aux.tiempo_restante = aux.periodo_inicial;
        mensajes1.push(aux);
    }
    // escribir la solución

    int k, clk = 5000, i = 0;
    cin >> k;



    while (k > 0) {
        if (i % 2 == 0) {  // para el i == 0 y pares pasa de la cola 1 a la 2
            for (int i = 0; i < n; i++) {
                tMensaje aux = mensajes1.top();
                aux.tiempo_restante -= clk;
                mensajes2.push(aux);
                mensajes1.pop();
            }
            while (!mensajes2.empty() &&  mensajes2.top().tiempo_restante <= 0 && k > 0) {
                tMensaje aux = mensajes2.top();
                mensajes2.pop();
                cout << aux.id << "\n";
                aux.tiempo_restante += aux.periodo_inicial;
                mensajes2.push(aux);
                k--;
            }
        } else {  // para el i impar pasa de la cola 2 a la 1
            for (int i = 0; i < n; i++) {
                tMensaje aux = mensajes2.top();
                aux.tiempo_restante -= clk;
                mensajes1.push(aux);
                mensajes2.pop();
            }
            while (!mensajes1.empty() && mensajes1.top().tiempo_restante <= 0 && k > 0) {
                tMensaje aux = mensajes1.top();
                mensajes1.pop();
                cout << aux.id << "\n";
                aux.tiempo_restante += aux.periodo_inicial;
                mensajes1.push(aux);
                k--;
            }
        }
        i++;
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
