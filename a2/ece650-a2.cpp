// Compile with c++ ece650-a2cpp -std=c++11 -o ece650-a2
#include <iostream>
#include <sstream>

#include "a2.hpp"

int main(int argc, char** argv) {

    // sign character and commands
    const char angle = '<';
    const char cmd_1 = 'V';
    const char cmd_2 = 'E';
    const char cmd_3 = 's';

    int i, j = 0;

    int v = 0;
    bool **matrix;

    // read from stdin until EOF
    while (!std::cin.eof()) {

        // read a line of input until EOL and store in a string
        std::string line;
        std::getline(std::cin, line);

        // if nothing was read, go to top of the while to check for eof
        if (line.size() == 0)
            continue;

        // create an input stream based on the line
        // we will use the input stream to parse the line
        std::istringstream input(line);
        
        // ignore empty lines
        std::ws(input);
        if (input.eof())
            continue;

        char ch;
        input >> ch;
        // just in case
        if (input.fail()) {
            std::cerr << "Error: Failed to read input" << std::endl;
            continue;
        }
        
        // input_line: V v
        if (ch == cmd_1) {
            input >> v;

            if (v < 2) 
                std::cerr << "Error: V should be greater than 1" << std::endl;
            // initialize adjacency matrix
            // we simply suppose that v cannot be too large
            else {
                matrix = new bool *[v];
                for (j = 0; j < v; j++)
                    matrix[j] = new bool[v];
                for (i = 0; i < v; i++)
                    for (j = 0; j < v; j++) 
                        matrix[i][j] = false;
            }
        }
        // input_line: E {<stem,dtem>,<>}
        else if (ch == cmd_2) {
            std::ws(input);
            int stem, dtem = 0;
            while (!input.eof()) {
                input >> ch;
                
                // set the adjacency matrix
                if (ch == angle) {
                    input >> stem;
                    input >> ch;
                    input >> dtem;

                    // test whether input edge is out of range
                    if (stem <= 0 || dtem <= 0 || stem > v || dtem > v) {
                        std::cerr << "Error: Wrong vertex(es) included" << std::endl;
                        break;
                    }

                    // undirected graph
                    matrix[stem - 1][dtem - 1] = true;
                    matrix[dtem - 1][stem - 1] = true;
                }
            }
        }
        // input_line: s sour des
        else if (ch == cmd_3) {
            int sour, des;
            input >> sour;
            input >> des;
            if (sour <= 0 || des <= 0 || sour > v || des > v) 
                std::cerr << "Error: Vertex(es) out of range" << std::endl;
            else {
                int *stack = new int [v + 1] ();
                int top = 0;

                // do Bellman-Ford and output
                if (process(matrix, v, sour, des, stack, top)) {
                    std::cout << stack[top--];
                    for (; top >= 0; top--) 
                        std::cout << "-" << stack[top];
                    std::cout << std::endl;
                }
                else
                    std::cerr << "Error: Path does not exist between them" << std::endl;
                
                // destroy the stack
                delete[] stack;
            }
        }
        else 
            std::cerr << "Error: Wrong command" << std::endl;
    }

    // destroy old adjacency matrix
    for (i = 0; i < v; i++) 
        delete[] matrix[i];
    delete[] matrix;

    return 0;
}
