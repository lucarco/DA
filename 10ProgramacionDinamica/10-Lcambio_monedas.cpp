/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm> // Necesario para min
using namespace std;

#include "Matriz.h"

/*@ <answer>
   Explicación de cambios:
   1. Se define un valor INF para inicializar la matriz (representa "imposible alcanzar esta suma").
   2. Se limita el tamaño de la matriz (columnas) a 'precio + 10000'. No es necesario calcular hasta la 'suma total' de todas las monedas, 
      porque si nos pasamos del precio por más del valor del billete más grande, esa solución nunca será óptima. Esto evita TLE y MLE.
   3. La lógica dentro del bucle elige el mínimo entre "no coger la moneda" (m[i-1][j]) y "cogerla" (m[i-1][j-valor] + 1).
 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

const int INF = 1e9; 

// Estructura para devolver el resultado
struct tSol {
    int pagado;
    int num_monedas;
};

// Función corregida
tSol cambio(const vector<int>& monedas, int precio) {
    // COTA SUPERIOR: 
    // No necesitamos una matriz hasta la suma total de todas las monedas (que puede ser enorme).
    // Solo necesitamos llegar hasta precio + valor_maximo_posible (10000 según enunciado).
    // Esto ahorra mucha memoria y tiempo.
    int max_limite = precio + 10005; 
    
    int N = monedas.size();
    
    // Inicializamos con INF, porque buscamos el MÍNIMO.
    // m[i][j] = mínimo número de monedas usando las primeras i monedas para sumar j.
    Matriz<int> m(N + 1, max_limite, INF);

    // Caso base: Para conseguir suma 0 con 0 monedas, hacen falta 0 monedas.
    for(int i = 0; i <= N; i++) {
        m[i][0] = 0;
    }

    for (int i = 1; i <= N; i++) {
        int valor_moneda = monedas[i - 1]; // Valor de la moneda actual
        
        for (int j = 1; j < max_limite; j++) {
            // Opción 1: No cogemos la moneda actual (copiamos el resultado de arriba)
            m[i][j] = m[i - 1][j];

            // Opción 2: Si cabe la moneda, intentamos cogerla
            if (j >= valor_moneda) {
                // Si la suma restante (j - valor) era posible (no es INF), probamos a sumar 1 moneda
                if (m[i - 1][j - valor_moneda] != INF) {
                    m[i][j] = min(m[i][j], m[i - 1][j - valor_moneda] + 1);
                }
            }
        }
    }

    // BUSCAR LA SOLUCIÓN
    // Recorremos la última fila (usando todas las monedas disponibles)
    // Empezamos desde 'precio' hacia arriba. El primero que no sea INF es la solución.
    // Esto garantiza: 1. Pagar al menos el precio. 2. Pagar lo mínimo posible (por el orden del bucle).
    for (int j = precio; j < max_limite; j++) {
        if (m[N][j] != INF) {
            return {j, m[N][j]};
        }
    }
    
    return {0, 0}; // No debería llegar aquí
}

bool resuelveCaso() {
    int precio, N;
    cin >> precio >> N;
    
    if (!std::cin) return false;

    vector<int> monedas(N);
    // Ya no necesitamos calcular 'col' (suma total) para dimensionar la matriz
    // con precio + 10000 es suficiente.
    for (int i = 0; i < N; i++) {
        cin >> monedas[i];
    }

    tSol solucion = cambio(monedas, precio);
    cout << solucion.pagado << " " << solucion.num_monedas << endl;

    return true;
}
//@ </answer>

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
    // system("PAUSE");
#endif
    return 0;
}