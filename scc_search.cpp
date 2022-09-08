#include <vector>
#include <set>
#include <algorithm>
#include "graph.h"
#include "scc_search.h"

class SCGSFirstVisitor: public DFSVisitor {
private:
    size_t Counter;
public:
    std::vector<size_t> Values;
    SCGSFirstVisitor(size_t nodeNumber) : Counter(0), Values(nodeNumber) {}
    ~SCGSFirstVisitor(){}

    void StartComponent() override {}
    void EndComponent() override {}
    void StartNode(size_t ind) override {
        Values[ind] = ++Counter;
    }
    void ReturnToNode(size_t ind) override{
        Values[ind] = ++Counter;
    }
    void EndNode(size_t ind) override {}
};


class SCGSSecondVisitor: public DFSVisitor {
public:
    SCGSSecondVisitor() : Components(), currentComponet(){}
    ~SCGSSecondVisitor(){}
    std::set<std::set<size_t>> Components;
    std::set<size_t> currentComponet;

    void StartComponent() override {
        currentComponet.clear();
    }
    void EndComponent() override {
        Components.insert(currentComponet);
    }
    void StartNode(size_t ind) override {
        currentComponet.insert(ind);
    }
    void ReturnToNode(size_t ind) override{}
    void EndNode(size_t ind) override{}
};

std::set<std::set<size_t>> SCGSearch(size_t nodesNumber, const std::vector<std::pair<size_t, size_t>>& edges) {
    /// @brief search of strongly connected components.
    /// @param nodesNumber nodes number
    /// @param edges vector of edges as pair of node ind (first->second) /

    DirectedGraph graph(nodesNumber, edges);
    SCGSFirstVisitor firstVisitor(graph.NodesAmount());
    graph.DFS(firstVisitor);

    std::vector<size_t> order;
    for (size_t i = 0; i < graph.NodesAmount(); i++) {
        order.push_back(i);
    } 
    std::sort(order.begin(), order.end(), [&firstVisitor](size_t i, size_t j){
        return firstVisitor.Values[i] > firstVisitor.Values[j];
        });
    
    SCGSSecondVisitor secondVisitor;
    auto inversedGraph = graph.GetInverseGraph();
    inversedGraph->DFS(secondVisitor, order);
    
    return secondVisitor.Components;
}