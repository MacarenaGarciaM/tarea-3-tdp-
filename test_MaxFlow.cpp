#include "MaxFlow.h"
#include <cassert>
#include <iostream>

void test_SimpleMaxFlow() {
    // Crear el grafo original y residual
    Graph original(3);
    original.addEdge(0, 1, 5);  // Fuente (0) -> Nodo intermedio (1)
    original.addEdge(1, 2, 3);  // Nodo intermedio (1) -> Sumidero (2)

    // Crear una copia del grafo original como grafo residual
    Graph residual = original;

    // Configurar fuente y sumidero
    int source = 0;
    int sink = 2;

    // Crear instancia de MaxFlow
    MaxFlow maxFlow(original, residual, source, sink);

    // Calcular flujo máximo
    int totalFlow = maxFlow.calculate();

    // Verificar el flujo máximo esperado
    assert(totalFlow == 3);  // El flujo máximo está limitado por la capacidad más baja (1 -> 2, cap = 3)

    // Imprimir resultados
    std::cout << "Test SimpleMaxFlow passed! Total flow: " << totalFlow << "\n";
}

int main() {
    test_SimpleMaxFlow();
    return 0;
}
