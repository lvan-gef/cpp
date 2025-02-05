#include "PmergeMe.hpp"

void PmergeMe::run_vector(int size, char **args) {
    _vec.sort(size, args);
}

void PmergeMe::run_deque(int size, char **args) {
    _deq.sort(size, args);
}
