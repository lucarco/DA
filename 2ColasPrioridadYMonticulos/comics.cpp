
/*@ <answer>
 *
 * Nombre y Apellidos: Lucas Arranz Corral
 *
 *@ </answer> */

#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

// #include "..."  // propios o los de las estructuras de datos de clase

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
5 5 2 3 1 20
7 9 12 44 13 4 7 8
3
3 4 5 6
2 3 2
4 11 8 9 7

SALIDA
6
1

*/
bool resuelveCaso() {
    // leer los datos de la entrada

    if (!std::cin)  // fin de la entrada
        return false;

    // resolver el caso posiblemente llamando a otras funciones
    int n;
    cin >> n;
    cin.ignore();  // commo voy a hacer un getline que le den al salto de linea

    vector<stack<int>> pilas(n);
    int min = 10000;

    for (int i = 0; i < n; i++) {
        string linea;
        getline(cin, linea);

        int num = 0;
        bool dentroNumero = false;

        for (char c : linea) {
            if (isdigit(c)) {
                num = num * 10 + (c - '0');
                dentroNumero = true;
            } else if (dentroNumero) {
                if (num < min) min = num;
                pilas[i].push(num);
                num = 0;
                dentroNumero = false;
            }
        }
    }
        // Mostrar las pilas
    for (int i = 0; i < n; i++) {
        cout << "Pila " << i << ": ";
        stack<int> copia = pilas[i]; // copiamos la pila
        while (!copia.empty()) {
            cout << copia.top() << " ";
            copia.pop();
        }
        cout << endl;
    }
    // escribir la solución
    /*
    int sol = 0;
    bool encontrado = false;

    while (!encontrado) {
        int colaQuitar = 0;
        int minAct = pilas[0].top();

        for (int i = 0; i < n; i++) {
            if (pilas[i].top() < minAct) {
                colaQuitar = i;
                minAct = pilas[i].top();
            }
        }

        pilas[colaQuitar].pop();
        if (minAct == min) {
            encontrado = true;
        }
        sol++;
    }

    cout << sol << "\n";
    */

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
