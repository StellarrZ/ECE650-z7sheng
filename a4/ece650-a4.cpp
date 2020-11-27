#include <iostream>
#include <sstream>

#include "a4.hpp"

int main(int argc, char** argv) {

    // sign character and commands
    const char angle = '<';
    const char cmd_1 = 'V';
    const char cmd_2 = 'E';

    unsigned i, j = 0;

    unsigned v = 0;
    bool **matrix;

    // read from stdin until EOF
    while (!std::cin.eof()) {

        // read a line of input until EOL and store in a string
        std::string line;
        std::getline(std::cin, line);

        // if nothing was read, go to top of the while to check for eof
        if (line.empty())
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

            if (v < 2) {
                std::cerr << "Error: V should be greater than 1" << std::endl;
            }
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
            bool noedge = true;
            unsigned stem, dtem = 0;
            while (!input.eof()) {
                input >> ch;
                
                // set the adjacency matrix
                if (ch == angle) {
                    noedge = false;
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

            if (noedge) {
                std::cout << std::endl;
            }
            // min vertex cover
            else if (minvc(matrix, v) != 0) {
                std::cerr << "Error: Failed to execute minvc()\n";
            }
        }
        else {
            std::cerr << "Error: Wrong command" << std::endl;
        }
    }

    return 0;
}