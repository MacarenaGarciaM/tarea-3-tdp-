#ifndef MAXFLOW_H
#define MAXFLOW_H

#include "Graph.h"
#include "State.h"
#include <chrono>
#include <utility>
#include <vector>

class MaxFlow {
private:
    Graph& graph;
    Graph& originalGraph;
    State state;
    int source;
    int sink;
    int totalFlow;
    double executionTime;
    std::vector<std::pair<int, int>> sourceFlows;  // (node, flow)
    std::vector<std::pair<int, int>> sinkFlows;    // (node, flow)

    bool bfs();
    int dfs(int u, int flow);
    void calculateFlows();

public:
    MaxFlow(Graph& original, Graph& residual, int s, int t);
    int calculate();  // Antes era maxFlow()
    void printResults() const;
};

#endif // MAXFLOW_H