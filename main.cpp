#include <iostream>
#include <chrono>
#include "Graph.h"
#include "MaxFlow.h"

void displayMenu() {
    std::cout << "\n--- Menu Principal ---\n";
    std::cout << "1. Resolver flujo maximo desde un archivo\n";
    std::cout << "2. Salir\n";
    std::cout << "Seleccione una opcion: ";
}

int main() {
    while (true) {
        displayMenu();
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string filename;
            std::cout << "Ingrese el nombre del archivo de entrada: ";
            std::cin >> filename;

            Graph graph;
            if (!graph.readFromFile(filename)) {
                std::cerr << "Error: No se pudo leer el archivo.\n";
                continue;
            }

            // Crear una copia para el grafo residual
            Graph residualGraph = graph;

            // Obtener super fuente y super sumidero
            int superSource, superSink;
            residualGraph.addSuperSourceSink(superSource, superSink);

            // Calcular y mostrar resultados
            MaxFlow dinic(graph, residualGraph, superSource, superSink);
            dinic.calculate();
            dinic.printResults();
        } else if (choice == 2) {
            std::cout << "Saliendo del programa. Hasta luego!\n";
            break;
        } else {
            std::cerr << "Opcion no valida. Por favor, intente nuevamente.\n";
        }
    }

    return 0;
}
