
/*@ <answer>
 *
 * Nombre y Apellidos: Lucas Arranz Corral
 *
 *@ </answer> */


 /*
 ENTRADA:
 4
15 20 25 30
2
1 3
5
16 8 4 4 32
3
2 4 5
0

SALIDA:
15
25
---
8
32
??
---
 
 
 */
#include <iostream>
#include <fstream>
//#include <...>
using namespace std;

#include "TreeSet_AVL.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
   
   // leer los datos de la entrada
   int n, m;
   cin >> n;

   
   if (n == 0)
      return false;
   

   Set<int> arbol;
   int num;
   for(int i = 0; i<n; i++){
      cin >> num;
      arbol.insert(num);
   }
   // resolver el caso posiblemente llamando a otras funciones
   int k;
   cin >>m;
   for(int i = 0; i<m; i++){
      cin >> k;
      cout << arbol.kesimo(k) << "\n";
   }
   
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
