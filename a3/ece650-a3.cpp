#include <iostream>
#include <vector>
#include <signal.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>


// get line from std input
int sfind(void) {
    while (!std::cin.eof()) {
        std::string line;
        std::getline(std::cin, line);
        if (line.size() > 0){
            usleep(360000);
            std::cout << line << std::endl;
        }
    }
    return 0;
}


int main (int argc, char **argv) {
    std::vector<pid_t> kids;

    int p1[2];
    pipe(p1);

    pid_t child;
    child = fork();
    if (child == 0) {
        // rgen
        dup2(p1[1], STDOUT_FILENO);
        close(p1[0]);
        close(p1[1]);

        char **argrg = new char *[argc + 1];
        argrg[0] = (char *)"rgen";
        for (unsigned i = 1; i < unsigned(argc); i++)
            argrg[i] = argv[i];
        argrg[argc] = nullptr;

        execv("./rgen", argrg);

        std::cerr << "Error: Fail to execute rgen" << std::endl;
        return 1;
    }
    else if (child < 0) {
        std::cerr << "Error: Could not fork" << std::endl;
        return 1;
    }

    kids.push_back(child);

    int p2[2];
    pipe(p2);

    child = fork();
    if (child == 0) {
        // ece650-a2
        close(p1[0]);
        close(p1[1]);

        dup2(p2[0], STDIN_FILENO);
        close(p2[0]);
        close(p2[1]);

        // return sfind();

        char *arga2[2];
        arga2[0] = (char *)"ece650-a2";
        arga2[1] = nullptr;
        execv("./ece650-a2", arga2);

        std::cerr << "Error: Fail to execute ece650-a2" << std::endl;
        return 1;
    }
    else if (child < 0) {
        std::cerr << "Error: Could not fork" << std::endl;
        return 1;
    }

    kids.push_back(child);

    child = fork();
    if (child == 0) {
        // ece650-a1
        dup2(p1[0], STDIN_FILENO);
        close(p1[0]);
        close(p1[1]);

        dup2(p2[1], STDOUT_FILENO);
        close(p2[0]);
        close(p2[1]);

        char *arga1[3];
        arga1[0] = (char *)"python3";
        arga1[1] = (char *)"./ece650-a1.py";
        arga1[2] = nullptr;
        execv("/usr/bin/python3", arga1);

        std::cerr << "Error: Fail to execute ece650-a1" << std::endl;
        return 1;
    }
    else if (child < 0) {
        std::cerr << "Error: Could not fork" << std::endl;
        return 1;
    }

    kids.push_back(child);

    close(p1[0]);
    close(p1[1]);

    child = fork();
    if (child == 0) {
        // get line from std input (s command)
        dup2(p2[1], STDOUT_FILENO);
        close(p2[0]);
        close(p2[1]);

        int res = sfind();

        // kill rgen
        kill(kids.front(), SIGTERM);

        return res;
    }
    else if (child < 0) {
        std::cerr << "Error: Could not fork" << std::endl;
        return 1;
    }

    kids.push_back(child);
    child = 0;

    close(p2[0]);
    close(p2[1]);

    int status;
    waitpid(kids.front(), &status, 0);
    
    // // kiling spree
    for (pid_t k : kids) {
        kill(k, SIGTERM);
        waitpid(k, &status, 0);
    }
    
    return 0;
}
