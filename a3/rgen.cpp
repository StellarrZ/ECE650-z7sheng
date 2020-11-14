// # include ""
#include <iostream>
#include <unistd.h>

// int main(int argc, char **argv) {
//     // std::cout << "add \"Amphitheatre Prkw\" (2,-1)(2,2) (5,5) (5,6) (3,8)\n"
//     //           << "mod \"amphitheatre PRKW\" (2,8)(4,6)(5,6)(7,8)\n"
//     //           << "add \"One Infinite Loop\" (2,4)(3,6)(6,6)(8,4)\n"
//     //           << "gg\n"
//     //           << std::endl;

//     // std::cout << "rm \"Amphitheatre Prkw\"\n"
//     //           << "rm \"One Infinite Loop\"\n"
//     //           << "add \"Amphitheatre Prkw\" (2,-1)(2,2) (5,5) (5,6) (3,8)\n"
//     //           << "add \"One Infinite Loop\" (2,4)(3,6)(6,6)(8,4)\n"
//     //           << "gg\n"
//     //           << std::endl;

//     std::cout << "add \"Amphitheatre Prkw\" (2,-1)(2,2) (5,5) (5,6) (3,8)" << std::endl;
//     std::cout << "mod \"amphitheatre PRKW\" (2,8)(4,6)(5,6)(7,8)" << std::endl;
//     std::cout << "add \"One Infinite Loop\" (2,4)(3,6)(6,6)(8,4)" << std::endl;
//     std::cout << "gg" << std::endl;
//     sleep(3);

//     std::cout << "rm \"Amphitheatre Prkw\"" << std::endl;
//     std::cout << "rm \"One Infinite Loop\"" << std::endl;
//     std::cout << "add \"Amphitheatre Prkw\" (2,-1)(2,2) (5,5) (5,6) (3,8)" << std::endl;
//     std::cout << "add \"One Infinite Loop\" (2,4)(3,6)(6,6)(8,4)" << std::endl;
//     std::cout << "gg" << std::endl;

//     sleep(15);
//     return 0;
// }

int main(int argc, char **argv) {
    opterr = 0;
    std::string temval;
    int cmd = -1;
    int sp = 10;
    int np = 5;
    int lp = 5;
    int cp = 20;

    while ((cmd = getopt(argc, argv, "s:n:l:c:")) != -1) {
        switch (cmd) {
        case 's':
            temval = optarg;
            sp = atoi(temval.c_str());
            break;
        case 'n':
            temval = optarg;
            np = atoi(temval.c_str());
            break;
        case 'l':
            temval = optarg;
            lp = atoi(temval.c_str());
            break;
        case 'c':
            temval = optarg;
            cp = atoi(temval.c_str());
            break;
        case '?':
            std::cerr << "Error: Wrong system parameter(s) received" << std::endl;
        }
    }

    // test para
    std::cerr << sp << np << lp << cp << "\n";

    sleep(10);
    
    return 0
}