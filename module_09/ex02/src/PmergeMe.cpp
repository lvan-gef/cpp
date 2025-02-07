#include <deque>
#include <vector>

#include "../include/PmergeMe.hpp"

std::vector<int> PmergeMe::run_vector(int size, char **args) {
    return _vec.sort(size, args);
}

std::deque<int> PmergeMe::run_deque(int size, char **args) {
    return _deq.sort(size, args);
}
