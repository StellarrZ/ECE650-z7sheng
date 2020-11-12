#pragma once

// Vertex class. Storage distance and predecessor
class Vertex
{
    // distance from source to this vertex
    unsigned distance;
    // predecessor on a path from source
    int predecessor;
public:
    // constructor. Init unsigned dis = -1, pre = 0
    Vertex();
    // returns distance value
    unsigned dis();
    // returns predecessor number
    int pre();
    // set the distance of source vertex to equal 0
    void set();
    // relaxes a edge directly from vertex parent to this vertex
    void relax(int parent, unsigned dpre);
};

/** 
 * Implements Bellman-Ford algorithm to calculate shortest paths 
 * from a given source to other vertices.
 * Pushes output into a stack and records stack-top-index.
 * Returns true if a shortest path is found between source and destination.
 * Returns false if there is no path between source and destination.
 */
bool process (bool **matrix, int v, int sour, int des,
             int *stack, int &top);