#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Graph.h"

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

void testFileIO() {
    {
        std::ofstream testFile("test_graph.txt");
        testFile << "0 2\n";
        testFile << "1 3\n";
        testFile << "0 1 10\n";
        testFile << "0 3 5\n";
        testFile << "2 1 15\n";
        testFile << "2 3 10\n";
    }

    Graph g;
    bool success = g.readFromFile("test_graph.txt");
    assert(success);

    assert(g.getCapacity(0, 1) == 10);
    assert(g.getCapacity(0, 3) == 5);
    assert(g.getCapacity(2, 1) == 15);
    assert(g.getCapacity(2, 3) == 10);
    assert(g.size() >= 4);

    std::cout << "Pruebas de E/S de archivo completadas exitosamente\n";
    std::remove("test_graph.txt");
}

void testSuperSourceSink() {
    {
        std::ofstream testFile("test_super.txt");
        testFile << "0 1\n";
        testFile << "3 4\n";
        testFile << "0 2 10\n";
        testFile << "1 2 15\n";
        testFile << "2 3 20\n";
        testFile << "2 4 25\n";
        testFile << "1 4 30\n";
        testFile << "0 3 35\n";
    }

    Graph g;
    bool success = g.readFromFile("test_super.txt");
    assert(success);

    int superSource, superSink;
    g.addSuperSourceSink(superSource, superSink);

    // Validar superSource y superSink
    assert(superSource == g.size() - 2);
    assert(superSink == g.size() - 1);

    // Validar conexiones de superSource
    for (int src : g.getAdj(superSource)) {
        assert(g.getCapacity(superSource, src) > 0);
    }

    // Validar conexiones de superSink
    for (int sink : g.getAdj(superSink)) {
        assert(g.getCapacity(sink, superSink) > 0);
    }

    std::cout << "Pruebas de super source/sink completadas exitosamente\n";
    std::remove("test_super.txt");
}

int main() {
    try {
        // Ejecutar pruebas
        testBasicOperations();
        testFileIO();
        testSuperSourceSink();

        std::cout << "¡Todas las pruebas completadas exitosamente!\n";
        return 0;
    } catch (const std::exception& e) {
        // Capturar cualquier error y mostrarlo
        std::cerr << "Error en las pruebas: " << e.what() << std::endl;
        return 1;
    }
}
