#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <vector>

#include "../include/PmergeDeque.hpp"
#include "../include/PmergeVector.hpp"

class PmergeMe {
  public:
    PmergeMe() = default;

    PmergeMe(const PmergeMe &rhs) = default;
    PmergeMe &operator=(const PmergeMe &rhs) = default;

    PmergeMe(PmergeMe &&rhs) noexcept = default;
    PmergeMe &operator=(PmergeMe &&rhs) noexcept = default;

    ~PmergeMe() = default;

  public:
    std::vector<int> run_vector(int size, char **args);
    std::deque<int> run_deque(int size, char **args);

  private:
    PmergeVector _vec;
    PmergeDeque _deq;
};

#endif // !PMERGEME_HPP
