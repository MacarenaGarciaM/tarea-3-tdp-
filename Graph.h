#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
using namespace std;
// Clase para representar un grafo con capacidades en las aristas y nodos fuente y sumidero 


class Graph {
// Atributos
private:
    int vertices; // Número de nodos
    vector<vector<int>> capacity; // Capacidad de las aristas
    vector<vector<int>> adj; // Lista de adyacencia
    vector<int> sources; // Nodos fuente
    vector<int> sinks; // Nodos sumidero

public:
    // Constructor modificado para inicializar correctamente
    Graph(int n = 0) : vertices(n) {
        resize(n);
    }
    
    // Constructor de copia explícito
    Graph(const Graph& other) : 
        vertices(other.vertices),
        capacity(other.capacity),
        adj(other.adj),
        sources(other.sources),
        sinks(other.sinks) {}
    
    void addEdge(int u, int v, int cap);
    int getCapacity(int u, int v) const;
    const vector<int>& getAdj(int u) const;
    void updateCapacity(int u, int v, int flow);
    int size() const;
    void addSuperSourceSink(int& superSource, int& superSink);
    
    bool readFromFile(const std::string& filename);
    const vector<int>& getSources() const { return sources; }
    const vector<int>& getSinks() const { return sinks; }
    
private:
    void resize(int newSize) {
        vertices = newSize;
        capacity.resize(vertices, vector<int>(vertices, 0));
        adj.resize(vertices);
    }
    
    void clear() {
        capacity.clear();
        adj.clear();
        sources.clear();
        sinks.clear();
        vertices = 0;
    }
};

#endif // GRAPH_H