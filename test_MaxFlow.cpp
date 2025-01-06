#include <iostream>
#include <cassert>
#include "Graph.h"
#include "MaxFlow.h"

class MaxFlowTests {
private:
    void assertEqual(int actual, int expected, const std::string& message) {
        if (actual != expected) {
            std::cerr << "Fallo: " << message << "\n";
            std::cerr << "  Valor actual: " << actual << "\n";
            std::cerr << "  Valor esperado: " << expected << "\n";
            assert(false);
        }
    }

public:
    void testBasicMaxFlow() {
        std::cout << "Ejecutando testBasicMaxFlow...\n";
        Graph graph(4);

        graph.addEdge(0, 1, 10);
        graph.addEdge(1, 2, 5);
        graph.addEdge(2, 3, 10);

        Graph residualGraph = graph;
        MaxFlow maxFlow(graph, residualGraph, 0, 3);

        int flow = maxFlow.calculate();
        assertEqual(flow, 5, "El flujo máximo básico falló.");
        std::cout << "  testBasicMaxFlow pasado.\n";
    }

    void testMultiplePaths() {
    std::cout << "Ejecutando testMultiplePaths...\n";
    Graph graph(4);

    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 10);
    graph.addEdge(1, 3, 5);
    graph.addEdge(2, 3, 15);

    Graph residualGraph = graph;
    MaxFlow maxFlow(graph, residualGraph, 0, 3);

    int flow = maxFlow.calculate();
    assertEqual(flow, 15, "El flujo máximo con múltiples caminos falló.");  // Cambiado de 20 a 15
    std::cout << "  testMultiplePaths pasado.\n";
}

    void testDisconnectedGraph() {
        std::cout << "Ejecutando testDisconnectedGraph...\n";
        Graph graph(4);

        graph.addEdge(0, 1, 10);
        // Nodos 2 y 3 no conectados a 0 o 1

        Graph residualGraph = graph;
        MaxFlow maxFlow(graph, residualGraph, 0, 3);

        int flow = maxFlow.calculate();
        assertEqual(flow, 0, "El flujo máximo en grafo desconectado falló.");
        std::cout << "  testDisconnectedGraph pasado.\n";
    }

    void runTests() {
        std::cout << "=== Ejecutando pruebas para MaxFlow ===\n";

        testBasicMaxFlow();
        testMultiplePaths();
        testDisconnectedGraph();

        std::cout << "=== Todas las pruebas pasaron correctamente ===\n";
    }
};

int main() {
    MaxFlowTests tests;
    tests.runTests();
    return 0;
}
