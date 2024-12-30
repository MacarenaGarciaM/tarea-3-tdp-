#include "Graph.h"
#include <cassert>
#include <iostream>

void testGraphInitialization() {
    Graph graph(5);

    assert(graph.size() == 5);
    for (int u = 0; u < 5; ++u) {
        for (int v = 0; v < 5; ++v) {
            assert(graph.getCapacity(u, v) == 0);  // Inicialmente todas las capacidades son 0
        }
    }

    std::cout << "testGraphInitialization passed.\n";
}

void testAddEdge() {
    Graph graph(4);
    graph.addEdge(0, 1, 10);
    graph.addEdge(1, 2, 20);
    graph.addEdge(2, 3, 30);

    assert(graph.getCapacity(0, 1) == 10);
    assert(graph.getCapacity(1, 2) == 20);
    assert(graph.getCapacity(2, 3) == 30);

    // Verificar que se actualicen correctamente las listas de adyacencia
    const auto& adj0 = graph.getAdj(0);
    const auto& adj1 = graph.getAdj(1);
    const auto& adj2 = graph.getAdj(2);

    assert(adj0.size() == 1 && adj0[0] == 1);
    assert(adj1.size() == 2 && adj1[0] == 0 && adj1[1] == 2);
    assert(adj2.size() == 2 && adj2[0] == 1 && adj2[1] == 3);

    std::cout << "testAddEdge passed.\n";
}

void testUpdateCapacity() {
    Graph graph(4);
    graph.addEdge(0, 1, 10);
    graph.updateCapacity(0, 1, 5);

    assert(graph.getCapacity(0, 1) == 5);  // Capacidad actualizada correctamente
    assert(graph.getCapacity(1, 0) == 5);  // Capacidad inversa actualizada correctamente

    graph.updateCapacity(1, 0, 2);
    assert(graph.getCapacity(1, 0) == 7);  // Capacidad inversa aumenta correctamente

    std::cout << "testUpdateCapacity passed.\n";
}

void testResize() {
    Graph graph(3);
    graph.addEdge(0, 1, 10);

    graph.addEdge(2, 0, 15);
    graph.addEdge(2, 1, 5);

    graph.addEdge(0, 3, 20);  // Automáticamente se redimensiona

    assert(graph.size() == 4);
    assert(graph.getCapacity(0, 3) == 20);
    assert(graph.getCapacity(3, 0) == 0);  // Capacidad inversa no configurada automáticamente

    const auto& adj3 = graph.getAdj(3);
    assert(adj3.size() == 1 && adj3[0] == 0);

    std::cout << "testResize passed.\n";
}

void testSuperSourceSink() {
    Graph graph(4);
    graph.addEdge(0, 1, 10);
    graph.addEdge(1, 2, 20);
    graph.addEdge(2, 3, 30);

    // Configurar fuentes y sumideros
    graph.addEdge(0, 0, 0); // superedge 
    

    int superSource, superSink;
    graph.addSuperSourceSink(superSource, superSink);

    assert(superSource == 4);
    assert(superSink == 5);

    // Superfuente conectado a todas las fuentes
    assert(graph.getCapacity(superSource, 0) > 0);
    assert(graph.getCapacity(superSource, 0) == 30);  // La capacidad es la suma de las conexiones

    // Supersumidero conectado a todos los sumideros
    assert(graph.getCapacity(3, superSink) > 0);
    assert(graph.getCapacity(3, superSink) == 30);  // La capacidad es la suma de las conexiones

    std::cout << "testSuperSourceSink passed.\n";
}

int main() {
    testGraphInitialization();
    testAddEdge();
    testUpdateCapacity();
    testResize();
    testSuperSourceSink();

    std::cout << "All Graph tests passed successfully.\n";
    return 0;
}
