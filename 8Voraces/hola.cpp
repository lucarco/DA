#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

/*@ <answer>

La solución consiste en transformar cada zombi en el tiempo que tardará en llegar a la
máquina (tiempo = distancia / velocidad). Si se ordenan estos tiempos de menor a mayor,
siempre será óptimo eliminar primero a los zombis que lleguen antes.

La máquina dispara una pelota cada segundo: en el segundo 0 elimina a un zombi, en el
segundo 1 a otro, etc. Si llega el turno de disparar en el instante i y el zombi que toca
tiene un tiempo de llegada menor o igual que i, significa que ya habría alcanzado la
máquina antes de ser eliminado, por lo que el proceso termina.

Se recorren los tiempos ordenados comprobando si se puede eliminar cada zombi. El número
de zombis eliminados es la solución del caso.

Coste: ordenar los tiempos requiere O(Z log Z), siendo Z ≤ 50.000. El resto es O(Z).

@ </answer> */

int salvar(vector<double>& tiempos, int Z) {
    sort(tiempos.begin(), tiempos.end());
    bool seguir = true;
    int i = 0;

    while (i < Z && seguir) {
        if (tiempos[i] <= i)  // si el zombi llega antes o justo cuando se le dispara → fin
            seguir = false;
        else
            i++;
    }

    return i;
}

bool resuelveCaso() {
    int Z;
    cin >> Z;

    if (!cin) return false;

    vector<double> tiempos(Z);
    vector<int> distancias(Z);
    vector<int> velocidades(Z);

    for (int i = 0; i < Z; i++)
        cin >> distancias[i];

    for (int i = 0; i < Z; i++)
        cin >> velocidades[i];

    for (int i = 0; i < Z; i++)
        tiempos[i] = (double)distancias[i] / velocidades[i];

    cout << salvar(tiempos, Z) << "\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
