#include <cerrno>
#include <deque>
#include <iostream>
#include <unistd.h>
#include <vector>

#include "../../include/PmergeVector.hpp"
#include "../../include/PmergeDeque.hpp"
#include "../include/PmergeMeTester.hpp"

int runTest(int argc, char **args) {
    PmergeVector vec;

    std::vector<int> vec_result = vec.sort(argc, args);
    if (errno != 0 || vec_result.empty()) {
        return 1;
    }

    vec.printSeq(vec_result, argc - 1);

    PmergeDeque deq;
    std::deque<int> deq_result = deq.sort(argc, args);
    if (errno != 0 || deq_result.empty()) {
        return 1;
    }

    deq.printSeq(deq_result, argc - 1);
    return 0;
}

int main(int argc, char **argv) {
    int result = runTest(argc, argv);
    std::cerr.flush();
    std::cout.flush();
    return result;
}
