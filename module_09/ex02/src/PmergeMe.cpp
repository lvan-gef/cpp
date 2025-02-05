#include "PmergeMe.hpp"
#include <cerrno>
#include <climits>
#include <cstdlib>

void PmergeMe::run_vector(int size, char **args) {
    _vec.sort(size, args);

}
