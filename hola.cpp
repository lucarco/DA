#include <bits/stdc++.h>
using namespace std;

class Grafo {
    vector<vector<int>> _ady;
public:
    Grafo(int V = 0) : _ady(V) {}

    void ponArista(int v, int w) {
        if (v >= (int)_ady.size() || w >= (int)_ady.size())
            throw std::domain_error("Índice de vértice fuera de rango");
        _ady[v].push_back(w);
        _ady[w].push_back(v);
    }

    void addVertice() { _ady.push_back({}); }

    int numVertices() const { return _ady.size(); }

    const vector<vector<int>>& ady() const { return _ady; }
};

// ------------------------------------------------------------
// getId: devuelve el ID numérico asociado a un nombre de actor
// Si no existe, lo crea y añade un vértice al grafo
// ------------------------------------------------------------
int getId(const string& nombre,
          unordered_map<string, int>& stringToId,
          vector<string>& idToString,
          Grafo& g) {
    auto it = stringToId.find(nombre);
    if (it == stringToId.end()) {
        int id = g.numVertices();
        stringToId[nombre] = id;
        idToString.push_back(nombre);
        g.addVertice();
        return id;
    }
    return it->second;
}

// ------------------------------------------------------------
int main() {
    int P;
    cin >> P;

    unordered_map<string, int> stringToId;
    vector<string> idToString;
    Grafo g;

    for (int i = 0; i < P; i++) {
        string titulo;
        int actores;
        cin >> titulo >> actores;

        vector<int> ids;
        ids.reserve(actores);

        for (int j = 0; j < actores; j++) {
            string nombre;
            cin >> nombre;
            int id = getId(nombre, stringToId, idToString, g);
            ids.push_back(id);
        }

        // Conectar todos los actores de la misma película
        for (int a = 0; a < actores; ++a)
            for (int b = a + 1; b < actores; ++b)
                g.ponArista(ids[a], ids[b]);
    }

    // Mostrar lista de adyacencia (prueba)
    for (int i = 0; i < g.numVertices(); ++i) {
        cout << idToString[i] << ": ";
        for (int w : g.ady()[i])
            cout << idToString[w] << " ";
        cout << "\n";
    }

    return 0;
}
