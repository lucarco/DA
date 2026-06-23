
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <fstream>
#include <iostream>
#include <string>
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
One Respect Radio_Ga_Ga One Volando_voy Caruso
Respect One Volando_voy Ne_me_quitte_pas Radio_Ga_Ga
Despacito Fiesta_pagana
Grandola_Vila_Morena
Yesterday Macarena Mocatriz Buleria Orobroy Thriller
Macarena Buleria Texas_Hold'em Vagabundo Thriller Bizcochito


SALIDA
Respect One Volando_voy
Macarena Buleria Thriller

*/
string rec_patines(string const& patitos, Matriz<int> const& patin,
                   int i, int j) {
    if (i > j) return {};
    if (i == j) return {patitos[i]};
    if (patitos[i] == patitos[j])
        return patitos[i] + rec_patines(patitos, patin, i + 1, j - 1) + patitos[j];
    else if (patin[i][j] == patin[i + 1][j])
        return rec_patines(patitos, patin, i + 1, j);
    else
        return rec_patines(patitos, patin, i, j - 1);
}

string reconstruir(vector<string> const& lista1, vector<string> const& lista2, Matriz<int> const& m, int i, int j) {
    if (i >= lista1.size() || j >= lista2.size()) {
        return "";
    } else if (lista1[i] == lista2[j]) {
        string siguientes = reconstruir(lista1, lista2, m, i + 1, j + 1);
        if (siguientes.empty()) {
            return lista1[i];
        }
        return lista1[i] + " " + siguientes;
    } else if (m[i][j] == m[i + 1][j]) {
        return reconstruir(lista1, lista2, m, i + 1, j);
    } else {
        return reconstruir(lista1, lista2, m, i, j + 1);
    }
}

int canciones_rec(vector<string> const& v1, vector<string> const& v2, int i, int j, Matriz<int>& m) {
    if (i >= v1.size() || j >= v2.size()) {
        return 0;
    }
    int& res = m[i][j]; 
    if (res == -1) {
        if (v1[i] == v2[j]) {
            res = canciones_rec(v1, v2, i + 1, j + 1, m) + 1;
        } else {
            res = max(canciones_rec(v1, v2, i + 1, j, m),
                      canciones_rec(v1, v2, i, j + 1, m));
        }
    }
    return res;
}
bool resuelveCaso() {
    // leer los datos de la entrada
    vector<string> v1;
    vector<string> v2;

    string linea;
    getline(cin, linea);

    string aux = "";
    for (int i = 0; i < linea.size(); i++) {
        if (linea[i] != ' ') {
            aux += linea[i];
        } else {
            v1.push_back(aux);
            aux = "";
        }
    }
    v1.push_back(aux);

    aux = "";
    getline(cin, linea);

    for (int i = 0; i < linea.size(); i++) {
        if (linea[i] != ' ') {
            aux += linea[i];
        } else {
            v2.push_back(aux);
            aux = "";
        }
    }
    v2.push_back(aux);

    if (!std::cin) {
        return false;
    }

    // resolver el caso posiblemente llamando a otras funciones

    Matriz<int> m(v1.size() + 1, v2.size() + 1, -1);

    // cout << canciones_rec(v1, v2, 0, 0, m) << "\n";
    canciones_rec(v1, v2, 0, 0, m);
    cout << reconstruir(v1, v2, m, 0, 0) << "\n";
    // falta la reconstruccion

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
