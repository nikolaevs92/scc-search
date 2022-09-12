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
    std::vector<size_t>& Values;
public:
    SCGSFirstVisitor(size_t nodeNumber, std::vector<size_t>& values) : Counter(0), Values(values) {}
    ~SCGSFirstVisitor(){}

    void StartComponent() override {}
    void EndComponent() override {}
    void StartNode(size_t ind) override {
        if(ind >= Values.size()) {
            Values.resize(ind+1, 0);
        }
        Values[ind] = ++Counter;
    }
    void ReturnToNode(size_t ind) override{
        if(ind >= Values.size()) {
            Values.resize(ind+1, 0);
        }
        Values[ind] = ++Counter;
    }
    void EndNode(size_t ind) override {}

    const std::vector<size_t> &GetResultValue() const {
        return Values;
    }    
};


class SCGSSecondVisitor: public DFSVisitor {
private:
    std::set<std::set<size_t>> &Components;
    std::set<size_t> currentComponet;
public:
    SCGSSecondVisitor(std::set<std::set<size_t>> &components) : Components(components), currentComponet(){}
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
// TODO: Upd: Change to pass reference to components object, no coping now. Visitors don't conrol result fully 
// (Its good, because they dount know what we run).
// Still can be better I think.
void SCGSearch(size_t nodesNumber, const std::vector<std::pair<size_t, size_t>>& edges, std::set<std::set<size_t>>& result) {
    /// @brief search of strongly connected components.
    /// @param nodesNumber nodes number
    /// @param edges vector of edges as pair of node ind (first->second) /
    /// @param result for store result components set
    result.clear();

    DirectedGraph graph(nodesNumber, edges);
    std::vector<size_t> Values;
    SCGSFirstVisitor firstVisitor(graph.NodesAmount(), Values);
    graph.DFS(firstVisitor);

    std::vector<size_t> order;
    for (size_t i = 0; i < graph.NodesAmount(); i++) {
        order.push_back(i);
    } 
    std::sort(order.begin(), order.end(), [&Values](size_t i, size_t j){
        return Values[i] > Values[j];
        });
    
    SCGSSecondVisitor secondVisitor(result);
    auto inversedGraph = graph.GetInverseGraph();
    inversedGraph->DFS(secondVisitor, order);
}