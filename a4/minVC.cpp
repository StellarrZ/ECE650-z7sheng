#include "a4.hpp"

#include <sstream>
#include <vector>
// defined std::unique_ptr
#include <memory>
// defines Var and Lit
#include "minisat/core/SolverTypes.h"
// defines Solver
#include "minisat/core/Solver.h"


// solve and output a mini-vertex-cover
int minvc(bool **matrix, unsigned v) {
    std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());

    unsigned i, j, p, q = 0;
    unsigned cnt = 0;
    std::vector< std::vector<Minisat::Lit> > lv(1);
    Minisat::vec<Minisat::Lit> cl;  // to storage a clause

    // test size of k increasingly
    for (unsigned k = 1; k < v; k++) {
        lv.resize(k);
        // initialize atoms
        for (j = 0; j < k; j++) {
            for (i = 0; i < v; i++) {
                lv[j].push_back( Minisat::mkLit(solver->newVar()) );
            }
        }

        // k clauses
        for (j = 0; j < k; j++) {
            // x_1,j + x_2,j + ... + x_v,j
            for (i = 0; i < v; i++) {
                cl.push(lv[j][i]);
            }
            solver->addClause(cl);
            cl.clear();
        }

        if (k > 1) {
            // v * C(k,2) clauses
            for (i = 0; i < v; i++) {
                // !x_i,j + !x_i,q
                for (j = 0; j < k; j++) {
                    for (q = j + 1; q < k; q++) {
                        solver->addClause(~lv[j][i], ~lv[q][i]);
                    }
                }
            }
        }

        // k * C(v,2) clauses
        for (j = 0; j < k; j++) {
            // !x_i,j + !x_p,j
            for (i = 0; i < v; i++) {
                for (p = i + 1; p < v; p++) {
                    solver->addClause(~lv[j][i], ~lv[j][p]);
                }
            }
        }

        // |E| clauses
        for (i = 0; i < v - 1; i++) {
            for (p = i + 1; p < v; p++) {
                if (matrix[i][p]) {
                    // (x_i,1 + x_i,2 + ... + x_i,k) + (x_p,1 + x_p,2 + ... + x_p,k) 
                    for (j = 0; j < k; j++) {
                        cl.push(lv[j][i]);
                        cl.push(lv[j][p]);
                    }
                    solver->addClause(cl);
                    cl.clear();
                }
            }
        }
        
        // if true then min = k
        if (solver->solve()) {
            cnt = 0;
            // output vertices ascendingly
            for (i = 0; i < v; i++) {
                for (j = 0; j < k; j++) {
                    if (solver->modelValue(lv[j][i]) == Minisat::l_True) {
                        if (cnt++ != 0) {
                            std::cout << " ";
                        }
                        std::cout << i + 1;
                        // if true then already output k vertices
                        if (cnt == k) {
                            std::cout << std::endl;
                            return 0;
                        }
                        else {
                            break;
                        }
                    }
                }
            }
        }
        else {
            lv.clear();
            solver.reset(new Minisat::Solver());
        } 
    }

    // abnormal
    return 1;
}