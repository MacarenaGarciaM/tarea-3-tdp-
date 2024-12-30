#include "MaxFlow.h"
#include <queue>
#include <limits>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

// Estructura para manejar las prioridades (capacidad residual)
struct NodePriority {
    int node;
    int priority;

    bool operator<(const NodePriority& other) const {
        return priority < other.priority;  // Prioridad alta significa mayor capacidad residual
    }
};

bool MaxFlow::bfs() {
    state.resetLevels();
    std::priority_queue<NodePriority> pq;

    // Iniciar BFS desde la fuente
    pq.push({source, std::numeric_limits<int>::max()});
    state.setLevel(source, 0);

    while (!pq.empty()) {
        NodePriority current = pq.top();
        pq.pop();

        int u = current.node;

        for (int v : graph.getAdj(u)) {
            // Considerar solo aristas con capacidad residual positiva y nodos no visitados
            if (state.getLevel(v) == -1 && graph.getCapacity(u, v) > 0) {
                state.setLevel(v, state.getLevel(u) + 1);
                int residualCap = graph.getCapacity(u, v);
                pq.push({v, residualCap});
            }
        }
    }

    // Si no se puede alcanzar el sumidero, no hay más caminos aumentantes
    return state.getLevel(sink) != -1;
}

MaxFlow::MaxFlow(Graph& original, Graph& residual, int s, int t) 
    : graph(residual), originalGraph(original), state(residual.size()), 
      source(s), sink(t), totalFlow(0), executionTime(0.0) {}



int MaxFlow::dfs(int u, int flow) {
    if (u == sink) {
        return flow;  // Se alcanzó el sumidero, devolver flujo
    }

    // Explorar aristas adyacentes
    for (; state.getPointer(u) < graph.getAdj(u).size(); state.incrementPointer(u)) {
        int v = graph.getAdj(u)[state.getPointer(u)];
        int availableCapacity = graph.getCapacity(u, v);

        // Verificar si es posible avanzar
        if (state.getLevel(v) == state.getLevel(u) + 1 && availableCapacity > 0) {
            int pushed = dfs(v, std::min(flow, availableCapacity));
            if (pushed > 0) {
                graph.updateCapacity(u, v, pushed);  // Reducir capacidad y aumentar capacidad residual
        return pushed;
    }
}

    }
    return 0;  // No se encontró un flujo válido
}


void MaxFlow::calculateFlows() {
    sourceFlows.clear();
    sinkFlows.clear();
    
    // Calcular flujos para cada fuente
    for (int src : originalGraph.getSources()) {
        int flow = 0;
        for (int v : originalGraph.getAdj(src)) {
            int origCap = originalGraph.getCapacity(src, v);
            int resCap = graph.getCapacity(src, v);
            if (origCap > 0) {
                flow += (origCap - resCap);
            }
        }
        if (flow > 0) {
            sourceFlows.push_back({src, flow});
        }
    }
    
    // Calcular flujos para cada sumidero
    for (int snk : originalGraph.getSinks()) {
        int flow = 0;
        for (int u : originalGraph.getAdj(snk)) {
            int origCap = originalGraph.getCapacity(u, snk);
            int resCap = graph.getCapacity(u, snk);
            if (origCap > 0) {
                flow += (origCap - resCap);
            }
        }
        if (flow > 0) {
            sinkFlows.push_back({snk, flow});
        }
    }
    
    // Ordenar los resultados
    std::sort(sourceFlows.begin(), sourceFlows.end());
    std::sort(sinkFlows.begin(), sinkFlows.end());
}

int MaxFlow::calculate() {
    auto start = std::chrono::high_resolution_clock::now();

    while (bfs()) {
        state.resetPointers();
        while (int flow = dfs(source, numeric_limits<int>::max())) {
            totalFlow += flow;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    executionTime = std::chrono::duration<double, std::milli>(end - start).count();
    
    calculateFlows();
    return totalFlow;
}

void MaxFlow::printResults() const {
    std::cout << "Fuentes:\n";
    for (const auto& [node, flow] : sourceFlows) {
        std::cout << node << " " << flow << "\n";
    }
    
    std::cout << "\nSumideros:\n";
    for (const auto& [node, flow] : sinkFlows) {
        std::cout << node << " " << flow << "\n";
    }
    
    std::cout << "\nFlujo Total: " << totalFlow << "\n";
    std::cout << "Tiempo: " << executionTime << " [ms]\n";
}