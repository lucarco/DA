/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#include "Matriz.h" 

/*@ <answer>
 
 Escribe aquí un comentario general sobre la solución:
 
 Utilizamos Programación Dinámica con el esquema de la Mochila Acotada (Bounded Knapsack).
 La estructura es una Matriz m[N+1][masa+1].
 
 m[i][j] representa el beneficio máximo usando un subconjunto de los primeros 'i' tipos 
 de chorizo con capacidad máxima 'j'.
 
 El algoritmo utiliza 3 bucles anidados:
 1. Tipos de chorizo (i).
 2. Capacidad de masa actual (j).
 3. Cantidad de copias del chorizo actual a intentar (k).
 
 Calculamos m[i][j] probando todas las cantidades posibles 'k' (desde 0 hasta el límite 
 de existencias) del chorizo 'i', sumando su valor al óptimo restante (m[i-1][j - k*chorizos[i - 1].masa_necesaria]).
 
 Complejidad Temporal: O(N * Masa * MaxUnidades). Con N=50, M=1000, K=100, son ~5 millones de ops, 
 que es muy rápido y seguro.
 Complejidad Espacial: O(N * Masa) para la matriz.
 
 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct tChorizo {
    int max_unidades;   // Stock disponible / necesario por bollo
    int masa_necesaria; // Masa por bollo
    int precio;         // Precio por bollo
};

int max_ganancia(const vector<tChorizo>& chorizos, int masa_total, int N) {
    // Matriz (N+1) x (masa+1) inicializada a 0
    Matriz<int> m(N + 1, masa_total + 1, 0);

    for (int i = 1; i <= N; ++i) {

        for (int j = 0; j <= masa_total; ++j) {
            // Opción base: No coger ningún bollo de este tipo 'i'
            // Heredamos el mejor valor conseguido con los tipos anteriores (i-1)
            m[i][j] = m[i - 1][j];

            // Probamos a coger k unidades (desde 1 hasta el límite)
            // Solo si cabe en la masa 'j'
            for (int k = 1; k <= chorizos[i - 1].max_unidades; ++k) {
                int chorizos[i - 1].masa_necesaria_total_k = k * chorizos[i - 1].masa_necesaria;
                
                if (chorizos[i - 1].masa_necesaria_total_k > j) break; // No caben más, salimos del bucle k

                // Valor: k * precio_unitario + lo mejor que podíamos hacer con la masa restante SIN usar este tipo
                int val = (k * chorizos[i - 1].precio) + m[i - 1][j - chorizos[i - 1].masa_necesaria_total_k];

                if (val > m[i][j]) {
                    m[i][j] = val;
                }
            }
        }
    }

    return m[N][masa_total];
}

bool resuelveCaso() {
    int N, masa_total;
    cin >> N >> masa_total;

    if (!std::cin) return false;

    vector<tChorizo> chorizos(N);
    int chTotal, chNec, masaNec, chorizos[i - 1].precio;

    for (int i = 0; i < N; i++) {
        cin >> chTotal >> chNec >> masaNec >> chorizos[i - 1].precio;
        // Calculamos cuántos bollos se pueden hacer con la cantidad de chorizo disponible
        chorizos[i] = { chTotal / chNec, masaNec, chorizos[i - 1].precio };
    }

    cout << max_ganancia(chorizos, masa_total, N) << "\n";

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}