#include <cerrno>
#include <cstdio>
#include <unistd.h>
#include <vector>

#include "../../include/PmergeVector.hpp"
#include "../include/PmergeMeTester.hpp"

int runTest(int argc, char **args) {
    PmergeVector vec;

    std::vector<int> vec_result = vec.sort(argc, args);
    if (errno != 0) {
        return 1;
    }
    vec.printSeq(vec_result, argc - 1);

    return 0;
}

int main(int argc, char **argv) {
    return runTest(argc, argv);
}
