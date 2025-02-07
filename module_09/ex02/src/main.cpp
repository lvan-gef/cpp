#include "../include/PmergeMe.hpp"

int main(int argc, char **argv) {
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
