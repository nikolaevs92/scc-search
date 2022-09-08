#include <vector>
#include <set>
#include <algorithm>
#include <memory>

#include "graph.h"
#include "scc_search.h"

class SCGSFirstVisitor: public DFSVisitor {
private:
    size_t Counter;
    // TODO: change name?
    std::vector<size_t> Values;
public:
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

    const std::vector<size_t> &GetResultValue() const {
        return Values;
    }
    std::vector<size_t> && GetResultValues() {
        return std::move(Values);
    }
    
};


class SCGSSecondVisitor: public DFSVisitor {
private:
    std::set<std::set<size_t>> Components;
    std::set<size_t> currentComponet;
public:
    SCGSSecondVisitor() : Components(), currentComponet(){}
    ~SCGSSecondVisitor(){}

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
    
    const std::set<std::set<size_t>> &GetResulComponents() const {
        return Components;
    }
    std::set<std::set<size_t>> && GetResulComponents() {
        return std::move(Components);
    }
    
};

//TODO: pointer? this should work correctly and clean, we return a copy of reference to class member, but coping not obvious or optimaized
// But maybe we should copy it explisit, make new object inside func, and return smart pointer.
// Or maybe SCGSSecondVisitor should keep pointer to needed result (Components), created in func,
// it will ruin incapsulation, but we dount need a copying
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
        return firstVisitor.GetResultValue()[i] > firstVisitor.GetResultValue()[j];
        });
    
    SCGSSecondVisitor secondVisitor;
    auto inversedGraph = graph.GetInverseGraph();
    inversedGraph->DFS(secondVisitor, order);
    
    return secondVisitor.GetResulComponents();
}