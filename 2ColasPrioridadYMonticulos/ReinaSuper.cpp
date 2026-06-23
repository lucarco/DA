
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
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
2 2
10 5
2 2
5 10
3 2
5 10
0 0

SALIDA
2
1
3

*/

struct caja{
    int id;
    int t;

};

// Comparador: devuelve true si "a" es peor que "b"
bool operator>(caja const& a, caja const& b) {
    if (a.t == b.t) return a.id < b.id; // el de mayor id tiene menos prioridad
    return a.t < b.t;                   // el que tarda más tiene menos prioridad
}

bool resuelveCaso() {
   
   // leer los datos de la entrada
   int n, c;
   cin >> n >> c;

   if (!cin || (n == 0 && c == 0))
      return false;
   
   // resolver el caso posiblemente llamando a otras funciones
   PriorityQueue<caja, greater<caja>> fila;


   for(int i = 0; i < n; i++){
        caja aux({i + 1, 0});
        fila.push(aux);
   }

   for(int i = 0; i < c; i++){
    int cliente;
    cin >> cliente;
    caja cajaPrio = fila.top();
    fila.pop();
    cajaPrio.t += cliente;
    fila.push(cajaPrio);
   }
   // escribir la solución
   caja sol = fila.top();
   cout << sol.id << endl;

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
