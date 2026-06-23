#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <cmath>
#include <climits>
using namespace std;

struct tHora {
    int hora;
    int min;
    int distancia;
};

tHora bfs(tHora ini, tHora fin, const vector<tHora>& opc) {
    bool visitado[24][60] = {false};
    tHora mejor = ini;
    int minDiff = INT_MAX;
    ini.distancia = 0;
    queue<tHora> cola;
    cola.push(ini);
    visitado[ini.hora][ini.min] = true;
    
    while (!cola.empty()) {
        tHora v = cola.front();
        cola.pop();
        
        // Comprobar si es mejor candidato
        int diff = abs((fin.hora * 60 + fin.min) - (v.hora * 60 + v.min));
        if (diff < minDiff || (diff == minDiff && (v.hora * 60 + v.min) < (mejor.hora * 60 + mejor.min))) {
            minDiff = diff;
            mejor = v;
        }
        
        // Generar nuevos estados
        for (int i = 0; i < 2; i++) {
            int nuevaHora = (v.hora + opc[i].hora) % 24;
            int nuevoMin = (v.min + opc[i].min) % 60;
            
            if (!visitado[nuevaHora][nuevoMin]) {
                visitado[nuevaHora][nuevoMin] = true;
                tHora nuevo = {nuevaHora, nuevoMin, v.distancia + 1};
                cola.push(nuevo);
                
                // Si encontramos la hora exacta, la devolvemos inmediatamente
                if (nuevaHora == fin.hora && nuevoMin == fin.min) {
                    return nuevo;
                }
            }
        }
    }
    
    return mejor;
}

bool resuelveCaso() {
    string auxIni, auxFin;
    cin >> auxIni >> auxFin;
    if (!cin) return false;
    
    tHora ini, fin;
    vector<tHora> opc(2);
    
    // Parsear horas inicial y final
    ini.hora = stoi(auxIni.substr(0, 2));
    ini.min = stoi(auxIni.substr(3, 2));
    fin.hora = stoi(auxFin.substr(0, 2));
    fin.min = stoi(auxFin.substr(3, 2));
    
    // Leer desplazamientos de botones
    cin >> opc[0].hora >> opc[0].min >> opc[1].hora >> opc[1].min;
    
    tHora sol = bfs(ini, fin, opc);
    
    if (sol.hora == fin.hora && sol.min == fin.min) {
        cout << sol.distancia << "\n";
    } else {
        if (sol.hora < 10) cout << "0";
        cout << sol.hora << ":";
        if (sol.min < 10) cout << "0";
        cout << sol.min << " " << sol.distancia << "\n";
    }
    
    return true;
}

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