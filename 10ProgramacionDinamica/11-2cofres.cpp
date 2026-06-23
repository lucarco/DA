
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

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
210
3
40 5
40 1
25 2
200
5
25 4
50 5
40 4
10 2
70 10
29
1
10 20




SALIDA
7
2
40 5
25 2
---
8
2
25 4
40 4
---
0
0
---

*/

struct tCofre {
    int prof;
    int oro;
};

void reconstruir(Matriz<int>& m, vector<tCofre>& cofre, int T, int N, int oro_max){
    vector<tCofre> sol;
    int cont = 0;

    int i = N, j = T;
    while(oro_max != 0){
        if(m[i][j] != m[i-1][j]){
            oro_max -= cofre[i-1].oro;
            cont++;
            sol.push_back(cofre[i-1]);
            j -= cofre[i-1].prof;
        }
        i--;
    }

    cout << cont<< "\n";
    
    for(tCofre c : sol){
        cout << c.prof/3 << " " << c.oro << "\n";
    }

    cout << "---\n";
    
}

int oroMax(Matriz<int>& m, vector<tCofre>& cofre, int T, int N) {
    for (int i = 1; i < N + 1; i++) {
        for (int j = 1; j < T + 1; j++) {
            m[i][j] = m[i - 1][j];
            if (cofre[i - 1].prof <= j) {
                m[i][j] = max(m[i][j], m[i - 1][j - cofre[i - 1].prof] + cofre[i - 1].oro);
            }
        }
    }
    return m[N][T];
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int T, N;
    cin >> T >> N;

    vector<tCofre> cofre(N);

    for (int i = 0; i < N; i++) {
        int prof, oro;
        cin >> prof >> oro;
        cofre[i] = {prof * 3, oro};
    }

    if (!std::cin) {
        return false;
    }

    // resolver el caso posiblemente llamando a otras funciones
    Matriz<int> m(N + 1, T + 1, 0);
    int oro_max = oroMax(m, cofre, T, N);
    cout << oro_max << "\n";
    reconstruir(m, cofre, T, N, oro_max);
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
