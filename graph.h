#pragma once

#include <vector>
#include <memory>


class DFSVisitor {
public:
    virtual void StartComponent() = 0;
    virtual void EndComponent() = 0;
    virtual void StartNode(size_t ind) = 0;
    virtual void ReturnToNode(size_t ind) = 0;
    virtual void EndNode(size_t ind) = 0;
    // ToDO: should add more?
};


class DirectedGraph {
private:
    // TodOo? Maybe Node
    // struct Node {
    //     std::vector<Node*> conections;
    // };

    // bad name
    std::vector<std::vector<size_t>> Nodes;
public:
    DirectedGraph(size_t nodesNumber, const std::vector<std::pair<size_t, size_t>>& edges);
    DirectedGraph(size_t nodesNumber) : Nodes(nodesNumber, std::vector<size_t>()) {}

    // ToDo: maybe return poiner, but leak...
    void AddEdge(size_t from, size_t to);
    std::unique_ptr<DirectedGraph> GetInverseGraph() const;
    void DFS(DFSVisitor& visitor) const;
    void DFS(DFSVisitor& visitor, const std::vector<size_t>& order) const;
    size_t NodesAmount() const;
private:
    void DFSStep(DFSVisitor& visitor, const size_t node, std::vector<bool>& visited) const;
};