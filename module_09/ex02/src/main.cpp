#include <iostream>

#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Expect at least 1 argument got: 0" << '\n';
        return 1;
    }

    PmergeMe merge{};
    merge.run_vector(argc, argv);
    if (errno != 0) {
        return 1;
    }

    merge.run_deque(argc, argv);
    if (errno != 0) {
        return 2;
    }

    return 0;
}
