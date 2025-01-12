#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Graph.h"

// Pruebas unitarias para la clase Graph, donde se prueba la funcionalidad básica, la lectura y escritura de archivos y la creación de super source/sink
void testBasicOperations() {
    Graph g;
    
    // Test addEdge y getCapacity
    g.addEdge(0, 1, 10);
    assert(g.getCapacity(0, 1) == 10);
    assert(g.getCapacity(1, 0) == 0);
    
    // Test resize automático
    g.addEdge(5, 3, 15);
    assert(g.size() >= 6);
    assert(g.getCapacity(5, 3) == 15);
    
    // Test getAdj
    const auto& adj0 = g.getAdj(0);
    assert(std::find(adj0.begin(), adj0.end(), 1) != adj0.end());
    
    const auto& adj5 = g.getAdj(5);
    assert(std::find(adj5.begin(), adj5.end(), 3) != adj5.end());
    
    // Test updateCapacity
    g.updateCapacity(0, 1, 5);
    assert(g.getCapacity(0, 1) == 5);
    assert(g.getCapacity(1, 0) == 5);
    
    std::cout << "Pruebas básicas completadas exitosamente\n";
}

// Pruebas de lectura y escritura de archivos
void testFileIO() {
    {
        // Crear archivo de prueba
        std::ofstream testFile("test_graph.txt");
        testFile << "0 2\n";
        testFile << "1 3\n";
        testFile << "0 1 10\n";
        testFile << "0 3 5\n";
        testFile << "2 1 15\n";
        testFile << "2 3 10\n";
    }
    // Leer archivo de prueba
    Graph g;
    bool success = g.readFromFile("test_graph.txt");
    assert(success);
    // Verificar que los datos se hayan leído correctamente
    assert(g.getCapacity(0, 1) == 10);
    assert(g.getCapacity(0, 3) == 5);
    assert(g.getCapacity(2, 1) == 15);
    assert(g.getCapacity(2, 3) == 10);
    assert(g.size() >= 4);
    
    std::cout << "Pruebas de E/S de archivo completadas exitosamente\n";
    std::remove("test_graph.txt");
}


// Función principal que ejecuta todas las pruebas
int main() {
    try {
        testBasicOperations();
        testFileIO();
        
        std::cout << "¡Todas las pruebas completadas exitosamente!\n";
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error en las pruebas: " << e.what() << std::endl;
        return 1;
    }
}