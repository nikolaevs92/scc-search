#include <stdexcept>

#include "graph.h"


DirectedGraph::DirectedGraph(size_t nodesNumber, const std::vector<std::pair<size_t, size_t>>& edges) {
    /// @brief construct from given edges
    /// @param nodesNumber number or nodes
    /// @param edges vector, in (i) ind contains indexes of nodes connected by edge from node (i)

    Nodes = std::vector<std::vector<size_t>>(nodesNumber, std::vector<size_t>());
    for (const auto edge : edges) {
        AddEdge(edge.first, edge.second);
    }
}

void DirectedGraph::AddEdge(size_t from, size_t to){
    /// @brief add direct esge (from -> to)
    /// @param from 
    /// @param to 

    if (from >= Nodes.size() || to >= Nodes.size() || from < 0 || to < 0) {
            throw std::invalid_argument("edges should contain integer values from [0:nodesNumber)");
    }
    Nodes[from].push_back(to);
}

DirectedGraph* DirectedGraph::GetInverseGraph() const {
    /// @brief create inversed graph
    /// @return dynamic DirectedGraph, should be deleted in the end
    DirectedGraph* inversed = new DirectedGraph(Nodes.size());
    for (size_t from = 0; from < Nodes.size(); from++) {
        for (const auto to : Nodes[from]) {
            inversed->AddEdge(to, from);
        }
    }
    return inversed;
}

void DirectedGraph::DFS(DFSVisitor& visitor) const{
    /// @brief  depth first search
    /// @param visitor - with StartNode method using when first met of node, ReturnToNode using when recursion return back to node, 
    ///                  and EndNode when finaly leave node, StartComponent and EndComponent method/

    std::vector<bool> visited(Nodes.size(), false);
    for (size_t node = 0; node < Nodes.size(); node++) {
        if (!visited[node]) {
            visitor.StartComponent();
            DFSStep(visitor, node, visited);
            visitor.EndComponent();
        }
    }
}

void DirectedGraph::DFS(DFSVisitor& visitor, const std::vector<size_t>& order) const{
    /// @brief  depth first search with given order of start nodes
    /// @param visitor - with StartNode method using when first met of node, ReturnToNode using when recursion return back to node, 
    ///                  and EndNode when finaly leave node.
    /// @param order - order of start nodes/

    std::vector<bool> visited(Nodes.size(), false);
    for (const auto node : order) {
        if (node < 0 || node >= Nodes.size()) {
            throw std::invalid_argument("order should contain integer values from [0:nodes.size())");
        }
        if (!visited[node]) {
            visitor.StartComponent();
            DFSStep(visitor, node, visited);
            visitor.EndComponent();
        }
    }
}

void DirectedGraph::DFSStep(DFSVisitor& visitor, size_t startNode, std::vector<bool>& visited) const{
    /// @brief  depth first search one tree step
    /// @param visitor - with StartNode method using when first met of node, ReturnToNode using when recursion return back to node, 
    ///                  and EndNode when finaly leave node.
    /// @param visited - vector contained info about visited nodes, true in (i) position if node (i) is visited. 
    ///                    Visited nodes will not visited again/

    visitor.StartNode(startNode);
    visited[startNode] = true;
    for (const auto node : Nodes[startNode]) {
        if (!visited[node]) {
            DFSStep(visitor, node, visited);
            visitor.ReturnToNode(node);
        }
    }
    visitor.EndNode(startNode);
}

size_t DirectedGraph::NodesAmount() const {
    return Nodes.size();
}