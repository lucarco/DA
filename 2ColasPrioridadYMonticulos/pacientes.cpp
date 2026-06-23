
/*@ <answer>
 *
 * Nombre y Apellidos: Lucas Arranz Corral
 *
 *@ </answer> */

#include <fstream>
#include <iostream>
// #include <...>
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
4
I Luis 1000
I Eva 2000
A
A
9
I Alberto 4000
I Pepe 3000
A
I Rosa 2000
I Laura 5000
A
I Sara 3000
A
A
0




SALIDA
Eva
Luis
---
Alberto
Laura
Pepe
Sara
---

*/

struct tPaciente {
    int id;
    string nombre;
    int gravedad;
};

bool operator>(tPaciente a, tPaciente b) {
    if (a.gravedad == b.gravedad) return a.id < b.id;
    return a.gravedad > b.gravedad;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;

    if (n == 0) return false;

    // resolver el caso posiblemente llamando a otras funciones
    PriorityQueue<tPaciente, greater<tPaciente>> pacientes;

    for (int i = 0; i < n; i++) {
        char IA;
        cin >> IA;
        if (IA == 'I') {
            tPaciente aux;
            aux.id = i;
            cin >> aux.nombre >> aux.gravedad;
            pacientes.push(aux);
        } else {
            cout << pacientes.top().nombre << "\n";
            pacientes.pop();
        }
    }

    // escribir la solución
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
