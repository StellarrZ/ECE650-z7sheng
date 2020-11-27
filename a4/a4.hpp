#pragma once

/** 
 * Implements MiniSat SAT solver to solve minimal Vertex Cover problem.
 * MiniSat SAT solver available at https://github.com/agurfinkel/minisat
 * Input represents an undirected graph.
 * Output a valid minimal Vertex Cover of the given graph.
 * Returns 0 if output successfully.
 * Returns 1 if unexpected happened.
 */
int minvc(bool **matrix, unsigned v);