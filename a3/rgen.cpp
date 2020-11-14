// # include ""
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <vector>

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


// test whether a point is valid to be output
bool tvalid(std::vector<int *> segs, const int mx, const int my,
            const int x, const int y) {
    if (x == mx && y == my) {
        return false;
    }
    else {
        const auto diffxp = x - mx;
        const auto diffyp = y - my;
        int diffxk, diffyk;
        int gradp, gradk;
        int base, top;

        for (auto k : segs) {
            diffxk = k[2] - k[0];
            diffyk = k[3] - k[1];

            if (diffxp == 0 && diffxk == 0) {
                if (mx == k[0]) {
                    base = std::min(k[1], k[3]);
                    top = std::max(k[1], k[3]);
                    if (!((x <= base && mx <= base) || (x >= top && mx >= top)))
                        return false;
                }
            }
            else if (diffxp == 0 || diffxk == 0) { }
            else {
                gradp = diffyp / diffxp;
                gradk = diffyk / diffxk;
                
                if (gradp == gradk && (my - gradp * mx) == (k[1] - gradk * k[0])) {
                    base = std::min(k[0], k[2]);
                    top = std::max(k[0], k[2]);
                    if (!((x <= base && mx <= base) || (x >= top && mx >= top)))
                        return false;
                }
            }
        }
        return true;
    }
}


int main(int argc, char **argv) {
    const unsigned limit = 25;
    const int cst_sp = 10;
    const int cst_np = 5;
    const int cst_lp = 5;
    const int cst_cp = 20;

    opterr = 0;
    std::string temval;
    int cmd = -1;
    int sp = cst_sp;
    int np = cst_np;
    int lp = cst_lp;
    int cp = cst_cp;

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
            std::cerr << "Error: [rgen] Wrong system parameter(s) received\n";
        }
    }
    if (sp < 2 || np < 1 || lp < 5 || cp < 1) {
        std::cerr << "Error: [rgen] Wrong value of parameter(s)\n";
        return 1;
    }

    // open /dev/urandom to read
    std::ifstream urandom("/dev/urandom");
    if (urandom.fail()) {
        std::cerr << "Error: Cannot open /dev/urandom\n";
        return 1;
    }

    int x, y, mx, my;
    int *temseg;
    std::vector<int *> segs;
    unsigned sr, nr, lr;
    unsigned num = 0;
    unsigned cntst = 0;
    unsigned cntsg, cntry = 0;

    while (true) {
        // clear the old graph
        while (cntst > 0) {
            std::cout << "rm \"I love ECE650 ";
            std::cout << (3000 + --cntst) << " times\"" << std::endl;
        }

        // clear storage of segments
        for (auto k : segs) 
            delete[] k;
        segs.clear();
        
        // sr is the number of streets
        urandom.read((char *)&num, sizeof(unsigned));
        sr = num % unsigned(sp - 2 + 1) + 2;

        // generate each street
        for (unsigned i = 0; i < sr; i++) {
            std::cout << "add \"I love ECE650 ";
            std::cout << (3000 + cntst++) << " times\"";

            // nr is the number of line-segments
            urandom.read((char *)&num, sizeof(unsigned));
            nr = num % unsigned(np - 1 + 1) + 1;

            // generate the 1st point
            urandom.read((char *)&num, sizeof(unsigned));
            mx = num % ((cp - 1 + 1) * 2 + 1) - cp;
            urandom.read((char *)&num, sizeof(unsigned));
            my = num % ((cp - 1 + 1) * 2 + 1) - cp;

            std::cout << " (" << mx << "," << my << ")";

            cntsg = 0;
            cntry = 0;
            // try to generate 2nd ~ (nr + 1)th point
            while (cntsg < nr) {
                cntry++;

                urandom.read((char *)&num, sizeof(unsigned));
                x = num % ((cp - 1 + 1) * 2 + 1) - cp;
                urandom.read((char *)&num, sizeof(unsigned));
                y = num % ((cp - 1 + 1) * 2 + 1) - cp;

                if (tvalid(segs, mx, my, x, y)) {
                    std::cout << " (" << x << "," << y << ")";

                    // store segments
                    temseg = new int [4];
                    temseg[0] = mx;
                    temseg[1] = my;
                    temseg[2] = x;
                    temseg[3] = y;
                    segs.push_back(temseg);

                    mx = x;
                    my = y;

                    cntsg ++;
                    cntry = 0;
                }
                else if (cntry >= limit) {
                    std::cerr << "Error: Failed to generate valid specification\n";
                    urandom.close();
                    return 0;
                }
            }

            // flush the current line of add~
            std::cout << std::endl;
        }

        // pass gg command
        std::cout << "gg" << std::endl;

        // wait lr seconds before the next input
        urandom.read((char *)&num, sizeof(unsigned));
        lr = num % unsigned(lp - 5 + 1) + 5;
        sleep(lr);
    }

    urandom.close();
    return 1;
}