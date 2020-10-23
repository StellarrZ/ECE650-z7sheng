// calculate shortest path from source to destination

#include "a2.hpp"

// define Vertex class
Vertex::Vertex() : distance(-2), predecessor(0) {}

unsigned Vertex::dis() { 
    return distance; }
int Vertex::pre() { 
    return predecessor; }
void Vertex::set() {
    distance = 0; }
void Vertex::relax(int parent, unsigned dpre) {
    if (distance > dpre + 1) {
        distance = dpre + 1;
        predecessor = parent;
    }
}

bool process (bool **matrix, int v, int sour, int des,
             int *stack, int &top) {
    // Bellman-Ford initialize
    Vertex node[v];
    node[sour - 1].set();

    // Bellman-Ford iterate
    int k, i, j;
    for (k = 1; k < v; k++) 
        for (i = 0; i < v; i++) 
            for (j = 0; j < v; j++) 
                if (matrix[i][j]) 
                    node[j].relax(i + 1, node[i].dis()); 

    const unsigned max_value = -2;
    // backtracking a shortest path and push
    if (node[des - 1].dis() < max_value) {
        k = des;
        stack[0] = des;
        while (node[k - 1].pre() != 0) {
            k = node[k - 1].pre();
            stack[++top] = k;
        }
        return true;
    }
    // unreachable
    return false;
}