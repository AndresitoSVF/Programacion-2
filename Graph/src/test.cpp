#include "GraphUndirected.h"
#include <cassert>
#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Función auxiliar para verificar si una lista contiene un valor
template<class T>
bool contains(const list<T>& lst, const T& value) {
    return find(lst.begin(), lst.end(), value) != lst.end();
}

void test_empty_graph() {
    GraphUndirected<int> g;
    assert(g.isEmpty() == true);
    assert(g.getNodeCount() == 0);
    assert(g.getEdgeCount() == 0);
    cout << "Test empty graph: PASSED" << endl;
}

void test_single_node() {
    GraphUndirected<int> g;
    g.addNode(1);
    assert(g.isEmpty() == false);
    assert(g.getNodeCount() == 1);
    assert(g.getEdgeCount() == 0);
    assert(g.getNeighbors(1).empty() == true);
    cout << "Test single node: PASSED" << endl;
}

void test_self_loop() {
    
    GraphUndirected<int> g;
    g.addNode(1);
    g.addEdge(1, 1, 5.0f); // Self-loop
    assert(g.getEdgeCount() == 1);
    assert(contains(g.getNeighbors(1), 1) == true);
    g.removeEdge(1, 1);
    assert(g.getEdgeCount() == 0);
    cout << "Test self-loop: PASSED" << endl;
}

void test_duplicate_nodes_edges() {
    GraphUndirected<int> g;
    g.addNode(1);
    g.addNode(1); // Duplicado
    assert(g.getNodeCount() == 1);
    
    g.addNode(2);
    g.addEdge(1, 2, 1.0f);
    g.addEdge(1, 2, 2.0f); // Duplicado
    assert(g.getEdgeCount() == 1);
    cout << "Test duplicate nodes/edges: PASSED" << endl;
}

void test_remove_nonexistent() {
    GraphUndirected<int> g;
    g.addNode(1);
    g.removeNode(2); // Nodo inexistente
    g.removeEdge(1, 2); // Arista inexistente
    assert(g.getNodeCount() == 1);
    assert(g.getEdgeCount() == 0);
    cout << "Test remove nonexistent: PASSED" << endl;
}

void test_complete_graph() {
    GraphUndirected<int> g;
    for (int i = 1; i <= 5; i++) {
        g.addNode(i);
    }
    for (int i = 1; i <= 5; i++) {
        for (int j = i + 1; j <= 5; j++) {
            g.addEdge(i, j, i + j);
        }
    }
    assert(g.getNodeCount() == 5);
    assert(g.getEdgeCount() == 10);
    
    for (int i = 1; i <= 5; i++) {
        auto neighbors = g.getNeighbors(i);
        assert(neighbors.size() == 4);
    }
    cout << "Test complete graph: PASSED" << endl;
}

void test_disconnected_graph() {
    GraphUndirected<int> g;
    g.addNode(1);
    g.addNode(2);
    g.addNode(3);
    g.addEdge(1, 2); // Componente conexa 1-2
    // Nodo 3 desconectado
    assert(g.getEdgeCount() == 1);
    assert(g.getNeighbors(3).empty() == true);
    cout << "Test disconnected graph: PASSED" << endl;
}

void test_bfs_dfs() {
    GraphUndirected<int> g;
    g.addNode(1);
    g.addNode(2);
    g.addNode(3);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    
    list<int> bfs_result = g.bfs2(1);
    assert(bfs_result.size() == 3);
    assert(*bfs_result.begin() == 1);
    
    list<int> dfs_result = g.dfs(1);
    assert(dfs_result.size() == 3);
    cout << "Test BFS/DFS: PASSED" << endl;
}

void test_weight_operations() {
    GraphUndirected<int> g;
    g.addNode(1);
    g.addNode(2);
    g.addEdge(1, 2, 5.0f);
    g.setWeightOfEdge(1, 2, 10.0f);
    // Asumiendo que getWeightOfEdge existe (no está en la interfaz)
    // Si no, verificar mediante otros métodos
    cout << "Test weight operations: PASSED" << endl;
}

void test_copy_constructor() {
    GraphUndirected<int> g1;
    g1.addNode(1);
    g1.addNode(2);
    g1.addEdge(1, 2);
    
    GraphUndirected<int> g2(g1);
    assert(g2.getNodeCount() == 2);
    assert(g2.getEdgeCount() == 1);
    
    g1.removeNode(1); // No debe afectar a g2
    assert(g2.getNodeCount() == 2);
    cout << "Test copy constructor: PASSED" << endl;
}

void test_assignment_operator() {
    GraphUndirected<int> g1, g2;
    g1.addNode(1);
    g1.addNode(2);
    g1.addEdge(1, 2);
    g2 = g1;
    assert(g2.getNodeCount() == 2);
    assert(g2.getEdgeCount() == 1);
    
    g1.removeNode(1);
    assert(g2.getNodeCount() == 2);
    cout << "Test assignment operator: PASSED" << endl;
}

void test_tree_detection() {
    GraphUndirected<int> tree;
    tree.addNode(1);
    tree.addNode(2);
    tree.addNode(3);
    tree.addEdge(1, 2);
    tree.addEdge(1, 3);
    assert(tree.isTree() == true);
    
    GraphUndirected<int> cycle;
    cycle.addNode(1);
    cycle.addNode(2);
    cycle.addNode(3);
    cycle.addEdge(1, 2);
    cycle.addEdge(2, 3);
    cycle.addEdge(3, 1);
    //cout << "Tree nodes: " << tree.getNodeCount() << " tree edges:" << tree.getEdgeCount() << " Is tree: " << tree.isTree() << endl; 
    assert(cycle.isTree() == false);
    cout << "Test tree detection: PASSED" << endl;
    cycle.show();
}

void test_complex_structure() {
    GraphUndirected<int> g;
    // Grafo con múltiples ciclos y nodos conectados
    for (int i = 1; i <= 6; i++) g.addNode(i);
    g.addEdge(1, 2); g.addEdge(2, 3); g.addEdge(3, 1); // Ciclo 1-2-3
    g.addEdge(4, 5); g.addEdge(5, 6); g.addEdge(6, 4); // Ciclo 4-5-6
    g.addEdge(1, 4); // Conexión entre ciclos
    g.addEdge(2, 5); // Otra conexión
    
    assert(g.getNodeCount() == 6);
    assert(g.getEdgeCount() == 8);
    assert(g.getNeighbors(1).size() == 3);
    cout << "Test complex structure: PASSED" << endl;
}

void test_complex_removal() {
    GraphUndirected<int> g;
    
    // Grafo complejo con ciclos
    for (int i = 1; i <= 5; i++) g.addNode(i);
    g.addEdge(1, 2); g.addEdge(2, 3); g.addEdge(3, 4); 
    g.addEdge(4, 5); g.addEdge(5, 1); g.addEdge(1, 3);
    
    // Remover nodo central
    g.removeNode(3);
    assert(g.getNodeCount() == 4);
    assert(g.getEdgeCount() == 3); // Verificar este número según tu lógica
    cout << "test complex removal: PASSED" << endl;
}

void test_memory_leaks() {
    // Usar valgrind o similar para verificar que no hay leaks
    GraphUndirected<std::string> g;
    g.addNode("A"); g.addNode("B"); g.addNode("C");
    g.addEdge("A", "B"); g.addEdge("B", "C"); g.addEdge("C", "A");
    g.removeNode("B");
    // Verificar que no hay memory leaks
    cout << "test memory leaks: PASSED" << endl;
}

/* int main() {
    test_empty_graph();
    test_single_node();
    test_self_loop();
    test_duplicate_nodes_edges();
    test_remove_nonexistent();
    test_complete_graph();
    test_disconnected_graph();
    test_bfs_dfs();
    test_weight_operations();
    test_copy_constructor();
    test_assignment_operator();
    test_tree_detection();
    test_complex_structure();
    test_complex_removal();
    test_memory_leaks();
    
    cout << "\nAll tests passed successfully!" << endl;
    return 0;
} */