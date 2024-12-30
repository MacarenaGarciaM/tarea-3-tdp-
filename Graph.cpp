#include "Graph.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>  // Para debugging

void Graph::addEdge(int u, int v, int cap) {
    // Asegurarse de que el grafo tenga el tamaño adecuado
    int maxNode = std::max(u, v);
    if (maxNode >= vertices) {
        resize(maxNode + 1);
    }
    
    capacity[u][v] += cap;
    
    // Verificar si v ya está en la lista de adyacencia de u
    if (std::find(adj[u].begin(), adj[u].end(), v) == adj[u].end()) {
        adj[u].push_back(v);
    }
    if (std::find(adj[v].begin(), adj[v].end(), u) == adj[v].end()) {
        adj[v].push_back(u);
    }
}

int Graph::getCapacity(int u, int v) const {
    if (u < vertices && v < vertices) {
        return capacity[u][v];
    }
    return 0;
}

const vector<int>& Graph::getAdj(int u) const {
    return adj[u];
}

void Graph::updateCapacity(int u, int v, int flow) {
    if (u < vertices && v < vertices) {
        capacity[u][v] -= flow;
        capacity[v][u] += flow;
    }
}

int Graph::size() const {
    return vertices;
}

bool Graph::readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
        return false;
    }

    // Limpiar el grafo actual
    clear();
    
    std::string line;
    
    // Leer fuentes
    if (!std::getline(file, line)) {
        std::cerr << "Error leyendo fuentes" << std::endl;
        return false;
    }
    
    std::istringstream iss(line);
    int node;
    while (iss >> node) {
        sources.push_back(node);
    }
    
    // Leer sumideros
    if (!std::getline(file, line)) {
        std::cerr << "Error leyendo sumideros" << std::endl;
        return false;
    }
    
    iss.clear();
    iss.str(line);
    while (iss >> node) {
        sinks.push_back(node);
    }
    
    // Primera pasada para encontrar el tamaño necesario
    int u, v, cap;
    int maxVertex = -1;
    while (file >> u >> v >> cap) {
        maxVertex = std::max(maxVertex, std::max(u, v));
    }
    
    if (maxVertex < 0) {
        std::cerr << "No se encontraron aristas en el archivo" << std::endl;
        return false;
    }
    
    // Redimensionar el grafo
    resize(maxVertex + 1);
    
    // Volver al inicio para leer las aristas
    file.clear();
    file.seekg(0);
    std::getline(file, line); // Saltar línea de fuentes
    std::getline(file, line); // Saltar línea de sumideros
    
    // Leer y agregar las aristas
    while (file >> u >> v >> cap) {
        addEdge(u, v, cap);
    }
    
    std::cout << "Grafo leído exitosamente:\n";
    std::cout << "Vertices: " << vertices << "\n";
    std::cout << "Fuentes: " << sources.size() << "\n";
    std::cout << "Sumideros: " << sinks.size() << "\n";
    
    return true;
}

void Graph::addSuperSourceSink(int& superSource, int& superSink) {
    superSource = vertices;
    superSink = vertices + 1;
    resize(vertices + 2);
    
    // Conectar superfuente a cada fuente original
    for (int src : sources) {
        int totalCap = 0;
        for (int v : adj[src]) {
            totalCap += capacity[src][v];
        }
        if (totalCap > 0) {
            addEdge(superSource, src, totalCap);
        }
    }
    
    // Conectar cada sumidero original al supersumidero
    for (int snk : sinks) {
        int totalCap = 0;
        for (int u : adj[snk]) {
            totalCap += capacity[u][snk];
        }
        if (totalCap > 0) {
            addEdge(snk, superSink, totalCap);
        }
    }
}