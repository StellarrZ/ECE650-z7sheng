// # include ""
#include <iostream>
#include <unistd.h>

int main (int argc, char **argv) {
    std::cout << "add \"Amphitheatre Prkw\" (2,-1)(2,2) (5,5) (5,6) (3,8)\n"
              << "mod \"amphitheatre PRKW\" (2,8)(4,6)(5,6)(7,8)\n"
              << "add \"One Infinite Loop\" (2,4)(3,6)(6,6)(8,4)\n"
              << "gg"
              << std::endl;
    sleep(15);
    return 0;
}