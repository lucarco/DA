/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits> // Para INT_MIN

using namespace std;

#include "Matriz.h"

/*@ <answer>
 
 El problema se resuelve mediante Programación Dinámica.
 Se trata de encontrar el alineamiento con puntuación máxima (Needleman-Wunsch).
 
 Estado:
    dp[i][j] = Puntuación máxima alineando el sufijo A[i..] con el sufijo B[j..].
 
 Transiciones (para cada estado i, j tenemos 3 opciones):
    1. Alinear A[i] con B[j]: coste[A[i]][B[j]] + dp[i+1][j+1]
    2. Alinear A[i] con Hueco: coste[A[i]]['-'] + dp[i+1][j]
    3. Alinear Hueco con B[j]: coste['-'][B[j]] + dp[i][j+1]
 
 Caso base:
    Cuando i == N y j == M, puntuación es 0.
    Si i == N pero j < M, forzamos huecos para el resto de B.
    Si j == M pero i < N, forzamos huecos para el resto de A.
 
 Coste:
    O(N*M) donde N y M son las longitudes de las cadenas.
 
 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

// Valor centinela para marcar celdas no calculadas.
// Debe ser menor que cualquier puntuación posible (aprox -50000 * 1000)
const int INF = -1e9; 

int getIndex(char c) {
    switch (c) {
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
        case '-': return 4;
        default: return 4;
    }
}

int secuencias_rec(string const& s1, string const& s2, int i, int j, 
                   Matriz<int> const& costes, Matriz<int>& m) {
    
    // 1. Caso Base: Ambas cadenas terminadas
    if (i == s1.size() && j == s2.size()) {
        return 0;
    }

    // 2. Comprobar memoización
    if (m[i][j] != INF) {
        return m[i][j];
    }

    int mejor_score = INF;

    // Opción 1: Alinear carácter de s1 con carácter de s2 (MATCH / MISMATCH)
    if (i < s1.size() && j < s2.size()) {
        int coste = costes[getIndex(s1[i])][getIndex(s2[j])];
        int val = secuencias_rec(s1, s2, i + 1, j + 1, costes, m);
        if (val != INF) mejor_score = max(mejor_score, val + coste);
    }

    // Opción 2: Alinear carácter de s1 con un hueco en s2 (GAP en s2)
    if (i < s1.size()) {
        int coste = costes[getIndex(s1[i])][getIndex('-')];
        int val = secuencias_rec(s1, s2, i + 1, j, costes, m);
        if (val != INF) mejor_score = max(mejor_score, val + coste);
    }

    // Opción 3: Alinear hueco en s1 con carácter de s2 (GAP en s1)
    if (j < s2.size()) {
        int coste = costes[getIndex('-')][getIndex(s2[j])];
        int val = secuencias_rec(s1, s2, i, j + 1, costes, m);
        if (val != INF) mejor_score = max(mejor_score, val + coste);
    }

    // Guardar y devolver
    return m[i][j] = mejor_score;
}

void resuelveCaso() {
    Matriz<int> costes(5, 5);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> costes[i][j];
        }
    }

    int pares;
    cin >> pares;
    for (int k = 0; k < pares; k++) {
        string s1, s2;
        cin >> s1 >> s2;

        // IMPORTANTE: Tamaño size + 1 para incluir los casos base
        // Inicializamos con INF porque las puntuaciones pueden ser negativas (-1 es válido)
        Matriz<int> m(s1.size() + 1, s2.size() + 1, INF);

        cout << secuencias_rec(s1, s2, 0, 0, costes, m) << "\n";
    }
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}