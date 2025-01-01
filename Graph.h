#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
using namespace std;

class Graph {
private:
    int vertices;
    vector<vector<int>> capacity;
    vector<vector<int>> adj;
    vector<int> sources;
    vector<int> sinks;

public:
    // Constructor por defecto
    Graph(int n = 0) : vertices(n) {
        resize(n);
    }
    
    // Constructor de copia mejorado
    Graph(const Graph& other) : 
        vertices(other.vertices),
        capacity(other.capacity),
        adj(other.adj),
        sources(other.sources),
        sinks(other.sinks) {
        // Asegurarse de que todas las estructuras tengan el tamaño correcto
        resize(vertices);
    }
    
    // Operador de asignación
    Graph& operator=(const Graph& other) {
        if (this != &other) {
            vertices = other.vertices;
            capacity = other.capacity;
            adj = other.adj;
            sources = other.sources;
            sinks = other.sinks;
            resize(vertices);
        }
        return *this;
    }

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
        if (newSize < 0) newSize = 0;
        vertices = newSize;
        
        // Redimensionar la matriz de capacidades
        capacity.resize(vertices);
        for (auto& row : capacity) {
            row.resize(vertices, 0);
        }
        
        // Redimensionar las listas de adyacencia
        adj.resize(vertices);
    }
    
    void clear() {
        vertices = 0;
        capacity.clear();
        adj.clear();
        sources.clear();
        sinks.clear();
    }
};

#endif // GRAPH_H