#include <iostream>

#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Expect at least 1 argument got: 0" << '\n';
        return 1;
    }

    PmergeMe merge{};
    merge.run_vector(argc - 1, argv);


    return 0;
}
