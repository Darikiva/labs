#include <iostream>
#include "demofuncs.h"
#include "boost/process.hpp"

int main(int argc, char ** argv) {
    int case_n;
    std::cin >> case_n;
    if (case_n >=0 && case_n < 6) std::cout << spos::lab1::demo::g_func<spos::lab1::demo::INT>(case_n) << std::endl;
    return 0;
}
