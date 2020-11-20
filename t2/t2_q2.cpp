int main() {
    int p1[2];
    int p2[2];
    pipe(p1);
    pipe(p2);

    pid_t child1;
    child1 = fork();
    if (child1 == 0) {
        dup2(p1[1], STDOUT_FILENO);
        close(p1[0]);
        close(p1[1]);

        dup2(p2[0], STDIN_FILENO);
        close(p2[0]);
        close(p2[1]);

        exec(A);

        std::cerr << "Error\n";
        return 1;
    }
    else if (child < 0) {
        std::cerr << "Error\n";
        return 1;
    }

    pid_t child2;
    child2 = fork();
    if (child2 == 0) {
        dup2(p1[0], STDIN_FILENO);
        close(p1[0]);
        close(p1[1]);

        dup2(p2[1], STDOUT_FILENO);
        close(p2[0]);
        close(p2[1]);

        exec(B);

        std::cerr << "Error\n";
        return 1;
    }
    else if (child < 0) {
        std::cerr << "Error\n";
        return 1;
    }

    close(p1[0]);
    close(p1[1]);
    close(p2[0]);
    close(p2[1]);

    waitpid(child1, &status, 0);
    waitpid(child2, &status, 0);
    return 0;
}