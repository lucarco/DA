
/*@ <answer>
 *
 * Nombre y Apellidos: Lucas Arranz Corral
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
//#include <...>
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
4 4
8 5 5 2
6 4
8 5 5 2
7 4
8 5 5 2

SALIDA
8
5
4

*/
struct instrumento{
   int personas;
   int atriles;
};

// La division de enteros va regular
bool operator>(const instrumento& a, const instrumento& b) {
   return (long long)a.personas * b.atriles > (long long)b.personas * a.atriles;
}

bool resuelveCaso() {
   
   // leer los datos de la entrada
   int p, n;
   cin >> p >> n;
   
   if (!std::cin)  // fin de la entrada
      return false;
   
   // resolver el caso posiblemente llamando a otras funciones
   PriorityQueue<instrumento, greater<instrumento>> musicos;

   for(int i = 0; i< n; i++){
      instrumento aux;
      cin >> aux.personas;
      aux.atriles = 1;
      musicos.push(aux);
   }
   // escribir la solución

   for(int i = 0; i < p - n; i++){
      instrumento aux = musicos.top();
      aux.atriles++;
      musicos.pop();
      musicos.push(aux);
   }


   instrumento aux = musicos.top();
   int sol = (aux.personas + aux.atriles - 1) / aux.atriles; // división techo
   cout << sol << "\n";

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
